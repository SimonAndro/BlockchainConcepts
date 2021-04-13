

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