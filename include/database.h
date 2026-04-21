#pragma once
#include <stdbool.h>

struct Person_dto{
    char *name;
    char *id;
    bool status;
};

void insert_name(char* name, char* path);
struct Person_dto* get_name(char* id);



