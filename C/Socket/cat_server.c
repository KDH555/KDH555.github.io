#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <pthread.h>

#define BUF_SIZE 1024
void error_handling(char *message);
void *handle_client(void *arg);

int main(int argc, char *argv[]) {
    int serv_sock;
    struct sockaddr_in serv_adr, clnt_adr;
    socklen_t clnt_adr_sz;
    pthread_t t_id;

    if (argc != 2) {
        printf("Usage: %s <port>\n", argv[0]);
        exit(1);
    }

    serv_sock = socket(PF_INET, SOCK_STREAM, 0);
    if (serv_sock == -1)
        error_handling("socket() error");

    memset(&serv_adr, 0, sizeof(serv_adr));
    serv_adr.sin_family = AF_INET;
    serv_adr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_adr.sin_port = htons(atoi(argv[1]));

    if (bind(serv_sock, (struct sockaddr*)&serv_adr, sizeof(serv_adr)) == -1)
        error_handling("bind() error");

    if (listen(serv_sock, 10) == -1)
        error_handling("listen() error");

    printf("🐾 고양이 서버 실행 중...\n");

    while (1) {
        clnt_adr_sz = sizeof(clnt_adr);
        int *clnt_sock = malloc(sizeof(int));
        *clnt_sock = accept(serv_sock, (struct sockaddr*)&clnt_adr, &clnt_adr_sz);

        if (*clnt_sock == -1) {
            perror("accept() error");
            free(clnt_sock);
            continue;
        }

        printf("📡 클라이언트 연결됨\n");

        pthread_create(&t_id, NULL, handle_client, (void*)clnt_sock);
        pthread_detach(t_id);
    }

    close(serv_sock);
    return 0;
}

void *handle_client(void *arg) {
    int sock = *((int*)arg);
    free(arg);

    char buf[BUF_SIZE];
    int read_len;

    // 요청 읽기
    read(sock, buf, BUF_SIZE - 1);
    buf[BUF_SIZE - 1] = 0;

    // HTML 요청 처리
    if (strstr(buf, "GET / ") != NULL) {
        int html_fd = open("cat_index.html", O_RDONLY);
        if (html_fd == -1) {
            perror("cat_index.html open error");
            close(sock);
            return NULL;
        }

        char header[] =
            "HTTP/1.1 200 OK\r\n"
            "Content-Type: text/html\r\n"
            "Connection: close\r\n\r\n";
        write(sock, header, strlen(header));

        while ((read_len = read(html_fd, buf, BUF_SIZE)) > 0)
            write(sock, buf, read_len);

        close(html_fd);
    }
    // 이미지 요청 처리
    else if (strstr(buf, "GET /cat.jpg") != NULL) {
        int img_fd = open("cat.jpg", O_RDONLY);
        if (img_fd == -1) {
            perror("cat.jpg open error");
            close(sock);
            return NULL;
        }

        char header[] =
            "HTTP/1.1 200 OK\r\n"
            "Content-Type: image/jpeg\r\n"
            "Connection: close\r\n\r\n";
        write(sock, header, strlen(header));

        while ((read_len = read(img_fd, buf, BUF_SIZE)) > 0)
            write(sock, buf, read_len);

        close(img_fd);
    }
    // 404 처리
    else {
        char header[] =
            "HTTP/1.1 404 Not Found\r\n"
            "Content-Type: text/plain\r\n"
            "Connection: close\r\n\r\n"
            "404 - 요청한 파일을 찾을 수 없습니다.";
        write(sock, header, strlen(header));
    }

    close(sock);
    printf("🔌 클라이언트 연결 종료\n\n");
    return NULL;
}

void error_handling(char *message) {
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}
