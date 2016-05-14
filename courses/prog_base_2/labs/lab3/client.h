#ifndef CLIENT_H
#define CLIENT_H

typedef struct client_s client_t;

client_t *client_create(const char *name);
const char *client_name(client_t *client);
void client_delete(client_t *client);

#endif // CLIENT_H
