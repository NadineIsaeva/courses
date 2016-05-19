#ifndef MIDDLEWARE_H
#define MIDDLEWARE_H

#include "directors.h"
#include "http_server.h"

typedef struct middleware_s middleware_t;

middleware_t *middleware_create(directors_t *directors);
http_server_callback_t middleware_callback();
void middleware_delete(middleware_t *middleware);

#endif // MIDDLEWARE_H
