#ifndef SUPADRIVE_H
#define SUPADRIVE_H

#include "client.h"
#include "file.h"
#include <stdlib.h>

typedef struct supadrive_s supadrive_t;

typedef void (*supadrive_new_file_func_t)(client_t *receiver, client_t *emitter, file_t *file);
typedef void (*supadrive_overflow_func_t)(client_t *receiver, client_t *emitter, file_t *file);

supadrive_t *supadrive_create(size_t capacity);
void supadrive_subscribe(supadrive_t *supadrive, client_t *client, supadrive_new_file_func_t supadrive_new_file_func, supadrive_overflow_func_t supadrive_overflow_func);
void supadrive_uploadFile(supadrive_t *supadrive, client_t *client, file_t *file);
file_t *supadrive_downloadFile(supadrive_t *supadrive, client_t *client, const char *fileName);
void supadrive_deleteFile(supadrive_t *supadrive, client_t *client, const char *fileName);
size_t supadrive_capacity(supadrive_t *supadrive);
size_t supadrive_used(supadrive_t *supadrive);
void supadrive_print(supadrive_t *supadrive);
void supadrive_delete(supadrive_t *supadrive);

#endif // SUPADRIVE_H
