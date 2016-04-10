#ifndef DIRECTORS_H
#define DIRECTORS_H

typedef struct directors_s directors_t;

directors_t *directors_create(const char *file_name);
void directors_print(directors_t *directors);
void directors_delete(directors_t *directors);

#endif // DIRECTORS_H
