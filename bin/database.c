#include "database.h"

struct Person_dto* insert_name(char* name, char* path) {
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
    if (!id) {
        fclose(file);
        free(person);
        return NULL;
    }

    person->id = id;

    person->name = strdup(name);

    size_t size = strlen(id) + strlen(name) + 3; 
    char buffer[size];

    snprintf(buffer, size, "%s|%s\n", id, name);

    fprintf(file, "%s", buffer);

    fclose(file);
    return person;
}




struct Person_dto *get_name(char *id, char *path) {
    if (!id || !path) return NULL;

    FILE *file = fopen(path, "r");
    if (!file) {
        fprintf(stderr, "Could not open file\n");
        return NULL;
    }

    struct Person_dto *person = malloc(sizeof(struct Person_dto));
    if (!person) {
        fprintf(stderr, "Memory allocation failed\n");
        fclose(file);
        return NULL;
    }

    char temp[255];
    bool found = false;

    while (fgets(temp, sizeof(temp), file)) {

        char current_id[37];
        char current_name[200];

        char *token = strtok(temp, "|");
        if (!token) continue;

        strncpy(current_id, token, sizeof(current_id));
        current_id[36] = '\0';

        token = strtok(NULL, "\n");
        if (!token) continue;

        strncpy(current_name, token, sizeof(current_name));
        current_name[199] = '\0';

        if (strcmp(current_id, id) == 0) {
            person->id = strdup(current_id);
            person->name = strdup(current_name);
            found = true;
            break;
        }
    }

    fclose(file);

    if (!found) {
        free(person);
        return NULL;
    }

    return person;
}