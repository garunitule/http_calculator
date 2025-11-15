#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define LISTEN_BACKLOG 5

int main(void) {
    int socket_fd;
    socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    printf("socket_fd: %d\n", socket_fd);
    
    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(8080);
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    int bind_result;
    bind_result = bind(socket_fd, (struct sockaddr *) &addr, sizeof(addr));
    printf("bind result: %d\n", bind_result);

    int listen_result;
    listen_result = listen(socket_fd, LISTEN_BACKLOG);
    printf("listen result: %d\n", listen_result);

    struct sockaddr_in peer_addr;
    socklen_t peer_addr_size;
    int accept_result;
    peer_addr_size = sizeof(peer_addr);
    accept_result = accept(socket_fd, (struct sockaddr *) &peer_addr, &peer_addr_size);
    printf("accept_Result: %d\n", accept_result);
    
    return 0;
}