#include "stdio.h"
#include "unistd.h"
#include "sock.h"
#include "http.h"
#include "database.h"
#include "string.h"
#include <stdbool.h>

int main() {
    struct Target_sock target = set_target(8000, "127.0.0.1");
    int server_fd = create_server_socket(&target);

    char *database_path = "users.txt";

    while (true) {
        int client_fd = accept(server_fd, NULL, NULL);

        char buffer[1024] = {0};
        read(client_fd, buffer, sizeof(buffer));

        struct HttpRequest req;
        http_parse_request(buffer, &req);

        char response[1024];

        if (strcmp(req.method, "POST") == 0 &&
            strcmp(req.path, "/user") == 0) {

            char *body = strstr(buffer, "\r\n\r\n");
            if (!body) {
                close(client_fd);
                continue;
            }
            body += 4;

            body[strcspn(body, "\r\n")] = 0;

            struct Person_dto *person = insert_name(body, database_path);

            sprintf(response,
                "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\n"
                "%s",
                (person && person->id) ? person->id : "error"
            );
        }

        else if (strcmp(req.method, "GET") == 0 &&
                 strstr(req.path, "/user") != NULL) {

            char id_str[64] = {0};

            char *id_pos = strstr(req.path, "id=");
            if (!id_pos) {
                sprintf(response,
                    "HTTP/1.1 400 Bad Request\r\n\r\nmissing id"
                );
                write(client_fd, response, strlen(response));
                close(client_fd);
                continue;
            }

            strncpy(id_str, id_pos + 3, sizeof(id_str) - 1);
            id_str[sizeof(id_str) - 1] = 0;
            id_str[strcspn(id_str, "& \r\n")] = 0;

            struct Person_dto *person = get_name(id_str, database_path);

            if (person && person->status && person->name) {
                sprintf(response,
                    "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\n"
                    "%s",
                    person->name
                );
            } else {
                sprintf(response,
                    "HTTP/1.1 404 Not Found\r\n\r\nnot found"
                );
            }
        }

        else {
            sprintf(response,
                "HTTP/1.1 404 Not Found\r\n\r\nroute not found"
            );
        }

        write(client_fd, response, strlen(response));
        close(client_fd);
    }

    return 0;
}