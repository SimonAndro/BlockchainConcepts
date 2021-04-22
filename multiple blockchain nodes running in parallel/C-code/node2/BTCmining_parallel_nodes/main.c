/*********************************************************************
* Filename:   main.c
* Author:     Nakibinge Simon, slemonla13@gmail.com
* Copyright:
* Details:    Blockchain nodes running parallel on the network
*********************************************************************/

/*************************** HEADER FILES ***************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <stdint.h>
#include <math.h>
#include <time.h>

#include "main.h"
#include "util/include/util.h"

#include "secp256k1/include/secp256k1.h"
#include "crypto/ripemd160.h"
#include "crypto/hash.h"

#include "blockchain/include/transaction.h"
#include "blockchain/include/block.h"

#include "network/include/network.h"


/*************************** MACROS     *****************************/
//#define DEBUG     1   // uncomment to analyse function process outputs

#define ALLOWSAVE 1   // uncomment to save block binary file

#define NUMBER_OF_BLOCKS 10 // generate 10 blocks

//#define GENERATE_TRANSACTION_POOL 1    // uncoment to generate a random transaction pool

#define NUMBER_OF_RND_TRANSACTIONS 100 // number of random transactions to generate

BLOCK B = {0}; //! must initialize it to zero or else results into random gabbage
               // that makes the hash change on every run

static secp256k1_context *ctx = NULL; // secp256k1 context


/**
* Main function
*/
int main(int argc, char* argv[])
{

    if(argc < 3)
    {
        printf("usage: BTCmining nodename port\n");
        return 1;
    }

    SOCKET socket_listen; // server socket

    socket_listen = initializeNetwork(argv); // initialize server network

    fd_set master; 
    FD_ZERO(&master);
    FD_SET(socket_listen, &master);
    SOCKET max_socket = socket_listen;

    printf("Waiting for connections...\n");

    NETWORKRESPONSE ntRes = {0};   // network response object
    char response[2048] = {0}; // reponse to the client(bytes)

    clock_t start_t, end_t;     // to measure execution time
    double cpu_time_used;

    ctx = secp256k1_context_create(
	SECP256K1_CONTEXT_SIGN | SECP256K1_CONTEXT_VERIFY); //secp256k1 context

    srand ((unsigned int) time (NULL));  // Use current time as seed for random generator

    /* generate my public and private address */
    KEYPAIR myKeys;
    genKeyPair(myKeys.private,myKeys.public);

    uint64_t txnPointer = 0;

#ifdef GENERATE_TRANSACTION_POOL
    /* generate a sample transaction pool */
    generateRandTxnToFile(NUMBER_OF_RND_TRANSACTIONS);
#endif

    /* listen from known nodes to get current block height*/
    KNOWNNODE knownNode ={0};
    strcpy(knownNode.nodeName,"127.0.0.1");
    if(!strcmp("8081",argv[2]))
    {
        strcpy(knownNode.nodeService,"8082");
    }else{
        strcpy(knownNode.nodeService,"8081");
    }

    printf("Configuring remote address for Known Node...\n");
    struct addrinfo hints;
    memset(&hints, 0, sizeof(hints));
    hints.ai_socktype = SOCK_STREAM;
    struct addrinfo *peer_address;
    if (getaddrinfo(knownNode.nodeName, knownNode.nodeService, &hints, &peer_address)) {
        fprintf(stderr, "getaddrinfo() failed. (%d)\n", GETSOCKETERRNO());
    }
    else
    {
        printf("Remote address is: ");
        char address_buffer[100];
        char service_buffer[100];
        getnameinfo(peer_address->ai_addr, peer_address->ai_addrlen,
                address_buffer, sizeof(address_buffer),
                service_buffer, sizeof(service_buffer),
                NI_NUMERICHOST);
        printf("%s %s\n", address_buffer, service_buffer);

        printf("Connecting to remote Node...\n");
        if (connect(socket_listen,
                    peer_address->ai_addr, peer_address->ai_addrlen)) {
            fprintf(stderr, "connect() failed. (%d)\n", GETSOCKETERRNO());
            printf("possibly no live node with this address found! \n");
        }
        freeaddrinfo(peer_address);

        printf("Connected to Node.\n");
    }

    uint8_t hashBuf[BLAKE3_OUT_LEN] ={0}; // store hash value
    
    int createNew = 0;

    for(int blockHeight = 0; blockHeight<NUMBER_OF_BLOCKS; blockHeight++)    // generate NUMBER_OF_BLOCKS blocks chained in the block chain
    {
        printf("--------------------------Start-----------------------------\n");

        // create block data
        memset(&B,0,sizeof(BLOCK));
        B.header.chainVersion = 3; // third version of chain
        B.header.height = blockHeight;
        memcpy(B.header.prevHash,hashBuf,sizeof(hashBuf));
        B.header.nonce_1 = 0;
        B.header.nonce_2 = 0;
        B.header.difficulty = 20; // set difficulty to 17 zero bits at beginning of hash value
        B.header.timeStamp = time(NULL);
        B.header.amount = 1+rand()%500; // random amount between 0 and 500
        memcpy(B.header.coinBase,myKeys.public,33); // add my publickey as miner address

#ifdef DEBUG
        printBlockHeader(B.header);  // print block header contents
        printf("\n");
#endif

        B.header.trxCount = 10; // random number of transactions to put in one block                            
        getTransactionFromFile(&B,txnPointer);   // add transactions to block  

#ifdef DEBUG
        for(int i = 0; i<B.header.trxCount; i++)
        {
            printf("\n\ntransaction number %d\n\n",i);
            printTXN(B.transactions[i]);
        }
#endif

        /* verify transactions in the block */
        printf("number of txn added to block:  %d\n",B.header.trxCount);
        printf("verifying transactions...");
        char  txnValid_flag = 1;
        for(int i = 0; i<B.header.trxCount; i++)
        {
            if(verifyTransaction(B.transactions[i],ctx))
            {
                txnValid_flag = 0;
                break;
            }
        }

        if(!txnValid_flag)// ignore blocks with invalid transactions
        {
            printf("Block ignored because contains invalid txn(s)\n");
            continue; 
        }else{
            printf("All txns in block are valid\n");
        } 

        printf("mining...");
        start_t = clock();
        while(1)  // mining
        {
            fd_set reads;
            reads = master;

            struct timeval timeout;
            timeout.tv_sec = 0;
            timeout.tv_usec = 0;

            if (select(max_socket+1, &reads, 0, 0, &timeout) < 0) {
                fprintf(stderr, "select() failed. (%d)\n", GETSOCKETERRNO());
                return 1;
            }

            SOCKET i;
            for(i = 1; i <= max_socket; ++i) {
                if (FD_ISSET(i, &reads)) {

                    if (i == socket_listen) {
                        struct sockaddr_storage client_address;
                        socklen_t client_len = sizeof(client_address);
                        SOCKET socket_client = accept(socket_listen,
                                (struct sockaddr*) &client_address,
                                &client_len);
                        if (!ISVALIDSOCKET(socket_client)) {
                            fprintf(stderr, "accept() failed. (%d)\n",
                                    GETSOCKETERRNO());
                            continue;
                        }

                        FD_SET(socket_client, &master);
                        if (socket_client > max_socket)
                            max_socket = socket_client;

                        char address_buffer[100];
                        getnameinfo((struct sockaddr*)&client_address,
                                client_len,
                                address_buffer, sizeof(address_buffer), 0, 0,
                                NI_NUMERICHOST);
                        printf("\n@@@New connection from [%s] socket number[%llu]\n ", address_buffer,socket_client);
                    } else {
                        
                        int bytes_received = recv(i, response, sizeof(NETWORKRESPONSE), MSG_WAITALL);
                        if (bytes_received < 1) {
                            FD_CLR(i, &master);
                            CLOSESOCKET(i);
                            continue;
                        }

                        memcpy(&ntRes,response,sizeof(NETWORKRESPONSE));

                        if(!strcmp("UPDATE",ntRes.msg)) // request for latest chain
                        {
                            BLOCK reqB={0};
                            for(size_t reqHeight = ntRes.height; reqHeight<blockHeight; reqHeight++)
                            {
                                blockFromFile(&reqB,reqHeight); // read block from file
                                memcpy(response,&reqB,sizeof(BLOCK));// copy block to send buffer
                                int begin = 0;
                                while (begin < sizeof(BLOCK)) { // send entire block
                                    int sent = send(i, response + begin, sizeof(BLOCK) - begin, 0);
                                    if (sent == -1) {
                                        //Handle error, maybe disconnected?
                                        break; // break from while lopl
                                        reqHeight = blockHeight; // for loop wont run again
                                    }
                                    begin += sent;
                                }
                            }
                        }
                        else if(!strcmp("NEWBLOCK",ntRes.msg)) // received new published block
                        {

                            int bytes_received = recv(i, response, sizeof(BLOCK), MSG_WAITALL);
                            if (bytes_received < 1) {
                                continue;
                            }
                            
                            BLOCK recvB={0};
                            memcpy(&recvB,response,sizeof(BLOCK));
                            hashData(&(recvB.header),sizeof(recvB.header),hashBuf); // calculate block header hash  first time
                            hashData(hashBuf,sizeof(hashBuf),hashBuf);    // calculate block header hash second time
                            
                            // verify hash value
                            if(!verifyHash(hashBuf,recvB.header.difficulty))
                            {
                                blockToFile(&recvB); //save block to binary file 
                                blockHeight = recvB.header.height;
                                createNew = 1;

                            } // if verifyhash

                        } // else received nonce 

                    } // else another socket(s) is ready for reading

                } //if FD_ISSET

            } //for i to max_socket

            if(createNew == 1)
            {
                createNew = 0;
                break; // break from mining while loop
            }

            hashData(&B.header,sizeof(B.header),hashBuf); // calculate block header hash  first time
            hashData(hashBuf,sizeof(hashBuf),hashBuf);    // calculate block header hash second time

            // verify hash value
            if(!verifyHash(hashBuf,B.header.difficulty))
            {
                end_t = clock();
                cpu_time_used = ((double) (end_t - start_t)) / CLOCKS_PER_SEC;

                printf(" Work done by server! ...time %.5f s\n",cpu_time_used);
                printf("---------------block header contents------------------\n");
                printBlockHeader(B.header);
                printf("------------------------------------------------------\n");

                /* broadcast to other nodes connected to me*/
                SOCKET j;
                memset(ntRes.msg,0,sizeof(ntRes.msg));
                strcpy(ntRes.msg,"NEWBLOCK");
                for (j = 1; j <= max_socket; ++j) {
                    if (FD_ISSET(j, &master)) {
                        if (j == socket_listen)
                            continue;
                        else
                        {
                            memcpy(response,&ntRes,sizeof(NETWORKRESPONSE));
                            send(j, response, sizeof(NETWORKRESPONSE), 0);
                        }
            
                    }
                }
                break; // break from mining while loop
            }
            B.header.nonce_2++; // increment nonce_2
        }

#ifdef ALLOWSAVE 
        blockToFile(&B); //save block to binary file 
#endif // ALLOWSAVE

        printf("---------------------------End---------------------------\n\n");
    }

    /* print atmost 9 transactions in the last added block*/
#ifdef DEBUG
    printf("-----------------Transactions in the last block-------------------\n");
    for(int i = 0; i<B.header.trxCount; i++)
    {
        printf("-----------TXN start---------------\n");
        printTXN(B.transactions[i]);
        printf("-----------TXN end-----------------\n");

        if(i==9) break;
    }
#endif

    printf("Calculating wallet balances ...\n");
    calculateWalletBalance(0,NUMBER_OF_BLOCKS,&B); // calculate balances for each wallet

    closeNetwork(socket_listen); // clean up and close network before returning

    return 0;
}

 
/**
 * @brief generates a pool of random transactions
 * 
 * @param num number of transactions to generate
 * @param fileName name of file to store in generated transactions
 */
void generateRandTxnToFile(int num)
{
    TRANSACTION Txn;    
    uint8_t signKey[32]; // hold private key
    KEYPAIR sample_keys_pairs[10]={0}; // sample public, private key pairs

    for(int i = 0; i<10; i++) // generate 10 sample public private key pairs
    {
        genKeyPair((sample_keys_pairs[i].private),(sample_keys_pairs[i].public));
    }

    FILE* filePtr = NULL;// pointer to the transaction pool file
    for(size_t j = 0; j<num; j++)
    {
        /* generate and sign a transaction */
        Txn = genTransaction(sample_keys_pairs,signKey);
        signTransaction(&Txn,signKey,ctx); 

        /* save transaction to bin file*/
        char txnFile[20] ={0};
        sprintf(txnFile,"../txnPool/txn%ld.bin",j);
        filePtr = fopen(txnFile,"wb");
        if(filePtr == NULL)
        {
            printf("file name %s",txnFile);
            err("generateRandTxnToFile couln't open file \n");
        }

        fwrite(&Txn,1,sizeof(TRANSACTION),filePtr);
        fclose(filePtr); // close transaction file
    }


}

/** @brief genKeyPair, generates a public and priavte key pair
 *  @param privBuf, buffer for private key
 *  @param pubBuf, buffer for public key
 *  @return void
 */ 
void genKeyPair(uint8_t *privBuf, uint8_t *pubBuf)
{
    genRandomBytes(32,privBuf);   // Load private key (seckey) from random bytes

    while(!secp256k1_ec_seckey_verify(ctx, privBuf))// generate another private key if got wrong key
    {
         genRandomBytes(32,privBuf);   // Load private key (seckey) from random bytes

    }

    /* compute public key*/
    secp256k1_pubkey pubkey;
    if(!secp256k1_ec_pubkey_create(ctx, &pubkey, privBuf))
    {
        err("Public key computation failed");
    }
    // serialize the pubkey in compressed format
    size_t pubKLen = 33;
    secp256k1_ec_pubkey_serialize(ctx, pubBuf, &pubKLen, &pubkey, SECP256K1_EC_COMPRESSED);

    /* create a fake balance for this public key*/
    FILE* filePtr = NULL;
    char sWFname[100] = {0}; 

    walletFileFromHex(pubBuf,sWFname);
    filePtr = fopen(sWFname,"w"); // open file in appending mode or create one if doesn't exist
    if(filePtr == NULL)
    {
        err("genKeyPair: file open failed");
    }
    fprintf(filePtr,"%ld",rand()%500); // write fake balance
    if(fclose(filePtr))         // close file
    {
        err("genKeyPair: file close failed");
    }

#ifdef DEBUG
    /* Loop through and print each byte of the private and public  key, */
    printf("Private: ");
    for(int i=0; i<32; i++) {
            printf("%02X", privBuf[i]);
    }
    printf("\n");

    printf("Public : ");
    for(int i=0; i<pubKLen; i++) {
            printf("%02X", pubBuf[i]);
    }
    printf("\n"); 
#endif

}

/** @brief  genRandomBytes, generate a stream of random bytes
 *  @param  num_bytes,  number of bytes
 *  @param  buff, storage buffer for the bytes
 *  @return void
 */ 
void genRandomBytes (size_t num_bytes, unsigned char * buff)
{
  size_t i;

  for (i = 0; i < num_bytes; i++)
  {
    buff[i] = rand ();
  }
}
