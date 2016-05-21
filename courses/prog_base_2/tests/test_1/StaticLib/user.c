#include "user.h"

#include <stdlib.h>
#include <string.h>

struct user_s {
    char *name;
};

user_t *user_create(const char *name) {
    user_t *user = malloc(sizeof(user_t));
    user->name = malloc((strlen(name) + 1) * sizeof(char));
    strcpy(user->name, name);
    return user;
}

const char *user_name(user_t *user) {
    return user->name;
}

void user_delete(user_t *user) {
    free(user->name);
    free(user);
}

