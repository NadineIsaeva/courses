#ifndef HALL_H
#define HALL_H

#include "user.h"
#include "place.h"

typedef struct hall_s hall_t;

typedef enum {
    hall_error_ok,
    hall_error_not_found
} hall_error_t;

hall_t *hall_create(const char *name, unsigned int width, unsigned int length);
hall_error_t hall_get_place(hall_t *hall, unsigned int x, unsigned int y, place_t **place_res);
void hall_print(hall_t *hall, user_t *user);
void hall_destroy(hall_t *hall);
unsigned int hall_width(hall_t *hall);
unsigned int hall_length(hall_t *hall);
const char *hall_errstr(hall_error_t hall_error);

#endif // HALL_H
