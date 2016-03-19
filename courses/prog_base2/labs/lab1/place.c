#include "place.h"

#include "user.h"
#include <stdlib.h>

struct place_s {
    user_t *user;
    place_status_t status;
};

place_t *place_create() {
    place_t *place = malloc(sizeof(place_t));
    place->user = NULL;
    place->status = place_status_free;
    return place;
}

place_error_t place_reserve(place_t *place, user_t *user) {
    if (place->status == place_status_free) {
        place->user = user;
        place->status = place_status_reserved;
        return place_error_ok;
    } else if (place->status == place_status_not_free)
        return place_error_not_free;
    else
        return place_error_reserved;
}

place_error_t place_dereserve(place_t *place, user_t *user) {
    if ((place->user == user) && (place->status == place_status_reserved)) {
        place->status = place_status_free;
        place->user = NULL;
        return place_error_ok;
    } else if ((place->user != user) && (place->status == place_status_reserved))
        return place_error_forbidden;
    else if (place->status == place_status_not_free)
        return place_error_not_free;
    else
        return place_error_free;
}

place_error_t place_buy(place_t *place, user_t *user) {
    if (((place->user == user) && (place->status == place_status_reserved)) || (place->status == place_status_free)) {
        place->status = place_status_not_free;
        place->user = user;
        return place_error_ok;
    } else if ((place->user != user) && (place->status == place_status_reserved))
        return place_error_forbidden;
    else if (place->status == place_status_not_free)
        return place_error_not_free;
}

user_t *place_user(place_t *place) {
    return place->user;
}

place_status_t place_status(place_t *place) {
    return place->status;
}

void place_destroy(place_t *place) {
    free(place);
}

const char *place_errstr(place_error_t place_error) {
    static const char *repr[] = {
        "OK",
        "This place is already reserved",
        "This place is not free",
        "Forbidden, incorrect user",
        "This place is already free"
    };

    return repr[place_error];
}
