#include "http_server.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <winsock2.h>

#pragma comment(lib,"ws2_32.lib") //Winsock Library

struct http_server_s {
    WSADATA wsa;
};

void domain_resolve(const char *domain, char *ip) {
    struct hostent *he;
    struct in_addr **addr_list;
    int i;

    if ((he = gethostbyname(domain)) == NULL) {
        printf("gethostbyname failed : %d" , WSAGetLastError());
        exit(1);
    }

    addr_list = (struct in_addr **) he->h_addr_list;

    for (i = 0; addr_list[i] != NULL; i++) {
        strcpy(ip, inet_ntoa(*addr_list[i]));
    }
}

void stradd(char *str, const char *add) {
    memcpy(str + strlen(str), add, strlen(add) + 1);
}

void make_http_request(const char *host, const char *url, const char *method, const char *body, char *res) {
    res[0] = 0;

    stradd(res, method);
    stradd(res, " ");
    stradd(res, url);
    stradd(res, " HTTP/1.1\r\n");
    stradd(res, "Host: ");
    stradd(res, host);
    stradd(res, "\r\n");
    if (body) {
        stradd(res, "Content-length: ");
        char content_length_str[100];
        sprintf(content_length_str, "%u", strlen(body));
        stradd(res, content_length_str);
        stradd(res, "\r\n");
    }
    stradd(res, "\r\n");
    if (body)
        stradd(res, body);
}

void get_message_from_response(const char *response, char *res) {
    const char *message = strstr(response, "\r\n\r\n") + 4;
    memcpy(res, message, strlen(message) + 1);
}

http_server_t *http_server_create(void) {
    http_server_t *http_server = malloc(sizeof(http_server_t));

    if (WSAStartup(MAKEWORD(2, 2), &http_server->wsa) != 0) {
        printf("Failed. Error Code : %d",WSAGetLastError());
        exit(1);
    }

    return http_server;
}

void http_server_request(http_server_t *http_server, const char *server_name, const char *url, const char *method, const char *body, char *res) {
    SOCKET sock;
    struct sockaddr_in server;
    char response[2048];

    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
        printf("Could not create socket : %d" , WSAGetLastError());
        exit(1);
    }

    char ip[100];
    domain_resolve(server_name, ip);

    server.sin_addr.s_addr = inet_addr(ip);
    server.sin_family = AF_INET;
    server.sin_port = htons(80);

    if (connect(sock, (struct sockaddr *)&server , sizeof(server)) < 0) {
        printf("connect error");
        exit(1);
    }

    char request[2048];
    make_http_request(server_name, url, method, body, request);

    if (send(sock, request, strlen(request), 0) < 0) {
        printf("Send failed");
        exit(1);
    }

    size_t recv_size;
    if ((recv_size = recv(sock, response, 2048, 0)) == SOCKET_ERROR) {
        printf("recv failed");
        exit(1);
    }

    response[recv_size] = 0;

    get_message_from_response(response, res);

    closesocket(sock);
}

void http_server_destroy(http_server_t *http_server) {
    WSACleanup();
    free(http_server);
}
