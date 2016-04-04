#include "array.h"

#include <stdlib.h>

struct array_s {
    size_t size;
    int *arr;
};

array_t *array_create(size_t size) {
    size_t i;
    array_t *array = malloc(sizeof(array_t));
    array->size = size;
    array->arr = malloc(sizeof(int) * size);
    for (i = 0; i < array->size; ++i) {
        array->arr[i] = 0;
    }
    return array;
}

void array_insert(array_t *array, size_t index, int num) {
    if (index >= array->size)
        return -1;

    array->arr[index] = num;
}

int array_get(array_t *array, size_t index) {
    if (index >= array->size)
        return -1;

    return array->arr[index];
}

size_t array_size(array_t *array) {
    return array->size;
}

void array_destroy(array_t *array) {
    free(array->arr);
    free(array);
}
