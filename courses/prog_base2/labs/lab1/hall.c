#include "hall.h"

#include "place.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <Windows.h>

struct hall_s {
    char *name;
    unsigned int width;
    unsigned int length;
    place_t ***places;
};

hall_t *hall_create(const char *name, unsigned int width, unsigned int length) {
    int i, j;
    hall_t *hall = malloc(sizeof(hall_t));
    hall->name = malloc(sizeof(char) * (strlen(name) + 1));
    memcpy(hall->name, name, sizeof(char) * (strlen(name) + 1));
    hall->width = width;
    hall->length = length;
    hall->places = malloc(sizeof(place_t **) * hall->length);
    for (i = 0; i < hall->length; ++i) {
        hall->places[i] = malloc(sizeof(place_t *) * hall->width);
        for (j = 0; j < hall->width; ++j) {
            hall->places[i][j] = place_create();
        }
    }

    return hall;
}

hall_error_t hall_get_place(hall_t *hall, unsigned int x, unsigned int y, place_t **place_res) {
    if ((x < hall->width) && (y < hall->length)) {
        *place_res = hall->places[x][y];
        return hall_error_ok;
    } else
        return hall_error_not_found;
}

unsigned int hall_width(hall_t *hall) {
    return hall->width;
}

unsigned int hall_length(hall_t *hall) {
    return hall->length;
}

void hall_print(hall_t *hall, user_t *user) {
    int i, j;
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    for (i = 0; i < hall->length; ++i) {
        for (j = 0; j < hall->width; ++j) {
            if (place_status(hall->places[i][j]) == place_status_free)
                printf("o");
            else if (place_status(hall->places[i][j]) == place_status_reserved) {
                if (place_user(hall->places[i][j]) == user) {
                    SetConsoleTextAttribute(h, 0x000a);
                    printf("O");
                    SetConsoleTextAttribute(h, 0x000f);
                } else
                    printf("O");
            } else {
                if (place_user(hall->places[i][j]) == user) {
                    SetConsoleTextAttribute(h, 0x000a);
                    printf("x");
                    SetConsoleTextAttribute(h, 0x000f);
                } else
                    printf("x");
            }
        }
        printf("\n");
    }
}

void hall_destroy(hall_t *hall) {
    int i, j;
    free(hall->name);
    for (i = 0; i < hall->length; i++) {
        for (j = 0; j < hall->width; j++) {
            place_destroy(hall->places[i][j]);
        }
        free(hall->places[i]);
    }
    free(hall->places);
    free(hall);
}

const char *hall_errstr(hall_error_t hall_error) {
    static const char *repr[] = {
        "OK",
        "No such place"
    };

    return repr[hall_error];
}
