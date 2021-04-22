/**
 * @file block.c
 * @author Nakibinge Simon (slemonla13@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2021-04-11
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "../include/block.h"

/*************************** FUNCTION DECLARATION  *******************/

/** @brief verifyBlockFromFile, verifies block saved in binary file
 *         is a valid block
 *
 * @param fileName, name of binary file with saved block
 * @return int, 0 on success, non zero on failure
 */
int verifyBlockFromFile(char *fileName, BLOCK* B)
{
    memset(B,0,sizeof(BLOCK));
    blake3_hasher hasher;                   // hash Initializer
    uint8_t hashBuf[BLAKE3_OUT_LEN] ={0};   // calculated hash buffer

    // read binary file
    FILE* filePtr = NULL;
    filePtr = fopen(fileName,"rb");
    if(filePtr == NULL)
    {
        err("verifyBlockFromFile: file open failed");
    }
    fread(B,sizeof(BLOCK),1,filePtr);
    if(fclose(filePtr))
    {
        err("verifyBlockFromFile: file close failed");
    }

    hashData(&(B->header),sizeof(B->header),hashBuf); // calculate block header hash  first time
    hashData(hashBuf,sizeof(hashBuf),hashBuf);    // calculate block header hash second time

    #ifdef DEBUG
        printf("retrived block header hash");
        printHex(hashBuf,BLAKE3_OUT_LEN);
    #endif

    if(!verifyHash(hashBuf,B->header.difficulty))
    {
        return 0; // valid block
    }
    return -1;  // invalid block
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
    printf("coin base: ");
    printHex(hdr.coinBase,sizeof(hdr.coinBase));
    printf("mining reward: %llu\n",hdr.amount);
}

/**
 * @brief blockFromFile reads a block from file, given its height
 * 
 * @param B buffer to store read block
 * @param height height of block to read
 */
void blockFromFile(BLOCK* B, uint64_t height)
{
    FILE* filePtr = NULL;   // pointer to block file
    char fileName[10] = {0}; // name of saved block file

    sprintf(fileName,"block%llu.bin",height); // create file name
    filePtr = fopen(fileName,"rb");
    if(filePtr == NULL)
    {
        printf("block height: %llu, filename: %s", height,fileName);
        err("calculateWalletBalance: file open failed");
    }
    fread(B,sizeof(BLOCK),1,filePtr);
    if(fclose(filePtr))
    {
        err("calculateWalletBalance: file close failed");
    }

}

void blockToFile(BLOCK* B)
{
      // write block data to binary file
    FILE *filePtr = NULL;
    char fileName[20] = {0};

    sprintf(fileName,"block%d.bin",B->header.height);  // create file name
    filePtr = fopen(fileName,"wb");
    if(filePtr == NULL)
    {
        err("main: file open failed");
    }
    fwrite(B,sizeof(BLOCK),1,filePtr);
    if(fclose(filePtr))
    {
        err("main: file close failed");
    }

    printf("verifying saved block...");
    if(!verifyBlockFromFile(fileName,B)) // verify written block --> debugging
    {
        printf("valid block!\n");
    }else{
        printf("invalid block!\n");
    }
}


/**
 * @brief calculateWalletBalance calculates the wallet balance
 * for an account starting from the block number root to block number height
 * 
 * @param root calculate balance starting from this block
 * @param height calculate balance upto this height
 */
void calculateWalletBalance(uint64_t root, uint64_t height, BLOCK* B)
{
    uint64_t currHeight = root; // start calculating from this block
  
    blake3_hasher hasher;    // hash Initializer
    uint8_t hashBuf[BLAKE3_OUT_LEN] ={0};   // calculated hash buffer

    memset(B,0,sizeof(BLOCK)); // clear block buffer 

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

        blockFromFile(B,currHeight);  //read binary file containing block

        for(int run =0; run<2; run++)
        {
            if(run==0)
            {
                pubKey = B->transactions[0].fromAddress; // calculate balance for this from address
                balNew -= B->transactions[0].amount; 
            }else{
                pubKey   = B->transactions[0].toAddress;   // calculate balance for this to address
                balNew += B->transactions[0].amount; 
            }
            

            /* traverse through all transactions in this block*/        
            for(int j=1; j<B->header.trxCount-1;j++)
            {
                /* calculate balance for from address */
                if(!memcmp(pubKey,B->transactions[j].fromAddress,COIN_ADDR_LEN))
                {
                    balNew -= B->transactions[j].amount; 
                }
                else if(!memcmp(pubKey,B->transactions[j].toAddress,COIN_ADDR_LEN))
                {
                    balNew += B->transactions[j].amount; 
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


void getTransactionFromFile(BLOCK* B, uint64_t txnPointer)
{

    FILE* filePtr = NULL;// pointer to the transaction file in the transaction pool
    uint64_t j =0;
    for(size_t txnNum=txnPointer; txnNum<(txnPointer+B->header.trxCount); txnNum++)
    {
        TRANSACTION txn = {0};
      
        /* get transaction from bin file*/
        char txnFile[20] ={0};
        sprintf(txnFile,"../txnPool/txn%ld.bin",txnNum);
        filePtr = fopen(txnFile,"rb");
        if(filePtr == NULL)
        {
            printf("file name %s",txnFile);
            err("generateRandTxnToFile couln't open file \n");
        }     

        fread(&txn,1,sizeof(TRANSACTION),filePtr);
        B->transactions[j++] = txn;
        fclose(filePtr); // close transaction file
    }
}
