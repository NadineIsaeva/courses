#ifndef LIST_H
#define LIST_H

#include <stdlib.h>

typedef struct list_s list_t;

typedef void (*list_dealloc_func_t)(void *elem);

list_t *list_create(list_dealloc_func_t dealloc_func);
void *list_get(list_t *list, size_t index);
void list_push(list_t *list, void *elem);
int list_put(list_t *list, void *elem, size_t index);
int list_remove(list_t *list, size_t index);
size_t list_size(list_t *list);
void list_delete(list_t *list);

#endif // LIST_H
