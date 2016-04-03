#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "http_server.h"

void get_maximum_word(const char *str, char *res) {
    size_t pos;
    size_t len = 0;
    size_t current_pos;
    size_t current_len = 0;
    size_t i;

    for (i = 0; i < strlen(str); ++i) {
        if (((str[i] >= 'a') && (str[i] <= 'z')) || ((str[i] >= 'A') && (str[i] <= 'Z'))) {
            if (current_len == 0)
                current_pos = i;
            ++current_len;
        } else {
            if (current_len > len) {
                len = current_len;
                pos = current_pos;
            }

            current_len = 0;
        }
    }
    if (current_len > len) {
        len = current_len;
        pos = current_pos;
    }

    memcpy(res, str + pos, len + 1);
    res[len] = 0;
}

int main()
{
    char result1[1024];
    char result2[1024];
    char result3[1024];
    char buffer[1024];
    char buffer2[1024];

    http_server_t *http_server = http_server_create();

    http_server_request(http_server, "pb-homework.appspot.com", "/var/4", "GET", NULL, result1);
    sprintf(buffer, "/var/4?%s", result1);
    http_server_request(http_server, "pb-homework.appspot.com", buffer, "GET", NULL, result2);
    get_maximum_word(result2, buffer);
    sprintf(buffer2, "result=%s", buffer);
    http_server_request(http_server, "pb-homework.appspot.com", "/var/4", "POST", buffer2, result3);
    printf(result3);

    http_server_destroy(http_server);

    return 0;
}
