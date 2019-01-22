#include <sys/socket.h>

int main(){
    int n = 50;
    int fds[n];
    for (int i = 0; i < n; i ++){
        fds[i] = socket(PF_INET, SOCK_STREAM, 0);
    }

    for (int i = 0; i < n; i ++){
        printf("%d\n", fds[i]);
    }

    return 0;


}