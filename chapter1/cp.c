#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>


#define BUF_SIZE 64

void error_handling(char *msg);

int main(int argc, char *argv[]){
    int srcfd, dstfd;
    int n;
    char buf[BUF_SIZE];

    if ( argc != 3 ){
        printf("usage: %s <src> <dst>\n", argv[0]);
        exit(0);
    }

    if ( (srcfd = open(argv[1], O_RDONLY) ) == -1 ){
        error_handling("open src error");
    }

    if ( (dstfd = open(argv[2], O_WRONLY | O_TRUNC | O_CREAT, S_IRWXU) ) == -1){
        error_handling("open dst error");
    }

    while ( ( n = read(srcfd, buf, BUF_SIZE) ) > 0){
        if ( n != write(dstfd, buf, n) ){
            error_handling("write error");
        }
    }
    if ( n == -1){
        error_handling("read error");
    }

    close(srcfd);
    close(dstfd);
    return 0;

}

void error_handling(char *msg){
    fputs(msg, stderr);
    fputc('\n', stderr);
    exit(1);
}