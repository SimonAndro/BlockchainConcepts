
#ifndef _HEAD_COMMON
#define _HEAD_COMMON

#include <stdlib.h>
#include <stdio.h>
#include "../../crypto/hash.h"

#define COIN_ADDR_LEN 33

// calculate data hash
void  
hashData(void* data,size_t dataLen, uint8_t* hashBuf);

// parse string into hex format
void  
parseHexString(uint8_t* hexStr, uint8_t* hexBuf, size_t strLen);

#endif //_HEAD_COMMON