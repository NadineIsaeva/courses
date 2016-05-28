#include "http_server.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <winsock2.h>
#include "middleware.h"

#pragma comment(lib,"ws2_32.lib")

#define MESSAGE_404 "HTTP/1.1 404 NOT FOUND\r\nContent-Length: 9\r\n\r\nNOT FOUND"

struct http_server_s {
    middleware_t *middleware;
};

int checkHttpRequestCompleteness(const char *request, size_t size) {
    char buffer[BUFFER_LENGTH];
    memcpy(buffer, request, size);
    buffer[size] = '\0';
    for (size_t i = 0; i < size; ++i)
        buffer[i] = tolower(buffer[i]);

    char *headersEndPos = strstr(buffer, "\r\n\r\n");
    if (!headersEndPos)
        return 0;

    char *contentLengthPos = strstr(buffer, "content-length: ");
    if ((!contentLengthPos) || contentLengthPos > headersEndPos)
        return 1;

    size_t contentLength = atoi(contentLengthPos + strlen("content-length: "));
    char *bodyStartPos = headersEndPos + strlen("\r\n\r\n");
    size_t contentRealLength = size - (bodyStartPos - buffer);
    if (contentRealLength >= contentLength)
        return 1;
    return 0;
}

void parseHttpRequest(const char *request, http_method_t *http_method, char *url, char *urlParamStr, char *message) {
    if (http_method) {
        *http_method = http_method_get;
        if (strncmp(request, "POST", strlen("POST")) == 0)
            *http_method = http_method_post;
        else if (strncmp(request, "DELETE", strlen("DELETE")) == 0)
            *http_method = http_method_delete;
    }

    if (url) {
        char *urlStart = strstr(request, " ") + 1;
        memcpy(url, urlStart, strstr(urlStart, " ") - urlStart);
        url[strstr(urlStart, " ") - urlStart] = '\0';
    }

    if (urlParamStr && url) {
        urlParamStr[0] = '\0';
        char *questionMarkPos = strchr(url, '?');
        if (questionMarkPos) {
            strcpy(urlParamStr, questionMarkPos + 1);
            *questionMarkPos = '\0';
        }
    }

    if (message) {
        char *messageStart = strstr(request, "\r\n\r\n") + 4;
        memcpy(message, messageStart, strlen(request) - (messageStart - request));
        message[strlen(request) - (messageStart - request)] = '\0';
    }
}

void stradd(char *str, const char *add) {
    memcpy(str + strlen(str), add, strlen(add) + 1);
}

void makeHttpResponse(const char *message, char *response) {
    *response = '\0';

    stradd(response, "HTTP/1.1 200 OK\r\n");
    stradd(response, "Content-type: application/json\r\n");
    stradd(response, "Content-length: ");
    char contentLengthStr[32];
    sprintf(contentLengthStr, "%u", strlen(message));
    stradd(response, contentLengthStr);
    stradd(response, "\r\n\r\n");
    stradd(response, message);
}

http_server_t *http_server_create(middleware_t *middleware) {
    http_server_t *http_server = malloc(sizeof(http_server_t));
    http_server->middleware = middleware;
    return http_server;
}

void http_server_start(http_server_t *http_server) {
    WSADATA wsa;
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
        printf("WSA startup failed: %d\n", WSAGetLastError());
        exit(1);
    }

    SOCKET listenSocket;
    if ((listenSocket = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
        printf("Create listen socket failed: %d\n", WSAGetLastError());
        WSACleanup();
        exit(1);
    }

    struct sockaddr_in serverSockAddr;
    memset(&serverSockAddr, 0, sizeof(struct sockaddr_in));
    serverSockAddr.sin_family = AF_INET;
    serverSockAddr.sin_addr.s_addr = INADDR_ANY;
    serverSockAddr.sin_port = htons(8888);

    if (bind(listenSocket, (struct sockaddr *)&serverSockAddr, sizeof(struct sockaddr_in)) == SOCKET_ERROR) {
        printf("Bind socket error: %d\n", WSAGetLastError());
        WSACleanup();
        exit(1);
    }

    if (listen(listenSocket, SOMAXCONN) == SOCKET_ERROR) {
        printf("Listen socket error: %d\n", WSAGetLastError());
        closesocket(listenSocket);
        WSACleanup();
        exit(1);
    }

    while (1) {
        SOCKET clientSocket = accept(listenSocket, NULL, NULL);
        if (clientSocket == INVALID_SOCKET) {
            printf("Client socket accept error: %d\n", WSAGetLastError());
            closesocket(listenSocket);
            WSACleanup();
            exit(1);
        }

        char recvBuffer[BUFFER_LENGTH];
        char sendBuffer[BUFFER_LENGTH];

        size_t recvTotalSize = 0;
        while (1) {
            int recvSize = recv(clientSocket, recvBuffer + recvTotalSize, BUFFER_LENGTH - recvTotalSize, 0);
            if (recvSize > 0) {
                recvTotalSize += recvSize;
                if (checkHttpRequestCompleteness(recvBuffer, recvTotalSize))
                    break;
            } else if (recvSize == 0) {
                break;
            } else {
                printf("recv error: %d\n", WSAGetLastError());
                closesocket(clientSocket);
                closesocket(listenSocket);
                WSACleanup();
                exit(1);
            }
        }
        recvBuffer[recvTotalSize] = '\0';

        http_method_t http_method;
        char url[MAX_URL_LENGTH];
        char urlParamStr[MAX_URL_LENGTH];
        char request[BUFFER_LENGTH];
        char response[BUFFER_LENGTH];

        parseHttpRequest(recvBuffer, &http_method, url, urlParamStr, request);
        http_server_callback_t http_server_callback = middleware_callback();
        if (!http_server_callback(http_server->middleware, http_method, url, urlParamStr, request, response))
            strcpy(sendBuffer, MESSAGE_404);
        else
            makeHttpResponse(response, sendBuffer);

        size_t sendTotalSize = 0;
        while (1) {
            int sendSize = send(clientSocket, sendBuffer + sendTotalSize, strlen(sendBuffer) - sendTotalSize, 0);
            if (sendSize == SOCKET_ERROR) {
                printf("send error: %d\n", WSAGetLastError());
                closesocket(clientSocket);
                closesocket(listenSocket);
                WSACleanup();
                exit(1);
            }

            sendTotalSize += sendSize;
            if (sendTotalSize == strlen(sendBuffer))
                break;
        }

        if (shutdown(clientSocket, SD_SEND) == SOCKET_ERROR) {
            printf("shutdown client socket error: %d\n", WSAGetLastError());
            closesocket(clientSocket);
            closesocket(listenSocket);
            WSACleanup();
            exit(1);
        }

        closesocket(clientSocket);
    }

    closesocket(listenSocket);
    WSACleanup();
}

void http_server_delete(http_server_t *http_server) {
    free(http_server);
}
