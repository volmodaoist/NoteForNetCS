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

// argc: ��������, arg ������д, c �������;
// argv: ������ֵ, arg ������д, v ������ֵ;

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
     * ���� AF = Address Family
     * ���� PF = Protocol Family
     * �󲿷ֵ�ϵͳ���� AF �� PF ��������ͬ�ģ�����Щ��ϵͳ�ж��ߴ���һ������
     * ָ��Э���ʹ�þ���ʹ�� PF��
     * ָ����ַ��ʱ����ʹ�� AF
    */
    serv_sock = socket(PF_INET, SOCK_STREAM, 0);
    if (serv_sock == -1){
        error_handing("Socket Error!");
    }

    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htons(INADDR_ANY);
    serv_addr.sin_port = htons(atoi(argv[1]));

    // �ɹ����� 0, ʧ�ܷ��� -1, ��������ͨ����λȡ�������ܽ����߻���ת��
    if(bind(serv_sock, (struct sockaddr_in*)&serv_addr, sizeof(serv_addr)) == -1){
        error_handing("Bind Error!");
    }

    if (listen(serv_sock, 5) == -1) {
        error_handing("Bind Error!");
    }

    // �������˽��ܿͻ���ͨ��connect�������͵���������, ��ô����һ���ܹ�ͨ�ŵġ�����ͻ��˵��׽���!
    clnt_addr_size = sizeof(clnt_addr);
    clnt_sock = accept(serv_sock, (struct sockaddr_in*)&clnt_addr, &clnt_addr_size);
    if(clnt_sock == -1){
        error_handing("Accepted Error!");
    }

    write(clnt_sock, message, sizeof(message));
    printf("clnt_sock = %d\n", clnt_sock);
    printf("serv_sock = %d\n", serv_sock);

    // ��ӡ֮��ᷢ�ֿͻ��˴�ӡ������clnt_sock�׽��֣���ͬ�ڷ���˴�ӡ������clnt_sock
    close(clnt_sock);
    close(serv_sock);

    return 0;
}
