#include "directors.h"
#include "http_server.h"

int main()
{
    directors_t *directors = directors_create("directors.json");

    http_server_t *http_server = http_server_create(directors);
    http_server_start(http_server);
    http_server_delete(http_server);

    directors_delete(directors);

    return 0;
}
