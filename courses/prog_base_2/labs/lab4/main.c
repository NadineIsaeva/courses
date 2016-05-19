#include "http_server.h"
#include "directors.h"
#include "middleware.h"

int main() {
    directors_t *directors = directors_create();
    middleware_t *middleware = middleware_create(directors);
    http_server_t *http_server = http_server_create(middleware);
    http_server_start(http_server);
    http_server_delete(http_server);
    middleware_delete(middleware);
    directors_delete(directors);

    return 0;
}
