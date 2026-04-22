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
    memset(&addr, 0, sizeof(addr)); 

    addr.sin_family = AF_INET;
    addr.sin_port = htons(target->port); 
    addr.sin_addr.s_addr = INADDR_ANY;   

    if(bind(server_fd, (struct sockaddr*)&addr, sizeof(addr)) < 0){
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    if(listen(server_fd, 1000) < 0){
        perror("listen failed");
        exit(EXIT_FAILURE);
    }

    printf("\nServer listening on port %d\n", target->port);

    return server_fd;
}