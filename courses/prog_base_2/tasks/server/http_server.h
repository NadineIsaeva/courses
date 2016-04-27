#ifndef HTTP_SERVER_H
#define HTTP_SERVER_H

#include "directors.h"

typedef struct http_server_s http_server_t;

http_server_t *http_server_create(directors_t *directors);
void http_server_start(http_server_t *http_server);
void http_server_delete(http_server_t *http_server);

#endif // HTTP_SERVER_H
