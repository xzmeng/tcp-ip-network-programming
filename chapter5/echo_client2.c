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
    }

    while (1){
        fputs("Input message(Q/q to quit): ", stdout);
        fgets(buf, BUF_SIZE, stdin);
        if ( !strcmp(buf, "q\n") || !strcmp(buf, "Q\n") )
            break;
        len = strlen(buf);
        if ( len != write(sock, buf, len) ){
            error_handling("write");
        }
        
        int recv_len = 0;

        while ( recv_len < len ){
            n = read(sock, &buf[recv_len], BUF_SIZE - 1 - recv_len);
            if ( n == -1 ){
                error_handling("read");
            }
            recv_len += n;
        }

        buf[n] = 0;
        printf("Message from server: %s", buf);
    }
    close(sock);
    
    return 0;
}

void error_handling(char *msg){
    fputs(msg, stderr);
    fputc('\n', stderr);
    exit(1);
}