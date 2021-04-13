
#ifndef _HEAD_COMMON
#define _HEAD_COMMON

#include "../../crypto/hash.h"

#define COIN_ADDR_LEN 33

// calculate data hash
void  
hashData(void* data,size_t dataLen, uint8_t* hashBuf);

#endif //_HEAD_COMMON