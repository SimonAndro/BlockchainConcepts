/*********************************************************************
* Filename:   main.c
* Author:     Nakibinge Simon, slemonla13@gmail.com
* Copyright:
* Details:    Calculating a crypto hash value for a blockchain block data of 1MB
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

/*************************** MACROS     *****************************/
#define ONLINE 1 // uncomment to accept input from console
//#define ALLOWSAVE 1   // uncomment to save block binary file

#define COIN_ADDR_LEN 34

/*************************** DATA TYPES *****************************/
typedef struct Block{                 // defining a block of data in the block chain
    uint64_t chainVersion;            // version of chain
    uint8_t prevHash[BLAKE3_OUT_LEN]; // hash calculated using blake3 hashing algorithm
    uint64_t height;                  // position of block in the blockchain
    uint64_t nonce_1;                 // mining random number
    uint64_t nonce_2;                 // mining random number
    uint64_t difficulty;              // define the number of 0 bits at the begining of the hash value
    uint8_t coinBase[COIN_ADDR_LEN];  // transfer address of bit coin
    uint64_t amount;                  // reward for mining the block
    uint8_t info[910];                // other information here
}Block;

/*************************** FUNCTION DECLARATION  *******************/
int  verifyHash(uint8_t hash[],uint64_t difficulty);
void printHash(uint8_t hash[]);
void parseHashString(uint8_t* hashStr, uint8_t* hash);
int verifyBlockFromFile(char *fileName);
/**
* Main function
*/
int main()
{
    clock_t start_t, end_t;     // to measure execution time
    double cpu_time_used;

    blake3_hasher hasher;                   // hash Initializer
    uint8_t hashBuf[BLAKE3_OUT_LEN] ={0};   // calculated hash buffer

    // create block data
    Block block = {0}; //! must initialize it to zero or else results into random gabbage
                       // that makes the hash change on every run

    block.chainVersion=1;
    block.height=0;

    parseHashString("7E4755E4228610AB7DBD4A65E58B04C493FBAC85144190DF2AB0BF60F21EADD1",block.prevHash);

    block.nonce_1 = 0;
    block.nonce_2 = 0;

    #ifdef ONLINE
        printf("enter difficulty (number of zero bits): ");
        scanf("%llu",&block.difficulty);
        getchar(); // remove new line character left by scanf in the buffer,
                   // otherwise fgets below will misbehave
    #else
        block.difficulty = 8;
    #endif // ONLINE

    strcpy(block.coinBase,"16ftSEQ4ctQFDtVZiUBusQUjRrGhM3JYwe");
    block.amount = 254;

    #ifdef ONLINE
        printf("enter other info: ");
        fgets(block.info,sizeof(block.info),stdin);
    #else
        strcpy(block.info,"this is dummy info");
    #endif // ONLINE

	printf("\nrunning...");

	start_t = clock();
    while(1)  // mining
    {
        // calculate hash value first time
        blake3_hasher_init(&hasher); // initialize hasher
        blake3_hasher_update(&hasher, &block, sizeof(block));
        blake3_hasher_finalize(&hasher, hashBuf, BLAKE3_OUT_LEN);

        // calculate hash second time
        blake3_hasher_init(&hasher); // initialize hasher
        blake3_hasher_update(&hasher, hashBuf, sizeof(hashBuf));
        blake3_hasher_finalize(&hasher, hashBuf, BLAKE3_OUT_LEN);

        // verifyHash hash value
        if(!verifyHash(hashBuf,block.difficulty))
        {
            end_t = clock();
            cpu_time_used = ((double) (end_t - start_t)) / CLOCKS_PER_SEC;

            printf("\nWork done! \n");
            printf("\nDifficulty (zero bits): %d", block.difficulty);
            printf("\nNonce_2 is: %d",block.nonce_2);
            printf("\nNonce_1 is: %d",block.nonce_1);
            printf("\nrun time %.2fs",cpu_time_used);
            printHash(hashBuf);
            break;
        }

        // increment nonce_2
        block.nonce_2++;

    }

    #ifdef ALLOWSAVE //save binary file in test run
        // write block contents to binary file
        FILE* filePtr;
        filePtr = fopen("0.bin","wb");
        fwrite(&block,sizeof(block),1,filePtr);
        fclose(filePtr);

        printf("\nverifying saved block...");
        if(!verifyBlockFromFile("0.bin")) // verify written block --> debugging
        {
            printf("valid block\n");
        }else{
            printf("invalid block\n");
        }
    #endif // ALLOWSAVE

    return 0;
}

/** \brief verifyBlockFromFile, verifies block saved in binary file
 *
 * \param fileName, name of binary file with saved block
 * \return int, 0 on success, non zero on failure
 *
 */

int verifyBlockFromFile(char *fileName)
{
    Block block;  // a single block
    blake3_hasher hasher;                   // hash Initializer
    uint8_t hashBuf[BLAKE3_OUT_LEN] ={0};   // calculated hash buffer

    // read binary file
    FILE* filePtr;
    filePtr = fopen(fileName,"rb");
    fread(&block,sizeof(block),1,filePtr);
    fclose(filePtr);

     // calculate hash value first time
    blake3_hasher_init(&hasher); // initialize hasher
    blake3_hasher_update(&hasher, &block, sizeof(block));
    blake3_hasher_finalize(&hasher, hashBuf, BLAKE3_OUT_LEN);

    // calculate hash second time
    blake3_hasher_init(&hasher); // initialize hasher
    blake3_hasher_update(&hasher, hashBuf, sizeof(hashBuf));
    blake3_hasher_finalize(&hasher, hashBuf, BLAKE3_OUT_LEN);

    printHash(hashBuf);

    if(!verifyHash(hashBuf,block.difficulty))
    {
        return 0; // valid block
    }
    return -1;  // invalid block
}

/*************************** FUNCTION DEFINITIONS  *******************/
/** \brief parseHashString, converts input string into byte chunks of hash
 *
 * \param  hashStr, pointer to a string of length 64
 * \param  hash, pointer to a buffer of size 32 bytes
 * \return void
 *
 */
void parseHashString(uint8_t* hashStr, uint8_t* hash)
{
    uint8_t hex[2];
    int j =0,k =0;
    for(int i=0; i<64; i++)
    {
        hex[j++] = *(hashStr+i);
        if(j==2) // hexadecimal has two characters
        {
            *(hash + k++) = strtol(hex,NULL,16); // hex string to int
            j = 0;
        }
    }

}

/** \brief verifyHash, verifyHash whether the hash meets the difficulty requirement
 *
 * \param hash, is the hash value array
 * \param difficulty,, the difficulty requirement for the hash value
 * \return int, -1 for false and zero for true
 *
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

/** \brief printHash, prints hash value in hexadecimal
 *
 * \param hash, hash value array
 * \return void
 *
 */
void printHash(BYTE hash[])
{
    printf("\nhash value: ");
    for (size_t i = 0; i < BLAKE3_OUT_LEN; i++) { // Print the hash as hexadecimal.
        printf("%02X", hash[i]);
    }
    printf("\n");
}


