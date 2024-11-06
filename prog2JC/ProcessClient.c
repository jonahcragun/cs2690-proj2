#include <stdio.h>       // for print functions
#include <stdlib.h>      // for exit() 
// #include <winsock2.h>	 // for Winsock2 functions
// #include <ws2tcpip.h>    // adds support for getaddrinfo & getnameinfo for v4+6 name resolution
// #include <Ws2ipdef.h>    // optional - needed for MS IP Helper
#include "../winsock_wrapper.h"
    
void DisplayFatalErr(char *errMsg); // writes error message before abnormal termination

void ProcessClient(int sock) {
    // receive client message
    const int BUFF_SIZE = 500;
    char rcvStr[BUFF_SIZE] = { 0 };
    char *rcvBuf = rcvStr;
    int rcvLen = 0;
    do {
        rcvLen = recv(sock, rcvBuf, BUFF_SIZE - 1, 0);
        if (rcvLen < 0) {
            DisplayFatalErr("Error in recv");
        }
        else if (rcvLen > BUFF_SIZE) {
            DisplayFatalErr("Buffer overflow at recv");
        }
        else {
            rcvBuf += rcvLen;    
        }
    } while (rcvLen != 0);

    printf("here1\n");
    // echo message back to client     
    int msgLen = strlen(rcvStr);
    int sentBytes = 0;
    do {
    printf("here2\n");
        int bytesSent = send(sock, rcvStr, msgLen, 0);
        if (bytesSent > 0) {
            sentBytes += bytesSent;
        }
        else {
            DisplayFatalErr("send function failed");
        }
    } while (sentBytes < msgLen);

    // close client socket
    if (closesocket(sock) != 0)
        DisplayFatalErr("Error at closesocket");

}
