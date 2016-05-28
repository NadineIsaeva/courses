#ifndef MIDDLEWARE_H
#define MIDDLEWARE_H

#include "http_server.h"
#include "http_client.h"
#include "db.h"

typedef struct middleware_s middleware_t;

middleware_t *middleware_create(http_client_t *http_client, db_t *db);
http_server_callback_t middleware_callback();
void middleware_delete(middleware_t *middleware);

#endif // MIDDLEWARE_H
