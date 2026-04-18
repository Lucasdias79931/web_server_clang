#pragma once
#include "structs.h"
#include "string.h"
#include "stdlib.h"
#include "stdio.h"
#include "stddef.h"

#include "unistd.h"
#include "arpa/inet.h"
#include "sys/socket.h"


struct Target_sock set_target(int port, const char* host);

void free_target(struct Target_sock* target);

int create_server_socket(struct Target_sock* target);