#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <dlfcn.h>

#define PROXY_IP "127.0.0.1"
#define PROXY_PORT 9050
#define PROXY_USER_ID "toraliz"

#define REQUEST_SIZE sizeof(struct socks4_request)
#define RESPONSE_SIZE sizeof(struct socks4_response)

typedef unsigned char uint8;
typedef unsigned short int uint16;
typedef unsigned int uint32;

/*
    SOCKS4 Request Packet Structure

    ------------------------------------------------
    Field           Size (bytes)
    ------------------------------------------------
    Version Number          1
    Command Code            1
    Destination Port        2
    Destination IP          4
    User ID                 variable
    Null Terminator         1
*/

struct socks4_request {
    uint8 versionNumber;
    uint8 commandCode;
    uint16 destinationPort;
    uint32 destinationIp;
    unsigned char userId[8];
};

typedef struct socks4_request Socks4Request;

/*
    SOCKS4 Response Packet Structure

    ------------------------------------------------
    Field           Size (bytes)
    ------------------------------------------------
    Version Number          1
    Status Code             1
    Destination Port        2
    Destination IP          4
*/

struct socks4_response {
    uint8 versionNumber;
    uint8 statusCode;
    uint16 destinationPort;
    uint32 destinationIp;
};

typedef struct socks4_response Socks4Response;

int main(int argc, char **argv);

Socks4Request *createSocks4Request(
    const char *destinationIp,
    const int destinationPort
);