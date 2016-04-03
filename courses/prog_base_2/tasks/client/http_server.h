#ifndef HTTP_SERVER_H
#define HTTP_SERVER_H

typedef struct http_server_s http_server_t;

http_server_t *http_server_create(void);
void http_server_request(http_server_t *http_server, const char *server_name, const char *url, const char *method, const char *body, char *res);
void http_server_destroy(http_server_t *http_server);

#endif // HTTP_SERVER_H
