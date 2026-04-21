#include "stdio.h"
#include "unistd.h"
#include "sock.h"
#include "http.h"
#include "database.h"





int main() {
    struct Target_sock target = set_target(8000, "127.0.0.1");
    int server_fd = create_server_socket(&target);

    while (1) {
        int client_fd = accept(server_fd, NULL, NULL);

        char buffer[1024] = {0};
        read(client_fd, buffer, sizeof(buffer));

        struct HttpRequest req;
        http_parse_request(buffer, &req);

        printf("Method: %s\nPath: %s\nVersion: %s\n",
               req.method, req.path, req.version);

        char response[1024];
        http_build_response(response, 200, "text/plain", "Hello World");

        write(client_fd, response, strlen(response));

        close(client_fd);
    }

    return 0;
}