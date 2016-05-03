#ifndef DIRECTORS_DB_H
#define DIRECTORS_DB_H

#include <stdlib.h>

typedef struct {
    size_t id;
    char name[256];
    char surname[256];
    size_t investments;
    double rating;
    size_t year;
    size_t month;
    size_t day;
} director_t;

typedef struct directors_db_s directors_db_t;

directors_db_t *directors_db_open(const char *fileName);
void directors_db_insert(directors_db_t *directors_db, director_t *director);
void directors_db_readAll(directors_db_t *directors_db, director_t *directorArr, size_t *ammount);
int directors_db_readById(directors_db_t *directors_db, director_t *director, size_t id);
void directors_db_update(directors_db_t *directors_db, director_t *director);
void directors_db_delete(directors_db_t *directors_db, size_t id);
size_t directors_db_count(directors_db_t *directors_db);
void directors_db_filter(directors_db_t *directors_db, director_t *directorArr, size_t *ammount, size_t k, size_t p);
void directors_db_close(directors_db_t *directors_db);

void director_print(director_t *director);
void directors_print(director_t *directorArr, size_t ammount);

#endif // DIRECTORS_DB_H
