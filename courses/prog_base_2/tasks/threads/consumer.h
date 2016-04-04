#ifndef CONSUMER_H
#define CONSUMER_H

#include "array.h"
#include <windows.h>

typedef struct consumer_s consumer_t;

consumer_t *consumer_create(array_t *array, HANDLE mutex, size_t number);
void consumer_destroy(consumer_t *consumer);

#endif // CONSUMER_H
