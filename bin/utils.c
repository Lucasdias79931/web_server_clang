#include "utils.h"

char* generate_uuid() {
    uuid_t uuid;
    char *uuid_str = malloc(37); 

    if (uuid_str == NULL) {
        return NULL;
    }

    uuid_generate_random(uuid);
    uuid_unparse_lower(uuid, uuid_str); 

    return uuid_str;
}
