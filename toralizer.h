#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <dlfcn.h>

/*
    Function Used:
    1. socket()
    2. connect()
    3. close()
    4. htons()
    5. inet_addr()
*/

#define PROXY "127.0.0.1"
#define PROXYPORT 9050
#define USERNAME "toraliz"
#define reqsize sizeof(struct proxy_request)
#define ressize sizeof(struct proxy_response)

typedef unsigned char int8;
typedef unsigned short int int16; // You can skip the int here if you want, as by default short expects an int after it
typedef unsigned int int32;

/*
    Field	    Description	            Size (bytes)
    ------------------------------------------------
    VN	        Version Number	        1
    CD	        Command Code	        1
    DSTPORT	    Destination Port	    2
    DSTIP	    Destination IP Address	4
    USERID	    User ID	                variable
    NULL	    Null Terminator	        1
*/

struct proxy_request
{
    int8 vn;
    int8 cd;
    int16 dstport;
    int32 dstip;
    unsigned char userid[8];
};

typedef struct proxy_request Req;

/*
    Field	    Description	            Size (bytes)
    ------------------------------------------------
    VN	        Version Number	        1
    CD	        Command Code	        1
    DSTPORT	    Destination Port	    2
    DSTIP	    Destination IP Address	4
*/

struct proxy_response
{
    int8 vn;
    int8 cd;
    int16 _;
    int32 __;
};

typedef struct proxy_response Res;

int main(int, char**);
Req *request(const char*, const int);
// Req *request(const char* dstip, const int dstport)