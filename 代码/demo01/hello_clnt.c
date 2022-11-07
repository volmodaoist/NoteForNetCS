#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

void error_handing(char *message){
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}

// 传入的三个参数分别代表可执行文件名、IP地址、端口号
int main(int argc, char *argv[]){
    int sock;
    struct sockaddr_in serv_addr;
    char message[30];
    if (argc != 3){
        printf("Usage: %s <IP> <Port>\n", argv[0]);
        exit(1);
    }

    sock = socket(PF_INET, SOCK_STREAM, 0);
    if (sock == -1){
        error_handing("Socket Error!");
    }
    printf("sock = %d\n", sock);
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
    serv_addr.sin_port = htons(atoi(argv[2]));

    // 传入客户端的 sock, 然后向着服务端发出连接请求, 相当于是在尝试把客户端与服务端连在一起
    if (connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == -1){
        error_handing("Connect Error!");
    }

    // 会把读入的消息存入 message 里面
    int str_len = read(sock, message, sizeof(message) - 1);
    if (str_len == -1){
        error_handing("Read Error!");
    }
    printf("sock = %d\n", sock);
    printf("Message from server: %s\n", message);
    close(sock);
    return 0;
}