#include "list.h"

#include <stdlib.h>
#include <string.h>

struct list_s {
    list_dealloc_func_t dealloc_func;
    void **elems;
    size_t size;
};

list_t *list_create(list_dealloc_func_t dealloc_func) {
    list_t *list = malloc(sizeof(list_t));
    list->dealloc_func = dealloc_func;
    list->elems = malloc(0);
    list->size = 0;
    return list;
}

void *list_get(list_t *list, size_t index) {
    if (index < list->size)
        return list->elems[index];
    return NULL;
}

void list_push(list_t *list, void *elem) {
    ++list->size;
    list->elems = realloc(list->elems, list->size * sizeof(void *));
    list->elems[list->size - 1] = elem;
}

int list_put(list_t *list, void *elem, size_t index) {
    if (index == list->size) {
        list_push(list, elem);
        return 1;
    } else if (index < list->size) {
        list->elems[index] = elem;
        return 1;
    }
    return 0;
}

int list_remove(list_t *list, size_t index) {
    if (index < list->size) {
        list->dealloc_func(list->elems[index]);
        memmove(list->elems + index, list->elems + index + 1, (list->size - index - 1) * sizeof(void *));
        --list->size;
        list->elems = realloc(list->elems, list->size * sizeof(void *));
        return 1;
    }
    return 0;
}

size_t list_size(list_t *list) {
    return list->size;
}

void list_delete(list_t *list) {
    for (size_t i = 0; i < list->size; ++i)
        list->dealloc_func(list->elems[i]);
    free(list->elems);
    free(list);
}
