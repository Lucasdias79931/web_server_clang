#pragma once
#include "stdio.h"
#include "stdlib.h"
#include "stdbool.h"
#include "utils.h"
#include "string.h"

struct Person_dto{
    char *name;
    char *id;
    bool status;
    char *msg;
};



struct Person_dto* insert_name(char* name, char* path);
struct Person_dto* get_name(char* id, char *path);



