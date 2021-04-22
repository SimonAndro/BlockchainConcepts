

#include "../include/common.h"

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


/** @brief parseHexString, converts input string into byte chunks of hash
 *
 * @param  hexStr, pointer to a string of length 64
 * @param  hash, pointer to a buffer of size 32 bytes
 * @return void
 */
void parseHexString(uint8_t* hexStr, uint8_t* hexBuf, size_t strLen)
{
    char hex[3]={0};
    int j =0,k =0;

    for(int i=0; i<strLen; i++)
    {
        hex[j++] = *(hexStr+i);
        
        if(j==2) // hexadecimal has two characters
        {
            *(hexBuf + k++) = strtol(hex,NULL,16); // hex string to int
            j = 0;
        }
        {

            
        }
    }

}
