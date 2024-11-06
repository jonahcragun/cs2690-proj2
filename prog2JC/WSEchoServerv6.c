// CS 2690 Program 2 
// Simple Windows Sockets Echo Server (IPv6)
// Jonah Cragun cs2690-001
// macOS Sonoma 14.6.1
//
// Client usage: WSEchoClientv6 <server IPv6 address> <server port> <"message to echo">
// Companion client is WSEchoClientv6
// Server usage: WSEchoServerv6 <server port>
//
// This program is coded in conventional C programming style, with the 
// exception of the C++ style comments.
//
// I declare that the following source code was written by me or provided
// by the instructor. I understand that copying source code from any other 
// source or posting solutions to programming assignments (code) on public
// Internet sites constitutes cheating, and that I will receive a zero 
// on this project if I violate this policy.
// ----------------------------------------------------------------------------

// Minimum required header files for C Winsock program
#include <stdio.h>       // for print functions
#include <stdlib.h>      // for exit() 
// #include <winsock2.h>	 // for Winsock2 functions
// #include <ws2tcpip.h>    // adds support for getaddrinfo & getnameinfo for v4+6 name resolution
// #include <Ws2ipdef.h>    // optional - needed for MS IP Helper
#include "../winsock_wrapper.h"

// #define ALL required constants HERE, not inline 
// #define is a macro, don't terminate with ';'  For example...
#define RCVBUFSIZ 50

// declare any functions located in other .c files here
void DisplayFatalErr(char *errMsg); // writes error message before abnormal termination
void ProcessClient(int sock); // receives and echos message from client

int main(int argc, char *argv[]) {
 	// Declare ALL variables and structures for main() HERE, NOT INLINE (including the following...)
	WSADATA wsaData;                // contains details about WinSock DLL implementation
    struct sockaddr_in6 serverInfo = { 0 };	// standard IPv6 structure that holds server socket info
	unsigned short serverPort;

	// Verify correct number of command line arguments, else do the following:
    if (argc > 2) {
	    fprintf(stderr, "Server usage: WSEchoServerv6 <server port>");
	    exit(1);	  // ...and terminate with abnormal termination code (1)
    }
    else if (argc < 2) {
	// Retrieve the command line arguments. (Sanity checks not required, but port and IP addr will need
	// to be converted from char to int.  See slides 11-15 & 12-3 for details.)

    serverPort = 5001;

    }
    else {
	// Retrieve the command line arguments. (Sanity checks not required, but port and IP addr will need
	// to be converted from char to int.  See slides 11-15 & 12-3 for details.)

    serverPort = atoi(argv[1]);

    }
	

	// Initialize Winsock 2.0 DLL. Returns 0 if ok. If this fails, fprint error message to stderr as above & exit(1).  
    if (WSAStartup(MAKEWORD(2, 0), &wsaData) != 0) {
        fprintf(stderr, "Unable to load WSA Startup\n");
        exit(2);	  // ...and terminate with abnormal termination code (2)
    }

    // create socket
    int sock;
    sock = socket(AF_INET6, SOCK_STREAM, IPPROTO_TCP); 

    if (sock == INVALID_SOCKET) {
        DisplayFatalErr("socket() function failed.");
    }


    // Load server info into sockaddr_in6
    serverInfo.sin6_family = AF_INET6;
    serverInfo.sin6_port = htons(serverPort);
    serverInfo.sin6_addr = in6addr_any;

    // bind server socket to serverInfo
    if (bind(sock, (struct sockaddr *) &serverInfo, sizeof(serverInfo)) != 0) {
        DisplayFatalErr("bind() function failed.");
    };

    // set listen and max simultaneous client connection requests allowed
    if (listen(sock, 5) < 0) {
        DisplayFatalErr("listen() function failed.");
    };


    struct sockaddr_in6 emptyInfo = { 0 };
    unsigned long sockaddr_len = sizeof(emptyInfo);
    for (;;) {
        // display connection meesage
        printf("Jonah's Ipv6 echo server is ready for client connection...\n");


        // accept connection from client
        int connected = accept(sock, (struct sockaddr*)&emptyInfo, (socklen_t*)&sockaddr_len);
        if (connect < 0) {
            DisplayFatalErr("listen() function failed.");
        }

        char str_addr[20];
        inet_ntop(AF_INET, &(emptyInfo.sin6_addr), str_addr, 20);
        printf("processing the client at %s, client port %d, server port %d\n", str_addr, ntohs(emptyInfo.sin6_port), serverPort);

        // receive and echo client message
        ProcessClient(connected);

    }
}
