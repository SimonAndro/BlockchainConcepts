
#include <stdio.h>
#include <string.h>
#include <time.h>

#include "blockchain/include/block.h"
#include "network/include/network.h"

//#define DEBUG 1

BLOCK B = {0}; //! must initialize it to zero or else results into random gabbage
                // that makes the hash change on every run

#if defined(_WIN32)
#include <conio.h>
#endif


/**
 * @brief Main function
 * 
 * @param argc 
 * @param argv 
 * @return int 
 */
int main(int argc, char const *argv[])
{
    
#if defined(_WIN32)
    WSADATA d;
    if (WSAStartup(MAKEWORD(2, 2), &d)) {
        fprintf(stderr, "Failed to initialize.\n");
        return 1;
    }
#endif

    if (argc < 3) {
        fprintf(stderr, "usage: miner hostname port\n");
        return 1;
    }

    printf("Configuring remote address...\n");
    struct addrinfo hints;
    memset(&hints, 0, sizeof(hints));
    hints.ai_socktype = SOCK_STREAM;
    struct addrinfo *peer_address;
    if (getaddrinfo(argv[1], argv[2], &hints, &peer_address)) {
        fprintf(stderr, "getaddrinfo() failed. (%d)\n", GETSOCKETERRNO());
        return 1;
    }


    printf("Remote address is: ");
    char address_buffer[100];
    char service_buffer[100];
    getnameinfo(peer_address->ai_addr, peer_address->ai_addrlen,
            address_buffer, sizeof(address_buffer),
            service_buffer, sizeof(service_buffer),
            NI_NUMERICHOST);
    printf("%s %s\n", address_buffer, service_buffer);


    printf("Creating socket...\n");
    SOCKET socket_peer;
    socket_peer = socket(peer_address->ai_family,
            peer_address->ai_socktype, peer_address->ai_protocol);
    if (!ISVALIDSOCKET(socket_peer)) {
        fprintf(stderr, "socket() failed. (%d)\n", GETSOCKETERRNO());
        return 1;
    }


    printf("Connecting...\n");
    if (connect(socket_peer,
                peer_address->ai_addr, peer_address->ai_addrlen)) {
        fprintf(stderr, "connect() failed. (%d)\n", GETSOCKETERRNO());
        return 1;
    }
    freeaddrinfo(peer_address);

    printf("Connected.\n");

    NETWORKRESPONSE ntRes ={0};   // network response object
    char response[1024] ={0}; // reponse to the client(bytes)

    int isClosed = 0;   // is connection closed?

    while(1 && !isClosed){ 
        printf("----Waiting for new mining job...------\n");

        /* request for job from server */
        memset(ntRes.msg,0,sizeof(ntRes.msg)); 
        strcpy(ntRes.msg,"JOB");
        memcpy(response,&ntRes,sizeof(NETWORKRESPONSE));
        int bytes_sent = send(socket_peer, response, sizeof(NETWORKRESPONSE), 0);

    #ifdef DEBUG
        printf("Sent %d bytes.\n", bytes_sent);
    #endif

        uint8_t headBuf[4096];
        int bytes_received = recv(socket_peer, headBuf, sizeof(BLOCKHEADER), MSG_WAITALL);
        if (bytes_received < 1) {
            fprintf(stderr, "recv() failed. (%d)\n", GETSOCKETERRNO());
            return 1;
        }

        BLOCKHEADER bHeader;
        memcpy(&bHeader,headBuf,bytes_received); // copy bytes to bHeader

        //!todo: first validate block
    
        printf("\n-----------------received block header contents-----------------\n");
        printBlockHeader(bHeader);
        
        clock_t start_t, end_t;     // to measure execution time
        double cpu_time_used;

        uint8_t hashBuf[BLAKE3_OUT_LEN] ={0}; // store hash value
        bHeader.nonce_2 = 0; // start from nonce_2 = 0

        printf("mining...\n");
        while(1) {

            fd_set reads;
            FD_ZERO(&reads);
            FD_SET(socket_peer, &reads);

            struct timeval timeout;
            timeout.tv_sec = 0;
            timeout.tv_usec = 0;

            if (select(socket_peer+1, &reads, 0, 0, &timeout) < 0) {
                fprintf(stderr, "select() failed. (%d)\n", GETSOCKETERRNO());
                return 1;
            }

            if (FD_ISSET(socket_peer, &reads)) {

                int bytes_received = recv(socket_peer, response, sizeof(NETWORKRESPONSE), MSG_WAITALL);
                if (bytes_received < 1) {
                    printf("Connection closed by peer.\n");
                    isClosed = 1;
                    break;
                }

                memcpy(&ntRes,response,sizeof(NETWORKRESPONSE));

                if(!strcmp(ntRes.msg,"STOP"))
                {
                    printf("----work terminated by server---\n");
                    break; // server sent a stop command
                }
            }

            // mining
            hashData(&bHeader,sizeof(bHeader),hashBuf); // calculate block header hash  first time
            hashData(hashBuf,sizeof(hashBuf),hashBuf);    // calculate block header hash second time

            // verify hash value
            if(!verifyHash(hashBuf,bHeader.difficulty))
            {
                // inform server about finished work
                memset(ntRes.msg,0,sizeof(ntRes.msg)); 
                strcpy(ntRes.msg,"NONCE");
                ntRes.nonce_1 = bHeader.nonce_1;
                ntRes.nonce_2 = bHeader.nonce_2;

                memcpy(response,&ntRes,sizeof(NETWORKRESPONSE));

                int bytes_sent = send(socket_peer, response, sizeof(NETWORKRESPONSE), 0);

                end_t = clock();
                cpu_time_used = ((double) (end_t - start_t)) / CLOCKS_PER_SEC;

                printf(" Work done! ...time %.5f s\n",cpu_time_used);
                printf("---------------block header contents------------------\n");
                printBlockHeader(bHeader);
                printf("------------------------------------------------------\n");
                break;
            }

            bHeader.nonce_2++;        // increment nonce_2
        
        } //end while(1) inner
    } //end while(1) outer

    printf("Closing socket...\n");
    CLOSESOCKET(socket_peer);

#if defined(_WIN32)
    WSACleanup();
#endif

    printf("Finished.\n");
    
    return 0;
}
