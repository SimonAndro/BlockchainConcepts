

#include "../include/util.h"

/** @brief err prints error and hangs forever
 * 
 * @param message error message to print out
 * @return void
 */ 
void err(const char * message){
    printf("ERROR: %s\r\n", message);
    while(1);
}

/** @brief printHex prints hash value in hexadecimal
 *
 * @param hash hash value array
 * @return void
 */
void printHex(uint8_t * data, size_t dataLen)
{
    for (size_t i = 0; i < dataLen; i++) { // Print the hash as hexadecimal.
        printf("%02X", data[i]);
    }
    printf("\n");
}