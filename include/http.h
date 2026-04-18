#pragma once

struct HttpRequest{
    char method[8];
    char *path;
    char version[16];
};

void parser_http_requests(const char *row, HttpRequest *request);
void parser_http_response(char *buffer, const char *body);

