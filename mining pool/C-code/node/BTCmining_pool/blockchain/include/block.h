
#ifndef _HEAD_BLOCK
#define _HEAD_BLOCK

#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <math.h>
#include <time.h>

#include "common.h"
#include "transaction.h"
#include "../../crypto/hash.h"
#include "../../util/include/util.h"


/*************************** DATA TYPES *****************************/

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

/*************************** FUNCTION DECLARATION  *******************/
// verify hash with difficult
int   
verifyHash(uint8_t hash[],uint64_t difficulty);
// verify if block from file is valid
int   
verifyBlockFromFile(char *fileName, BLOCK *B);
// print bock header
void 
printBlockHeader(BLOCKHEADER hdr);
// calculate wallet balance
void
calculateWalletBalance(uint64_t root, uint64_t height, BLOCK* B);

#endif //_HEAD_BLOCK
