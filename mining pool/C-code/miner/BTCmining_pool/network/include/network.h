/*network.h*/
#ifndef _HEAD_NETWORK
#define _HEAD_NETWORK

#if defined(_WIN32)

    #ifndef _WIN32_WINNT
        #define _WIN32_WINNT 0x0600
    #endif
    #include <winsock2.h>
    #include <ws2tcpip.h>
    #pragma comment(lib, "ws2_32.lib")

#else

    #include <sys/types.h>
    #include <sys/socket.h>
    #include <netinet/in.h>
    #include <arpa/inet.h>
    #include <netdb.h>
    #include <unistd.h>
    #include <errno.h>
#endif

#if defined(_WIN32)
    #define ISVALIDSOCKET(s) ((s) != INVALID_SOCKET)
    #define CLOSESOCKET(s) closesocket(s)
    #define GETSOCKETERRNO() (WSAGetLastError())

#else
    #define ISVALIDSOCKET(s) ((s) >= 0)
    #define CLOSESOCKET(s) close(s)
    #define SOCKET int
    #define GETSOCKETERRNO() (errno)
#endif

#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>

//
SOCKET 
initializeNetwork();
//
int
closeNetwork(SOCKET socket);

typedef struct NetworkResponse{ // define network response between node and miner
    char msg[32]; // message
    uint64_t nonce_1;// nonce 1
    uint64_t nonce_2;//nonce 2
}NETWORKRESPONSE;

#endif //_HEAD_NETWORK