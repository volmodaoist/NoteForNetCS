#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <arpa/inet.h>
#include <sys/socket.h>


void error_handing(char *message){
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}

// 使用文件的读写方式

int main(){
    char buf[] = "Let's go!\n";
    int fd = open("test.txt", O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
    if (fd == -1){
        error_handing("Open Error!");
    }
    printf("File destriptor: %d\n", fd);
    if (write(fd, buf, sizeof(buf)) == -1) {
        error_handing("Write Error!");
    }
    close(fd);
    return 0;
}