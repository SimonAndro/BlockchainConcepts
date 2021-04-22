/**
 * @file transaction.c
 * @author Nakibinge Simon (slemonla13@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2021-04-11
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "../include/transaction.h"

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

/** @brief verifyTransaction, verifies whether the transaction is valid
 *  @param txn, transaction to be verifed
 *  @return int, 0 if valid and non-zero if invalid
 */ 
int verifyTransaction(TRANSACTION txn, secp256k1_context* ctx )
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
void signTransaction(TRANSACTION* txn, uint8_t* privKey,secp256k1_context* ctx)
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


