#pragma once

struct HttpRequest {
    char method[8];
    char path[256];
    char version[16];
};

void http_parse_request(const char *raw, struct HttpRequest *request);

void http_build_response(
    char *buffer,
    int status_code,
    const char *content_type,
    const char *body
);