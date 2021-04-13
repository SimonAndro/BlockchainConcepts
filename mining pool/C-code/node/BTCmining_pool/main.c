/*********************************************************************
* Filename:   main.c
* Author:     Nakibinge Simon, slemonla13@gmail.com
* Copyright:
* Details:    Creating and verifying transactions before adding new block to chain
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

BLOCK B = {0}; //! must initialize it to zero or else results into random gabbage
                // that makes the hash change on every run

static secp256k1_context *ctx = NULL; // secp256k1 context


/**
* Main function
*/
int main()
{

    SOCKET socket_listen; // server socket

    socket_listen = initializeNetwork(); // initialize server network

    fd_set master; 
    FD_ZERO(&master);
    FD_SET(socket_listen, &master);
    SOCKET max_socket = socket_listen;

    printf("Waiting for connections...\n");

    NETWORKRESPONSE ntRes ={0};   // network response object
    char response[1024] ={0}; // reponse to the client(bytes)
 
    int res;     // returned value  from calling a function

    clock_t start_t, end_t;     // to measure execution time
    double cpu_time_used;

    ctx = secp256k1_context_create(
	SECP256K1_CONTEXT_SIGN | SECP256K1_CONTEXT_VERIFY); //secp256k1 context


    KEYPAIR sample_keys_pairs[10]={0}; // sample public, private key pairs

    srand ((unsigned int) time (NULL));  // Use current time as seed for random generator

    for(int i = 0; i<10; i++) // generate 10 sample public private key pairs
    {
        genKeyPair(&(sample_keys_pairs[i].private),&(sample_keys_pairs[i].public));
    }


    uint8_t hashBuf[BLAKE3_OUT_LEN] ={0}; // store hash value
     char sampleCoinBase[4][35]=     // assumming there are four miners
    {
        {"16ftSEQ4ctQFDtVZiUBusQUjRrGhM3JYwe"},
        {"1K4Y7MF8uXFu7GrwvDcUpwEoNkKcREFnh7"},
        {"3PUMTdjxMeQgX7RbMweLJULkQhJ8owCF6p"},
        {"3KEMauXo856i59jhrx1Fb6yb4C68xMoXCR"}
    };

    
    int createNew = 0;

    for(int i = 0; i<NUMBER_OF_BLOCKS; i++)    // generate NUMBER_OF_BLOCKS blocks chained in the block chain
    {
        printf("--------------------------Start-----------------------------\n");

        // create block data
        memset(&B,0,sizeof(BLOCK));
        B.header.chainVersion = 3; // second version of chain
        B.header.height = i;
        memcpy(B.header.prevHash,hashBuf,sizeof(hashBuf));
        B.header.nonce_1 = 0;
        B.header.nonce_2 = 0;
        B.header.difficulty = 20; // set difficulty to 17 zero bits at beginning of hash value
        B.header.timeStamp = time(NULL);
        B.header.amount = 1+rand()%500; // random amount between 0 and 500
        memcpy(B.header.coinBase,sampleCoinBase[rand()%4],33); // get random miner

        #ifdef DEBUG
            printBlockHeader(B.header);  // print block header contents
            printf("\n");
        #endif

        B.header.trxCount = 1+rand()%MAX_TRANSACTION_PER_BLOCK; // random number of transactions to put in one block
                                                                // number doesn't exceed @MAX_TRANSACTION_PER_BLOCK, to maintain block size below 1MB
        
        for(int i =0;i<B.header.trxCount; i++)
        {
            /* generate random transactions */
            TRANSACTION Txn;
            uint8_t signKey[32];
            Txn = genTransaction(sample_keys_pairs,signKey);

            signTransaction(&Txn,signKey,ctx); // signing transaction 

            B.transactions[i] = Txn;   // add transaction to block  
         
        }

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
                            return 1;
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

                        if(!strcmp("JOB",ntRes.msg))
                        {
                            B.header.nonce_1 = i; // assign this miner a nonce_1

                            memcpy(response,&(B.header),sizeof(B.header));

                            send(i, response, sizeof(BLOCKHEADER), 0);
                        }
                        else if(!strcmp("NONCE",ntRes.msg))
                        {
                            B.header.nonce_1 = ntRes.nonce_1;
                            B.header.nonce_2 = ntRes.nonce_2;

                            hashData(&B.header,sizeof(B.header),hashBuf); // calculate block header hash  first time
                            hashData(hashBuf,sizeof(hashBuf),hashBuf);    // calculate block header hash second time
                            
                            // verify hash value
                            if(!verifyHash(hashBuf,B.header.difficulty))
                            {
                                end_t = clock();
                                cpu_time_used = ((double) (end_t - start_t)) / CLOCKS_PER_SEC;

                                printf("miner nonce_1: %llu finished job in %.5f s\n", ntRes.nonce_1,cpu_time_used);
                                
                                 // stop other miners
                                SOCKET j;
                                memset(ntRes.msg,0,sizeof(ntRes.msg));
                                strcpy(ntRes.msg,"STOP");
                                for (j = 1; j <= max_socket; ++j) {
                                    if (FD_ISSET(j, &master)) {
                                        if (j == socket_listen || j == i)
                                            continue;
                                        else
                                        {
                                            memcpy(response,&ntRes,sizeof(NETWORKRESPONSE));
                                            send(j, response, sizeof(NETWORKRESPONSE), 0);
                                        }
                        
                                    }
                                }
                                createNew = 1;
                                break; // break from for loop

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

                /* stop miners because nonce has been found*/
                SOCKET j;
                memset(ntRes.msg,0,sizeof(ntRes.msg));
                strcpy(ntRes.msg,"STOP");
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

        #ifdef ALLOWSAVE //save binary file in test run
            // write block data to binary file
            FILE *filePtr = NULL;
            char fileName[10] = {0};

            sprintf(fileName,"%d.bin",i);  // create file name
            filePtr = fopen(fileName,"wb");
            if(filePtr == NULL)
            {
                err("main: file open failed");
            }
            fwrite(&B,sizeof(BLOCK),1,filePtr);
            if(fclose(filePtr))
            {
                err("main: file close failed");
            }

            printf("verifying saved block...");
            if(!verifyBlockFromFile(fileName,&B)) // verify written block --> debugging
            {
                printf("valid block!\n");
            }else{
                printf("invalid block!\n");
            }

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

    calculateWalletBalance(0,NUMBER_OF_BLOCKS,&B); // calculate balances for each wallet

    closeNetwork(socket_listen); // clean up and close network before returning

    return 0;
}


/** @brief genKeyPair, generates a public and priavte key pair
 *  @param privBuf, buffer for private key
 *  @param pubBuf, buffer for public key
 *  @return void
 */ 
void genKeyPair(uint8_t *privBuf, uint8_t *pubBuf)
{
    ctx = secp256k1_context_create(
	SECP256K1_CONTEXT_SIGN | SECP256K1_CONTEXT_VERIFY); //secp256k1 context

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

/** @brief parseHexString, converts input string into byte chunks of hash
 *
 * @param  hexStr, pointer to a string of length 64
 * @param  hash, pointer to a buffer of size 32 bytes
 * @return void
 */
void parseHexString(uint8_t* hexStr, uint8_t* hexBuf, size_t strLen)
{
    uint8_t hex[2];
    int j =0,k =0;
    for(int i=0; i<strLen; i++)
    {
        hex[j++] = *(hexStr+i);
        if(j==2) // hexadecimal has two characters
        {
            *(hexBuf + k++) = strtol(hex,NULL,16); // hex string to int
            j = 0;
        }
    }

}
