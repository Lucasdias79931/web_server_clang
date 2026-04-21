#include "database.h"


struct Person_dto* insert_name(char* name, char* path){
    struct Person_dto* person = malloc(sizeof(struct Person_dto));
    if (!person) {
        fprintf(stderr, "Memory allocation failed\n");
        return NULL;
    }

    FILE *file = fopen(path, "a");
    if (!file) {
        fprintf(stderr, "Could not open file for writing\n");
        free(person);
        return NULL;
    }

    char *id = generate_uuid();

    person->id = id;
    person->name = name;
    
    file.write(name, sizeof(char), strlen(name), file);
    file.write("\n", sizeof(char), 1, file);
    fclose(file);
    person->status = true;
    person->msg = "Name inserted successfully";

    return person;
}