#ifndef ARRAY_H
#define ARRAY_H

#include <stdlib.h>

typedef struct array_s array_t;

array_t *array_create(size_t size);
void array_insert(array_t *array, size_t index, int num);
int array_get(array_t *array, size_t index);
size_t array_size(array_t *array);
void array_destroy(array_t *array);

#endif // ARRAY_H
