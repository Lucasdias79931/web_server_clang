#include "sock.h"

struct Target_sock set_target(int port, const char* host){
    struct Target_sock target;

    if (port < 1024 || port > 65535) {
        fprintf(stderr, "Invalid port! Should use between 1024 and 65535\n");
        exit(EXIT_FAILURE);
    }

    if (!host) {
        fprintf(stderr, "Host must be a valid string\n");
        exit(EXIT_FAILURE);
    }

    target.port = port;

    target.host = malloc(strlen(host) + 1);
    if (!target.host) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    strcpy(target.host, host);

    return target;
}

void free_target(struct Target_sock* target) {
    free(target->host);
}


int create_server_socket(struct Target_sock* target){
    int server_fd;

    server_fd = socket(AF_INET, SOCK_STREAM, 0);

    if(server_fd < 0){
        perror("socket failed");
        exit(EXIT_FAILURE);
    }


    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = target->port;
    addr.sin_addr.s_addr = inet_addr(target->host);

    if(listen(server_fd, 10) < 0){
        perror("listen failed");
        exit(EXIT_FAILURE);
    }

    printf("\nServe listening in {%s}:{%i}\n",target->host,target->port);

    return server_fd;
}