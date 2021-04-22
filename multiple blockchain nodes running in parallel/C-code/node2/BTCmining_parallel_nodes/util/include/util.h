#ifndef _HEAD_UTIL
#define _HEAD_UTIL

#include <stdio.h>
#include <stdint.h>

// print error message
void 
err(const char * message);
//
void 
printHex(uint8_t * data, size_t dataLen);

#endif //_HEAD_UTIL