#ifndef _HEADER_TRANSACTION
#define _HEADER_TRANSACTION

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>

#include "common.h"
#include "../../crypto/hash.h"
#include "../../util/include/util.h"
#include "../../secp256k1/include/secp256k1.h"


typedef struct keyPair{
    uint8_t private[32];
    uint8_t public[COIN_ADDR_LEN];
} KEYPAIR;

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
static int const txnd_size = sizeof(uint64_t)     // amount size
                    + COIN_ADDR_LEN*2;     // the to and from address size

// generate transaction
TRANSACTION 
genTransaction(KEYPAIR *keyPairs, uint8_t* signKey);
// sign a transaction
void 
signTransaction(TRANSACTION* txn, uint8_t* privKey,secp256k1_context* ctx);
// verify if transaction is valid
int 
verifyTransaction(TRANSACTION txn, secp256k1_context* ctx );
// print transaction
void 
printTXN(TRANSACTION txn);

// create wallet file name from public key
void
walletFileFromHex(uint8_t *hex, char* fileName);

#endif //_HEADER_TRANSACTION



