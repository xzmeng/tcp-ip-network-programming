#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <string.h>


#define BUF_SIZE 1024

void error_handling(char *msg);

int main(int argc, char *argv[]){
    int serv_sock, clnt_sock;
    struct sockaddr_in serv_addr, clnt_addr;
    int n;
    char buf[BUF_SIZE] = "hello,world!";
    int clnt_addr_len;

    if ( argc != 2 ){
        printf("Usage: %s  <port>\n", argv[0]);
        exit(0);
    }

    if ( (serv_sock = socket(PF_INET, SOCK_STREAM, 0)) == -1 ){
        error_handling("socket()");
    }
    memset((void *)&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons((short)atoi(argv[1]));
    
    if ( bind(serv_sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) == -1){
        error_handling("bind");
    }

    if ( listen(serv_sock, 5) == -1 ){
        error_handling("listen");
    }

    for (int i = 0; i < 5; ++ i){
        clnt_sock = accept(serv_sock, (struct sockaddr *)&clnt_addr, &clnt_addr_len);
        if ( clnt_sock == -1 ){
            error_handling("accept()");
        }
        

        printf("Connected from ...\n"); // TODO
        
        while ( (n = read(clnt_sock, buf, BUF_SIZE)) > 0 ){
            if ( write(clnt_sock ,buf, n) != n){
                error_handling("write()");
            }
        }
        if ( n < 0 ){
            error_handling("read");
        }

        close(clnt_sock);
    }
    close(serv_sock);
    exit(0);

}

void error_handling(char *msg){
    fputs(msg, stderr);
    fputc('\n', stderr);
    exit(1);
}