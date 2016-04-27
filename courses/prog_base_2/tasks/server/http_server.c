#include "http_server.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <winsock2.h>
#include <windows.h>
#include "cJSON.h"

#pragma comment(lib,"ws2_32.lib")

struct http_server_s {
    directors_t *directors;
};

typedef enum {
    http_server_request_method_get,
    http_server_request_method_post,
    http_server_request_method_delete
} http_server_request_method_t;

http_server_t *http_server_create(directors_t *directors) {
    http_server_t *http_server = malloc(sizeof(http_server_t));
    http_server->directors = directors;
    return http_server;
}

void stradd(char *str, const char *add) {
    memcpy(str + strlen(str), add, strlen(add) + 1);
}

void makeHttpResponse(const char *message, char *response) {
    *response = '\0';

    stradd(response, "HTTP/1.1 200 OK\r\n");
    stradd(response, "Content-length: ");
    char contentLengthStr[100];
    sprintf(contentLengthStr, "%u", strlen(message));
    stradd(response, contentLengthStr);
    stradd(response, "\r\n\r\n");
    stradd(response, message);
}

void parseHttpRequest(const char *request, http_server_request_method_t *http_server_request_method, char *url, char *message) {
    if (http_server_request_method) {
        *http_server_request_method = http_server_request_method_get;
        if (strncmp(request, "POST", strlen("POST")) == 0)
            *http_server_request_method = http_server_request_method_post;
        else if (strncmp(request, "DELETE", strlen("DELETE")) == 0)
            *http_server_request_method = http_server_request_method_delete;
    }

    if (url) {
        char *urlStart = strstr(request, " ") + 1;
        memcpy(url, urlStart, strstr(urlStart, " ") - urlStart);
        url[strstr(urlStart, " ") - urlStart] = '\0';
    }

    if (message) {
        char *messageStart = strstr(request, "\r\n\r\n") + 4;
        memcpy(message, messageStart, strlen(request) - (messageStart - request));
        message[strlen(request) - (messageStart - request)] = '\0';
    }
}

void http_server_start(http_server_t *http_server) {
    WSADATA wsa;
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
        printf("Failed. Error Code : %d", WSAGetLastError());
        exit(1);
    }

    SOCKET s;
    if ((s = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
        printf("Could not create socket : %d" , WSAGetLastError());
        exit(1);
    }

    struct sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(8888);

    if (bind(s, (struct sockaddr *)&server, sizeof(server)) == SOCKET_ERROR) {
        printf("Bind failed with error code : %d" , WSAGetLastError());
        exit(EXIT_FAILURE);
    }

    listen(s, 3);

    int c = sizeof(struct sockaddr_in);
    SOCKET newSocket;
    struct sockaddr_in client;
    while ((newSocket = accept(s, (struct sockaddr *)&client, &c)) != INVALID_SOCKET) {
        char message[500000];
        char request[500000];
        int recvSize = recv(newSocket, request, sizeof(request), 0);
        request[recvSize] = '\0';

        http_server_request_method_t http_server_request_method;
        char url[128];
        char requestMessage[500000];
        parseHttpRequest(request, &http_server_request_method, url, requestMessage);
        printf("%s\n", url);

        if (strcmp(url, "/directors") == 0) {
            cJSON *json = cJSON_CreateArray();

            for (size_t i = 0; i < directors_size(http_server->directors); ++i) {
                director_t *director = directors_get(http_server->directors, i);

                cJSON *jsonDir = cJSON_CreateObject();
                cJSON_AddStringToObject(jsonDir, "name", director->name);
                cJSON_AddStringToObject(jsonDir, "surname", director->surname);
                char birthdateStr[128];
                sprintf(birthdateStr, "%i-%i-%i", director->birth_date.tm_year, director->birth_date.tm_mday, director->birth_date.tm_mon);
                cJSON_AddStringToObject(jsonDir, "birthdate", birthdateStr);
                cJSON *jsonStartup = cJSON_CreateObject();
                cJSON_AddStringToObject(jsonStartup, "name", director->startup.name);
                cJSON_AddStringToObject(jsonStartup, "country", director->startup.country);
                cJSON_AddItemToObject(jsonDir, "startup", jsonStartup);
                cJSON_AddNumberToObject(jsonDir, "salary", director->salary);
                cJSON_AddNumberToObject(jsonDir, "rating", director->rating);

                cJSON_AddItemToArray(json, jsonDir);
            }

            char *jsonStr = cJSON_Print(json);

            makeHttpResponse(jsonStr, message);
            cJSON_Delete(json);
            send(newSocket, message, strlen(message), 0);
        } else if (strncmp(url, "/directors/", strlen("/directors/")) == 0) {
            size_t directorIndex = atoi(strstr(url + 1, "/") + 1);
            director_t *director = directors_get(http_server->directors, directorIndex);

            if (http_server_request_method == http_server_request_method_delete) {
                directors_remove(http_server->directors, directorIndex);

                makeHttpResponse("", message);
                send(newSocket, message, strlen(message), 0);
            } else if (http_server_request_method == http_server_request_method_post) {
                cJSON *json = cJSON_Parse(requestMessage);

                cJSON *subItem = json->child;
                while (subItem) {
                    if ((subItem->type == cJSON_String) && (strcmp(subItem->string, "name") == 0))
                        director_update(director, subItem->valuestring, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
                    if ((subItem->type == cJSON_String) && (strcmp(subItem->string, "surname") == 0))
                        director_update(director, NULL, subItem->valuestring, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
                    if ((subItem->type == cJSON_String) && (strcmp(subItem->string, "birthdate") == 0)) {
                        int year;
                        int day;
                        int month;
                        sscanf(subItem->valuestring, "%i-%i-%i", &year, &day, &month);
                        director_update(director, NULL, NULL, &year, &day, &month, NULL, NULL, NULL, NULL);
                    }
                    if ((subItem->type == cJSON_Object) && (strcmp(subItem->string, "startup") == 0)) {
                        cJSON *subJtem = subItem->child;
                        while (subJtem) {
                            if ((subJtem->type == cJSON_String) && (strcmp(subJtem->string, "name") == 0))
                                director_update(director, NULL, NULL, NULL, NULL, NULL, subJtem->valuestring, NULL, NULL, NULL);
                            if ((subJtem->type == cJSON_String) && (strcmp(subJtem->string, "country") == 0))
                                director_update(director, NULL, NULL, NULL, NULL, NULL, NULL, subJtem->valuestring, NULL, NULL);

                            subJtem = subJtem->next;
                        }
                    }
                    if ((subItem->type == cJSON_Number) && (strcmp(subItem->string, "salary") == 0)) {
                        director_update(director, NULL, NULL, NULL, NULL, NULL, NULL, NULL, &subItem->valueint, NULL);
                    }
                    if ((subItem->type == cJSON_Number) && (strcmp(subItem->string, "rating") == 0)) {
                        director_update(director, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, &subItem->valuedouble);
                    }

                    subItem = subItem->next;
                }

                makeHttpResponse("", message);
                send(newSocket, message, strlen(message), 0);
            } else {
                cJSON *json = cJSON_CreateObject();
                cJSON_AddStringToObject(json, "name", director->name);
                cJSON_AddStringToObject(json, "surname", director->surname);
                char birthdateStr[128];
                sprintf(birthdateStr, "%i-%i-%i", director->birth_date.tm_year, director->birth_date.tm_mday, director->birth_date.tm_mon);
                cJSON_AddStringToObject(json, "birthdate", birthdateStr);
                cJSON *jsonStartup = cJSON_CreateObject();
                cJSON_AddStringToObject(jsonStartup, "name", director->startup.name);
                cJSON_AddStringToObject(jsonStartup, "country", director->startup.country);
                cJSON_AddItemToObject(json, "startup", jsonStartup);
                cJSON_AddNumberToObject(json, "salary", director->salary);
                cJSON_AddNumberToObject(json, "rating", director->rating);

                char *jsonStr = cJSON_Print(json);

                makeHttpResponse(jsonStr, message);
                cJSON_Delete(json);
                send(newSocket, message, strlen(message), 0);
            }
        } else {
            const char *message = "HTTP/1.1 404\r\nContent-length: 0\r\n\r\n";
            send(newSocket, message, strlen(message), 0);
        }

        closesocket(newSocket);
    }

    if (newSocket == INVALID_SOCKET) {
        printf("accept failed with error code : %d" , WSAGetLastError());
        exit(1);
    }

    closesocket(s);
    WSACleanup();
}

void http_server_delete(http_server_t *http_server) {
    free(http_server);
}
