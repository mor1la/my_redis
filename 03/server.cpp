#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <iostream>
#include <cstring>

static void do_smth(int clientSocket) {
    char rbuf[64] = {};
    printf("READ\n");
    int n = read(clientSocket, rbuf, sizeof(rbuf) - 1);
    printf("client says: %s\n", rbuf);
    char wbuf[] = "hello";
    printf("WRITE\n");
    write(clientSocket, wbuf, strlen(wbuf));
}


int main() {
    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);

    sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(1234);
    serverAddress.sin_addr.s_addr = htonl(INADDR_ANY);
    
    int opt = 1;  // Включаем SO_REUSEADDR
    setsockopt(serverSocket, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
    bind(serverSocket, (const struct sockaddr *)&serverAddress, sizeof(serverAddress));
    listen(serverSocket, SOMAXCONN);

    while(true) {
        sockaddr_in clientAddress;
        socklen_t addrlen = sizeof(clientAddress);
        int clientSocket = accept(serverSocket, (struct sockaddr *)&clientAddress, &addrlen);
        if (clientSocket < 0) {
            printf("Client Socket < 0");
            continue;
        }
        do_smth(clientSocket);
        close(clientSocket);
    }
    close(serverSocket);
    return 0;
}




