#ifndef DIRECTOR_H
#define DIRECTOR_H

#include <time.h>

typedef struct {
    char name[128];
    char country[128];
} startup_t;

typedef struct {
    size_t id;
    char name[128];
    char surname[128];
    size_t salary;
    double rating;
    struct tm birthDate;
    startup_t startup;
} director_t;

void director_dealloc(void *director);

#endif // DIRECTOR_H
