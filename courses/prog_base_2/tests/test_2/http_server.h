#ifndef HTTP_SERVER_H
#define HTTP_SERVER_H

#define BUFFER_LENGTH 16384
#define MAX_URL_LENGTH 2000

typedef struct http_server_s http_server_t;
typedef struct middleware_s middleware_t;

typedef enum {
    http_method_get,
    http_method_post,
    http_method_delete
} http_method_t;

typedef int (*http_server_callback_t)(middleware_t *middleware, http_method_t http_method, const char *url, const char *urlParamStr, const char *request, char *response);

http_server_t *http_server_create(middleware_t *middleware);
void http_server_start(http_server_t *http_server);
void http_server_delete(http_server_t *http_server);

void stradd(char *str, const char *add);

#endif // HTTP_SERVER_H

