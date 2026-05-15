#include "toralizer.h"

Socks4Request *createSocks4Request(
    const char *destinationIp,
    const int destinationPort
) {

    Socks4Request *request;

    request = malloc(REQUEST_SIZE);

    request->versionNumber = 4;
    request->commandCode = 1;

    request->destinationPort = htons(destinationPort);

    request->destinationIp = inet_addr(destinationIp);

    strncpy(request->userId, PROXY_USER_ID, 8);

    return request;
}

int main(int argc, char *argv[]) {

    char *targetHost;

    int targetPort;

    int proxySocket;

    struct sockaddr_in proxyAddress;

    Socks4Request *connectionRequest;

    Socks4Response *proxyResponse;

    char responseBuffer[RESPONSE_SIZE];

    int connectionSuccessful;

    if(argc < 3) {

        fprintf(
            stderr,
            "Usage: %s <host> <port>",
            argv[0]
        );

        return -1;
    }

    targetHost = argv[1];

    targetPort = atoi(argv[2]);

    proxySocket = socket(AF_INET, SOCK_STREAM, 0);

    if(proxySocket < 0) {

        perror("socket");

        return -1;
    }

    proxyAddress.sin_family = AF_INET;

    proxyAddress.sin_port = htons(PROXY_PORT);

    proxyAddress.sin_addr.s_addr = inet_addr(PROXY_IP);

    if(connect(
        proxySocket,
        (struct sockaddr *) &proxyAddress,
        sizeof(proxyAddress)
    )) {

        perror("Connection Error");

        return -1;
    }

    printf("Connected to proxy!\n");

    connectionRequest = createSocks4Request(
        targetHost,
        targetPort
    );

    write(
        proxySocket,
        connectionRequest,
        REQUEST_SIZE
    );

    memset(
        responseBuffer,
        0,
        RESPONSE_SIZE
    );

    if(read(
        proxySocket,
        responseBuffer,
        RESPONSE_SIZE
    ) < 1) {

        perror("Read Error");

        free(connectionRequest);

        close(proxySocket);

        return -1;
    }

    proxyResponse = (Socks4Response *) responseBuffer;

    connectionSuccessful =
        (proxyResponse->statusCode == 90);

    if(!connectionSuccessful) {

        fprintf(
            stderr,
            "Unable to traverse the proxy, "
            "error code: %d\n",
            proxyResponse->statusCode
        );

        free(connectionRequest);

        close(proxySocket);

        return -1;
    }

    printf(
        "Successfully connected through the proxy to: "
        "%s:%d\n",
        targetHost,
        targetPort
    );

    free(connectionRequest);

    close(proxySocket);

    return 0;
}