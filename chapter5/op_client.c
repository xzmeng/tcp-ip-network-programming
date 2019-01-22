#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>

#define BUF_SIZE 1024

void error_handling(char *msg);

int main(int argc, char *argv[]){
    int sock;
    struct sockaddr_in serv_addr;
    int n;
    int len;
    char buf[BUF_SIZE];

    if ( argc != 3 ){
        printf("Usage: %s  <ip address>  <port>\n", argv[0]);
        exit(0);
    }

    memset((void *)&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
    serv_addr.sin_port = htons((short)atoi(argv[2]));

    if ( (sock = socket(PF_INET, SOCK_STREAM, 0)) == -1){
        error_handling("socket()");
    }

    if ( connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) == -1){
        error_handling("connect()");
    } else {
        puts("Connected ...");
    }

    fputs("Operand count: ", stdout);
    //TODO
    

    close(sock);
    
    return 0;
}

void error_handling(char *msg){
    fputs(msg, stderr);
    fputc('\n', stderr);
    exit(1);
}