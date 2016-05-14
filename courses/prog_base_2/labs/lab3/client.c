#include "client.h"

#include <stdlib.h>
#include <string.h>

struct client_s {
    char *name;
};

client_t *client_create(const char *name) {
    client_t *client = malloc(sizeof(client_t));
    client->name = malloc((strlen(name) + 1) * sizeof(char));
    strcpy(client->name, name);
    return client;
}

const char *client_name(client_t *client) {
    return client->name;
}

void client_delete(client_t *client) {
    free(client->name);
    free(client);
}
