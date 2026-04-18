#include "stdio.h"
#include "sock.h"



int main(){

    struct Target_sock target = set_target(8000, "127.0.0.1");
    int server_fd = create_server_socket(&target);
    int client_fd = accept(server_fd, NULL, NULL);

    return 0;
}