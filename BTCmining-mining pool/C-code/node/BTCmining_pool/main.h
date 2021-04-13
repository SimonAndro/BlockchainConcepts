#ifndef _HEAD_MAIN
#define _HEAD_MAIN

#include <stdint.h>

// parse string into hex format
void  
parseHexString(uint8_t* hexStr, uint8_t* hexBuf, size_t strLen);
// convert to base 58
char*
base58(uint8_t *s, int s_size, char *out, int out_size); 
// generate random bytes
void 
genRandomBytes (size_t num_bytes, unsigned char * buff); 
// generate key pairs
void 
genKeyPair(); 

#endif //_HEAD_MAIN