#include <stdlib.h>
#include <stdio.h>

#define BUF_SIZE 64

void error_handling(char *msg);

int main(int argc, char *argv[]){
    FILE *src, *dst;
    int n;
    char buf[BUF_SIZE];

    if ( argc != 3){
        printf("Usage: %s  <src>  <dst>\n", argv[0]);
        exit(0);
    }

    if ( ( src = fopen(argv[1], "r") ) == NULL){
        error_handling("open src");
    }

    if ( ( dst = fopen(argv[2], "w") ) == NULL){
        error_handling("open dst");
    }

    //TODO

    return 0;

}

void error_handling(char *msg){
    fputs(msg, stderr);
    fputc('\n', stderr);
    exit(1);
}