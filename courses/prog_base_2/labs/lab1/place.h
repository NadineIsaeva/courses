#ifndef PLACE_H
#define PLACE_H

#include "user.h"

typedef struct place_s place_t;

typedef enum {
    place_status_free,
    place_status_reserved,
    place_status_not_free
} place_status_t;

typedef enum {
    place_error_ok,
    place_error_reserved,
    place_error_not_free,
    place_error_forbidden,
    place_error_free
} place_error_t;

place_t *place_create();
place_error_t place_buy(place_t *place, user_t *user);
place_error_t place_reserve(place_t *place, user_t *user);
place_error_t place_dereserve(place_t *place, user_t *user);
user_t *place_user(place_t *place);
place_status_t place_status(place_t *place);
void place_destroy(place_t *place);
const char *place_errstr(place_error_t place_error);

#endif // PLACE_H
