#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

void error_handling(char *msg);

int main(void){
    char *filename = "data.txt";
    char buf[1024];
    int fd;
    int n;
    
    if( (fd = open(filename, O_RDONLY)) == -1){
        error_handling("open() error");
    }

    if( (n = read(fd, buf, sizeof(buf))) == -1){
        error_handling("read() error");
    }
    buf[n] = 0;
    printf("%s\n", buf);

    close(fd);

    exit(0);
}

void error_handling(char *msg){
    fputs(msg, stderr);
    fputc('\n', stderr);
    exit(1);
}