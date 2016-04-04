#ifndef PRODUCER_H
#define PRODUCER_H

#include "array.h"
#include <windows.h>

typedef struct producer_s producer_t;

producer_t *producer_create(array_t *array, HANDLE mutex);
void producer_destroy(producer_t *producer);

#endif // PRODUCER_H
