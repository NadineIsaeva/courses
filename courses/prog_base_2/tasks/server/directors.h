#ifndef DIRECTORS_H
#define DIRECTORS_H

#include <time.h>

typedef struct {
    char *name;
    char *country;
} startup_t;

typedef struct {
    char *name;
    char *surname;
    struct tm birth_date;
    startup_t startup;
    int salary;
    double rating;
} director_t;

typedef struct directors_s directors_t;

directors_t *directors_create(const char *file_name);
size_t directors_size(directors_t *directors);
director_t *directors_get(directors_t *directors, size_t index);
void directors_remove(directors_t *directors, size_t index);
void directors_print(directors_t *directors);
void directors_delete(directors_t *directors);

void director_update(director_t *director,
                     const char *name,
                     const char *surname,
                     const int *birthYear,
                     const int *birthDay,
                     const int *birthMonth,
                     const char *startupName,
                     const char *startupCountry,
                     const int *salary,
                     const double *rating);

#endif // DIRECTORS_H
