#include "user.h"

#include "place.h"
#include "hall.h"
#include <string.h>
#include <stdlib.h>

struct user_s {
    char *name;
};

struct users_s {
    unsigned int size;
    user_t **users_array;
};

char *user_name(user_t *user) {
    return user->name;
}

user_t *user_create(const char *name) {
    user_t *user = malloc(sizeof(user_t));
    user->name = malloc(sizeof(char) * (strlen(name) + 1));
    memcpy(user->name, name, sizeof(char) * (strlen(name) + 1));
    return user;
}

void user_destroy(user_t *user) {
    free(user->name);
    free(user);
}

users_t *users_create() {
    users_t *users = malloc(sizeof(users_t));
    users->size = 0;
    users->users_array = malloc(0);
    return users;
}

void users_destroy(users_t *users) {
    int i;
    for (i = 0; i < users->size; ++i) {
        user_destroy(users->users_array[i]);
    }
    free(users->users_array);
    free(users);
}
user_t *users_get(users_t *users, const char *name) {
    int i;
    for (i = 0; i < users->size; ++i) {
        if (strcmp(name, users->users_array[i]->name) == 0) {
            return users->users_array[i];
        }
    }

    user_t *user = user_create(name);
    ++users->size;
    users->users_array = realloc(users->users_array, sizeof(user_t) * users->size);
    users->users_array[users->size - 1] = user;
    return user;
}
