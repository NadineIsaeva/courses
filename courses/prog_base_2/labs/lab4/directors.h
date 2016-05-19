#ifndef DIRECTORS_H
#define DIRECTORS_H

#include <time.h>

typedef struct {
    char name[32];
    char country[32];
} startup_t;

typedef struct {
    size_t id;
    char name[32];
    char surname[32];
    size_t salary;
    double rating;
    struct tm birthdate;
    startup_t startup;
} director_t;

typedef struct directors_s directors_t;

directors_t *directors_create();
size_t directors_count(directors_t *directors);
void directors_insert(directors_t *directors, const director_t *director);
const director_t *directors_get(directors_t *directors, size_t id);
void directors_get_all(directors_t *directors, const director_t **directorArray, size_t *count);
void directors_update(directors_t *directors, size_t id, const director_t *director);
int directors_remove(directors_t *directors, size_t id);
void directors_delete(directors_t *directors);

#endif // DIRECTORS_H
