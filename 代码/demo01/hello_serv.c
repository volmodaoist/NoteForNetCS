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

// argc: 参数个数, arg 参数缩写, c 代表个数;
// argv: 参数数值, arg 参数缩写, v 代表数值;

int main(int argc, char* argv[]) {
    int serv_sock;
    int clnt_sock;
    struct sockaddr_in serv_addr;
    struct sockaddr_in clnt_addr;
    struct sockaddr_in6 x;
    socklen_t clnt_addr_size;
    char message[] = "Hello World!";

    if(argc != 2){
        printf("Usage: %s <port>!\n", argv[0]);
    }

    /**
     * 其中 AF = Address Family
     * 其中 PF = Protocol Family
     * 大部分的系统上面 AF 与 PF 二者是相同的，但在些许系统中二者存在一定差异
     * 指定协议的使用尽量使用 PF，
     * 指定地址的时候尽量使用 AF
    */
    serv_sock = socket(PF_INET, SOCK_STREAM, 0);
    if (serv_sock == -1){
        error_handing("Socket Error!");
    }

    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htons(INADDR_ANY);
    serv_addr.sin_port = htons(atoi(argv[1]));

    // 成功返回 0, 失败返回 -1, 两个数字通过按位取反操作能将二者互相转化
    if(bind(serv_sock, (struct sockaddr_in*)&serv_addr, sizeof(serv_addr)) == -1){
        error_handing("Bind Error!");
    }

    if (listen(serv_sock, 5) == -1) {
        error_handing("Bind Error!");
    }

    // 如果服务端接受客户端通过connect函数发送的连接请求, 那么返回一个能够通信的、代表客户端的套接字!
    clnt_addr_size = sizeof(clnt_addr);
    clnt_sock = accept(serv_sock, (struct sockaddr_in*)&clnt_addr, &clnt_addr_size);
    if(clnt_sock == -1){
        error_handing("Accepted Error!");
    }

    write(clnt_sock, message, sizeof(message));
    printf("clnt_sock = %d\n", clnt_sock);
    printf("serv_sock = %d\n", serv_sock);

    // 打印之后会发现客户端打印出来的clnt_sock套接字，不同于服务端打印出来的clnt_sock
    close(clnt_sock);
    close(serv_sock);

    return 0;
}
