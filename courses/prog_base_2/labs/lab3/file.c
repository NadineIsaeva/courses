#include "file.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define MAX_FILE_LENGTH 10

struct file_s {
    char *name;
    char *data;
};

file_t *file_create(const char *name, const char *data) {
    file_t *file = malloc(sizeof(file_t));
    file->name = malloc((strlen(name) + 1) * sizeof(char));
    strcpy(file->name, name);
    file->data = malloc((strlen(data) + 1) * sizeof(char));
    strcpy(file->data, data);
    return file;
}

file_t *file_createRandom(const char *name, size_t size) {
    char buffer[MAX_FILE_LENGTH + 1];
    size_t fileLength = size < MAX_FILE_LENGTH ? size : MAX_FILE_LENGTH;
    buffer[fileLength] = '\0';
    for (size_t i = 0; i < fileLength; ++i)
        buffer[i] = (rand() % ('z' - 'a' + 1)) + 'a';

    return file_create(name, buffer);
}

file_t *file_createRandomSized(const char *name) {
    return file_createRandom(name, rand() % (MAX_FILE_LENGTH + 1));
}

size_t file_size(file_t *file) {
    return strlen(file->data);
}

const char *file_name(file_t *file) {
    return file->name;
}

void file_print(file_t *file) {
    printf("File %s: <%s>\n", file->name, file->data);
}

void file_delete(file_t *file) {
    free(file->name);
    free(file->data);
    free(file);
}
