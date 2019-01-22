#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

void error_handling(char *msg);

int main(void){
    char *filename = "data.txt";
    char buf[1024] = "HELLO,WORLD!";
    int fd;
    int n;
    if( (fd = open(filename, O_CREAT | O_RDWR | O_TRUNC)) == -1){
        error_handling("open() error");
    }
    if( (n = write(fd, buf, strlen(buf)) ) != strlen(buf)){
        error_handling("write() error");
    }
    close(fd);

    exit(0);
}

void error_handling(char *msg){
    fputs(msg, stderr);
    fputc('\n', stderr);
    exit(1);
}