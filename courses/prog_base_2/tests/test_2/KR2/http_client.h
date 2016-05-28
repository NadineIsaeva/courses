#ifndef HTTP_CLIENT
#define HTTP_CLIENT

typedef struct http_client_s http_client_t;

http_client_t *http_client_create();
void http_client_request(http_client_t *http_client, const char *server_name, const char *url, const char *method, const char *body, char *res);
void http_client_delete(http_client_t *http_client);

#endif // HTTP_CLIENT
