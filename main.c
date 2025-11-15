#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define LISTEN_PORT 8080
#define LISTEN_BACKLOG 5

int main(void) {
    int socket_fd;
    socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    printf("socket_fd: %d\n", socket_fd);
    
    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(LISTEN_PORT);
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    int bind_result;
    bind_result = bind(socket_fd, (struct sockaddr *) &addr, sizeof(addr));
    printf("bind result: %d\n", bind_result);

    int listen_result;
    listen_result = listen(socket_fd, LISTEN_BACKLOG);
    printf("listen result: %d\n", listen_result);
    printf("listening on port %d...\n", LISTEN_PORT);

    while (1) {
        // accept
        struct sockaddr_in peer_addr;
        socklen_t peer_addr_size;
        int accept_result;
        peer_addr_size = sizeof(peer_addr);
        accept_result = accept(socket_fd, (struct sockaddr *) &peer_addr, &peer_addr_size);
        if (accept_result == -1) {
            perror("accept");
            continue;
        }
        int client_fd;
        client_fd = accept_result;
        printf("client_fd: %d\n", client_fd);

        // TODO: リクエスト情報から取得したパス、クエリのバリデーション・取得
        char buf[1024];
        ssize_t n = recv(client_fd, buf, sizeof(buf), 0);
        if (n > 0) {
            buf[n] = '\0';
        }
        printf("=== request ===\n%s\n", buf);

        // TODO: HTTPレスポンス返す

        // close
        close(client_fd);
        printf("closed. fd: %d\n", client_fd);
    }

    close(socket_fd);
    return 0;
}