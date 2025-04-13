#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <iostream>
#include <cstring>

void do_smth(int clientSocket) {
    char wbuf[] = "hello";
    write(clientSocket, wbuf, strlen(wbuf));
    char rbuf[64] = {};
    int n = read(clientSocket, rbuf, sizeof(rbuf) - 1);
    printf("%s", rbuf);
}


int main() {
    int clientSocket = socket(AF_INET, SOCK_STREAM, 0);

    sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(1234);
    serverAddress.sin_addr.s_addr = htonl(INADDR_LOOPBACK); 


    int rv = connect(clientSocket, (const struct sockaddr *)&serverAddress, sizeof(serverAddress));
    
    char wbuf[] = "hello";
    write(clientSocket, wbuf, strlen(wbuf));
    printf("WRITE\n");
    char rbuf[64] = {};
    int n = read(clientSocket, rbuf, sizeof(rbuf) - 1);
    printf("READ\n");
    printf("server says: %s\n", rbuf);
    printf("CLOSE\n");   
    close(clientSocket);

    return 0;
}



// bind(serverSocket, address);
// listen(fd);
// while(True){
//     conn_fd = accept(fd);
//     //do
//     close;
// }



