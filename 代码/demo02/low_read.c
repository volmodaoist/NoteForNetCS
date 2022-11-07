#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define MAXN 1005

char buf[MAXN];

void error_handing(char *message){
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}

// 文件描述符的分配是连续的
int main() {
    int fd = open("test.txt", O_RDONLY);
    if(fd == -1){
        error_handing("Open Error!");
    }
    printf("File Desriptor: %d\n", fd);
    if (read(fd, buf, sizeof(buf)) == -1) {
        error_handing("Read Error!");
    }
    printf("File data: %s\n", buf);
    close(fd);
    return 0;
}