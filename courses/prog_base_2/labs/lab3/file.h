#ifndef FILE_H
#define FILE_H

#include <stdlib.h>

typedef struct file_s file_t;

file_t *file_create(const char *name, const char *data);
file_t *file_createRandom(const char *name, size_t size);
file_t *file_createRandomSized(const char *name);
size_t file_size(file_t *file);
const char *file_name(file_t *file);
void file_print(file_t *file);
void file_delete(file_t *file);

#endif // FILE_H
