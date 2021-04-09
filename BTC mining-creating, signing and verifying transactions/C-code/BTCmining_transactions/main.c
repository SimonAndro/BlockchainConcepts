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
#include "crypto/hash.h"
#include "include/secp256k1.h"
#include "crypto/ripemd160.h"

/*************************** MACROS     *****************************/
#define COIN_ADDR_LEN 33
#define NUMBER_OF_BLOCKS 10

//#define DEBUG     1   // uncomment to analyse function process outputs
#define ALLOWSAVE 1   // uncomment to save block binary file


/*************************** DATA TYPES *****************************/
typedef struct TransactionSig{ // defining a transaction signature
      uint8_t data[72];  // transaction signature
      size_t len;        // length of signature
} TRXSIG;

typedef struct Transaction{  // defining a transaction
    uint8_t fromAddress[COIN_ADDR_LEN];// address to transfer from
    uint8_t toAddress[COIN_ADDR_LEN];  // address to transfer to
    uint64_t amount;        // amount to tranfser
  
    uint8_t trxHash[BLAKE3_OUT_LEN]; // hash calculated using blake3 hashing algorithm
    TRXSIG signature;
}TRANSACTION;

// size of hashable transaction data
int const txnd_size = sizeof(uint64_t)     // amount size
                    + COIN_ADDR_LEN*2;     // the to and from address size

typedef struct BlockHeader{                 // defining a block header
    uint8_t prevHash[BLAKE3_OUT_LEN]; // hash calculated using blake3 hashing algorithm
    uint64_t chainVersion;            // version of chain
    uint64_t height;                  // position of block in the blockchain
    uint64_t nonce_1;                 // mining random number
    uint64_t nonce_2;                 // mining random number
    uint64_t difficulty;              // define the number of 0 bits at the begining of the hash value
    time_t timeStamp;               // time of mining block
    uint64_t trxCount;                // number of transactions in this blocks
    char coinBase[COIN_ADDR_LEN];     // transfer address of bit coin for miner
    uint64_t amount;                  // reward for mining the block
}BLOCKHEADER;

#define MAX_TRANSACTION_PER_BLOCK  (((1048576llu)-sizeof(BLOCKHEADER))/sizeof(TRANSACTION)) // maximum number of transaction in a block

typedef struct Block{       // defining a block of data in the block chain
    BLOCKHEADER header;     // the block header
    TRANSACTION transactions[MAX_TRANSACTION_PER_BLOCK];   //transactions in the block
}BLOCK;

BLOCK B = {0}; //! must initialize it to zero or else results into random gabbage
                // that makes the hash change on every run

typedef struct keyPair{
    uint8_t private[32];
    uint8_t public[33];
} KEYPAIR;

static secp256k1_context *ctx = NULL; // secp256k1 context

/*************************** FUNCTION DECLARATION  *******************/
// calculate data hash
void  
hashData(void* data,size_t dataLen, uint8_t* hashBuf);
// verify hash with difficult
int   
verifyHash(uint8_t hash[],uint64_t difficulty);
// prints hex as a string
void  
printHex(uint8_t* data, size_t dataLen);
// parse string into hex format
void  
parseHexString(uint8_t* hexStr, uint8_t* hexBuf, size_t strLen);
// verify if block from file is valid
int   
verifyBlockFromFile(char *fileName);
// convert to base 58
char*
base58(BYTE *s, int s_size, char *out, int out_size); 
// generate random bytes
void 
genRandomBytes (size_t num_bytes, unsigned char * buff); 
// generate key pairs
void 
genKeyPair(); 
// generate transaction
TRANSACTION 
genTransaction(KEYPAIR *keyPairs, uint8_t* signKey);
// print error message
void 
err(const char * message);
// sign a transaction
void 
signTransaction(TRANSACTION* txn, uint8_t* signKey);
// verify if transaction is valid
int 
verifyTransaction(TRANSACTION txn);
// print transaction
void 
printTXN(TRANSACTION txn);
// print bock header
void 
printBlockHeader(BLOCKHEADER hdr);
// calculate wallet balance
void
calculateWalletBalance(uint64_t root, uint64_t height);
// create wallet file name from public key
void
walletFileFromHex(uint8_t *hex, char* fileName);


/**
* Main function
*/
int main()
{
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

    
    for(int i = 0; i<NUMBER_OF_BLOCKS; i++)    // generate NUMBER_OF_BLOCKS blocks chained in the block chain
    {
        printf("--------------------------Start-----------------------------\n");

        // create block data
        memset(&B,0,sizeof(B));
        B.header.chainVersion = 3; // second version of chain
        B.header.height = i;
        memcpy(B.header.prevHash,hashBuf,sizeof(hashBuf));
        B.header.nonce_1 = 0;
        B.header.nonce_2 = 0;
        B.header.difficulty = 8; // set difficulty to 8 zero bits at beginning of hash value
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

            signTransaction(&Txn,signKey); // signing transaction 

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
            if(verifyTransaction(B.transactions[i]))
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
            hashData(&B.header,sizeof(B.header),hashBuf); // calculate block header hash  first time
            hashData(hashBuf,sizeof(hashBuf),hashBuf);    // calculate block header hash second time

            // verify hash value
            if(!verifyHash(hashBuf,B.header.difficulty))
            {
                end_t = clock();
                cpu_time_used = ((double) (end_t - start_t)) / CLOCKS_PER_SEC;

                printf(" Work done! ...time %.5f s\n",cpu_time_used);
                printf("---------------block header contents------------------\n");
                printBlockHeader(B.header);
                printf("------------------------------------------------------\n");
                break;
            }

            // increment nonce_2
            B.header.nonce_2++;
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
            fwrite(&B,sizeof(B),1,filePtr);
            if(fclose(filePtr))
            {
                err("main: file close failed");
            }

            printf("verifying saved block...");
            if(!verifyBlockFromFile(fileName)) // verify written block --> debugging
            {
                printf("valid block!\n");
            }else{
                printf("invalid block!\n");
            }

        #endif // ALLOWSAVE

        printf("---------------------------End---------------------------\n\n");
    }

    /* print atmost 9 transactions in the last added block*/
    printf("-----------------Transactions in the last block-------------------\n");
    for(int i = 0; i<B.header.trxCount; i++)
    {
        printf("-----------TXN start---------------\n");
        printTXN(B.transactions[i]);
        printf("-----------TXN end-----------------\n");

        if(i==9) break;
    }
    

    calculateWalletBalance(0,NUMBER_OF_BLOCKS); // calculate balances for each wallet

    return 0;
}


/**
 * @brief walletFileFromHex create a wallet filename from public key
 * 
 * @param hex 
 * @param fileName 
 */
void walletFileFromHex(uint8_t *hex, char* fileName)
{
    char walletsDir[] = {"../wallet/"};

    strcat(fileName,walletsDir);

    char hexF[3] = {0};
    for(int sw=0; sw<COIN_ADDR_LEN; sw++)  
    {
        sprintf(hexF,"%02X", hex[sw]);
        strcat(fileName,hexF);
    }
    strcat(fileName,".txt");

}

/**
 * @brief calculateWalletBalance calculates the wallet balance
 * for an account starting from the block number root to block number height
 * 
 * @param root calculate balance starting from this block
 * @param height calculate balance upto this height
 */
void calculateWalletBalance(uint64_t root, uint64_t height)
{
    uint64_t currHeight = root; // start calculating from this block
  
    blake3_hasher hasher;    // hash Initializer
    uint8_t hashBuf[BLAKE3_OUT_LEN] ={0};   // calculated hash buffer

    FILE* filePtr = NULL;   // pointer to block file
    char fileName[10] = {0}; // name of saved block file

    memset(&B,0,sizeof(B)); // clear block buffer 

    FILE* walletPtr = NULL;  // pointer to wallet balances fils
    char walletFile[] = "wallet_balances.txt"; // name of wallet balances file
    uint8_t walletBuff[1024] = {0};  // one line of wallet buffer

    long long int balCurr = 0;  // wallet current balance 
    long long int balNew = 0;  // wallet new balance
    uint8_t* pubKey = NULL;     // wallet public key 


    walletPtr = fopen("wallet_balances.txt","a+"); // open file in appending mode or create one if doesn't exist
    if(walletPtr == NULL)
    {
        printf(" file name: %s",walletFile);
        err("calculateWalletBalance: file open failed");
    }

    for (;currHeight<height;currHeight++)
    {
        sprintf(fileName,"%llu.bin",currHeight); // create file name
    
        /* read binary file containing block */
        filePtr = fopen(fileName,"rb");
        if(filePtr == NULL)
        {
            printf("block height: %llu, filename: %s", currHeight,fileName);
            err("calculateWalletBalance: file open failed");
        }
        fread(&B,sizeof(B),1,filePtr);
        if(fclose(filePtr))
        {
            err("calculateWalletBalance: file close failed");
        }

        for(int run =0; run<2; run++)
        {
            if(run==0)
            {
                pubKey = B.transactions[0].fromAddress; // calculate balance for this from address
                balNew -= B.transactions[0].amount; 
            }else{
                pubKey   = B.transactions[0].toAddress;   // calculate balance for this to address
                balNew += B.transactions[0].amount; 
            }
            

            /* traverse through all transactions in this block*/        
            for(int j=1; j<B.header.trxCount-1;j++)
            {
                /* calculate balance for from address */
                if(!memcmp(pubKey,B.transactions[j].fromAddress,COIN_ADDR_LEN))
                {
                    balNew -= B.transactions[j].amount; 
                }
                else if(!memcmp(pubKey,B.transactions[j].toAddress,COIN_ADDR_LEN))
                {
                    balNew += B.transactions[j].amount; 
                }
            }

            /* create wallet file name for this address */
            

            /* read this wallet balance if it exists*/
            FILE* sWFPtr = NULL;
            char sWFname[100] = {0};
            walletFileFromHex(pubKey,sWFname);
            sWFPtr = fopen(sWFname,"r");
            if(sWFPtr != NULL)
            {
                fscanf(sWFPtr,"%ld",&balCurr); 
                balNew+=balCurr;
                fclose(sWFPtr);
            }
            /* write current balance to this wallet file*/
            sWFPtr = fopen(sWFname,"w");
            fprintf(sWFPtr,"%ld",balNew);
            fclose(sWFPtr);
        }
        
    }
    
}



/** @brief verifyTransaction, verifies whether the transaction is valid
 *  @param txn, transaction to be verifed
 *  @return int, 0 if valid and non-zero if invalid
 */ 
int verifyTransaction(TRANSACTION txn)
{
    /* parse public key into secp256k1_pubkey object */
    secp256k1_pubkey pubkey;
    if(!secp256k1_ec_pubkey_parse(ctx,&pubkey,
        txn.fromAddress,
        sizeof(txn.fromAddress)))
    {
        err("couldn't parse public key");
    }

    /* parse signture into secp256k1_ecdsa_signature object */
    secp256k1_ecdsa_signature sig;
    if(!secp256k1_ecdsa_signature_parse_der(ctx,&sig,
        txn.signature.data,txn.signature.len))
    {
        err("couldn't parse signature");
    }

    /* verify transaction signature */
    if(!secp256k1_ecdsa_verify(ctx, &sig, txn.trxHash, &pubkey)) // invalid signature
    {
        return -1;
    }
    
    // verify user has enough balance 

    return 0; // valid transaction
}

/** @brief signTransaction signs a transaction using senders private key
 * 
 * @param txn, transaction to sign
 * @param privKey, private key to use when signing the transction
 * @return void
 */ 
void signTransaction(TRANSACTION* txn, uint8_t* privKey)
{
    int res;  // function call response

    hashData(&txn,txnd_size,txn->trxHash);      // hashing the transaction

    #ifdef DEBUG
        printf("\ntransaction hash value: ");
        printHex(txn->trxHash,BLAKE3_OUT_LEN);
    #endif
    
    /* signing the transaction */
    secp256k1_ecdsa_signature sig;   
    res = secp256k1_ecdsa_sign(ctx, &sig, txn->trxHash, privKey, NULL, NULL);
    if(!res){ err("Can't sign"); }   

    /* serialization of the signature */
    uint8_t der[72];
    size_t len = sizeof(der);
    res = secp256k1_ecdsa_signature_serialize_der(ctx, der, &len, &sig);
    if(!res){ err("Can't serialize the signature"); }

    /* copy sigature into transaction object*/
    txn->signature.len = len;
    memcpy(txn->signature.data,der,len);

    #ifdef DEBUG
        printf("Signature: ");
        printHex(txn->signature.data, txn->signature.len);
        printf("Signature length %d: ",txn->signature.len);
    #endif
} 


/** @brief genTransaction generations a random transaction
 * 
 * @param keyPairs, an array containing key pairs
 * @param signKey, buffer to store private key that corresponds 
 *        to the senders public key
 * @return TRANSACTION, generated transaction
 */ 
TRANSACTION genTransaction(KEYPAIR *keyPairs, uint8_t* signKey)
{
    TRANSACTION Txn;
    int toAddress = rand()%10; // random address to send to
    int frAddress = rand()%10; // random address to send from

    while(frAddress == toAddress) // sender can't be same as receiver
    {
        frAddress = rand()%10;
    }
    memcpy(signKey,keyPairs[frAddress].private,32);

    memcpy(Txn.fromAddress,keyPairs[frAddress].public,33);
    memcpy(Txn.toAddress,keyPairs[toAddress].public,33);
    Txn.amount = 1+rand(); // random ammount to send

    return Txn;
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

/** @brief verifyBlockFromFile, verifies block saved in binary file
 *         is a valid block
 *
 * @param fileName, name of binary file with saved block
 * @return int, 0 on success, non zero on failure
 */
int verifyBlockFromFile(char *fileName)
{
    memset(&B,0,sizeof(B));
    blake3_hasher hasher;                   // hash Initializer
    uint8_t hashBuf[BLAKE3_OUT_LEN] ={0};   // calculated hash buffer

    // read binary file
    FILE* filePtr = NULL;
    filePtr = fopen(fileName,"rb");
    if(filePtr == NULL)
    {
        err("verifyBlockFromFile: file open failed");
    }
    fread(&B,sizeof(B),1,filePtr);
    if(fclose(filePtr))
    {
        err("verifyBlockFromFile: file close failed");
    }

    hashData(&B.header,sizeof(B.header),hashBuf); // calculate block header hash  first time
    hashData(hashBuf,sizeof(hashBuf),hashBuf);    // calculate block header hash second time

    #ifdef DEBUG
        printf("retrived block header hash");
        printHex(hashBuf,BLAKE3_OUT_LEN);
    #endif

    if(!verifyHash(hashBuf,B.header.difficulty))
    {
        return 0; // valid block
    }
    return -1;  // invalid block
}

/*************************** FUNCTION DEFINITIONS  *******************/
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

/** @brief verify, verify whether the hexBuf meets the difficulty requirement
 *
 * @param hash, is the hash value array
 * @param difficulty,, the difficulty requirement for the hash value
 * @return int, -1 for false and zero for true
 */
int verifyHash(uint8_t hash[],uint64_t difficulty)
{
    int i = 0;
    uint64_t count=0;

    if(difficulty == 0) return 0;

    while(1)
    {
        for(int j =7; j>=0; j--) // evaluate one byte for number of zero bits
        {
            if((hash[i] & (uint8_t)pow(2,j))!=0)
            {
                return -1;
            }else{
                count++;         // found a zero bit
            }

            if(count==difficulty) // satisfies number of zero bits
            {
                return 0;
            }
        }
        i++;

    }
    return -1;
}

/** @brief hashData, using blake3 to generate 256 hash for data
 * 
 * @param data, pointer data to be hashed
 * @param hashBuf, pointer to where to store hash value
 */ 
void hashData(void* data, size_t dataLen, uint8_t* hashBuf)
{
    blake3_hasher hasher;         // hash Initializer
    blake3_hasher_init(&hasher); // initialize hasher
    blake3_hasher_update(&hasher, data, dataLen);
    blake3_hasher_finalize(&hasher, hashBuf, BLAKE3_OUT_LEN);
}

/** @brief printHex prints hash value in hexadecimal
 *
 * @param hash hash value array
 * @return void
 */
void printHex(uint8_t * data, size_t dataLen)
{
    for (size_t i = 0; i < dataLen; i++) { // Print the hash as hexadecimal.
        printf("%02X", data[i]);
    }
    printf("\n");
}

/** @brief printTXN prints out transaction struct
 *  
 * @param txn transaction to be print out
 * @return void
 */ 
void printTXN(TRANSACTION txn)
{
    printf("\n\n");
    printf("Txn from address: ");
    printHex(txn.fromAddress,sizeof(txn.fromAddress));
    printf("Txn to   address: ");
    printHex(txn.toAddress,sizeof(txn.toAddress));
    printf("Txn amnt: %llu\n",txn.amount);
    printf("Txn hash: ");
    printHex(txn.trxHash,sizeof(txn.trxHash));
    printf("Txn sign: ");
    printHex(txn.signature.data,txn.signature.len);
    printf("\n\n");
}

/** @brief printBlockHeader prints contents of the header of a block
 * 
 * @param hdr header of a block
 * @return void
 */ 
void printBlockHeader(BLOCKHEADER hdr){
    printf("previous hash: ");
    printHex(hdr.prevHash,sizeof(hdr.prevHash));
    printf("chain version: %llu\n",hdr.chainVersion);
    printf("block height: %llu\n",hdr.height);
    printf("nonce_1: %llu\n",hdr.nonce_1);
    printf("nonce_2: %llu\n",hdr.nonce_2);
    printf("difficulty: %llu\n",hdr.difficulty);
    printf("timeStamp: %llu\n",hdr.timeStamp);
    printf("transactions in block: %llu\n",hdr.trxCount);
    printf("coin base: %s\n",hdr.coinBase);
    printf("mining reward: %llu\n",hdr.amount);
}

/** @brief err prints error and hangs forever
 * 
 * @param message error message to print out
 * @return void
 */ 
void err(const char * message){
    printf("ERROR: %s\r\n", message);
    while(1);
}

