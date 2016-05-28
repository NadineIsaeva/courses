#include "middleware.h"
#include "http_server.h"
#include "http_client.h"
#include "db.h"

int main() {
    http_client_t *http_client = http_client_create();
    db_t *db = db_create();
    middleware_t *middleware = middleware_create(http_client, db);
    http_server_t *http_server = http_server_create(middleware);
    http_server_start(http_server);

    return 0;
}
