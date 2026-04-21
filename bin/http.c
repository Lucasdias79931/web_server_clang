#include <stdio.h>
#include <string.h>
#include "http.h"

// 🔍 Parse da primeira linha da requisição HTTP
void http_parse_request(const char *raw, struct HttpRequest *req) {
    if (!raw || !req) return;

    // Inicializa estrutura (evita lixo)
    memset(req, 0, sizeof(struct HttpRequest));

    // Extrai: METHOD PATH VERSION
    sscanf(raw, "%7s %255s %15s", req->method, req->path, req->version);
}


void http_build_response(
    char *buffer,
    int status_code,
    const char *content_type,
    const char *body
) {
    if (!buffer || !content_type || !body) return;

    const char *status_text;

    switch (status_code) {
        case 200:
            status_text = "OK";
            break;
        case 404:
            status_text = "Not Found";
            break;
        case 500:
            status_text = "Internal Server Error";
            break;
        default:
            status_text = "OK";
            break;
    }

    int body_length = strlen(body);

    snprintf(
        buffer,
        1024, 
        "HTTP/1.1 %d %s\r\n"
        "Content-Type: %s\r\n"
        "Content-Length: %d\r\n"
        "Connection: close\r\n"
        "\r\n"
        "%s",
        status_code,
        status_text,
        content_type,
        body_length,
        body
    );
}