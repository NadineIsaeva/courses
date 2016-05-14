#include "supadrive.h"

#include "client.h"
#include "file.h"
#include <stdlib.h>

typedef struct {
    client_t *client;
    supadrive_new_file_func_t supadrive_new_file_func;
    supadrive_overflow_func_t supadrive_overflow_func;
} supadrive_clientNode_t;

struct supadrive_s {
    file_t **files;
    size_t numberOfFiles;
    supadrive_clientNode_t *clientNodes;
    size_t numberOfClients;
    size_t capacity;
};

file_t **findFile(file_t **files, size_t numberOfFiles, const char *name) {
    for (size_t i = 0; i < numberOfFiles; ++i)
        if (strcmp(name, file_name(files[i])) == 0)
            return files + i;

    return NULL;
}

supadrive_clientNode_t *findClientNode(supadrive_clientNode_t *clientNodes, size_t numberOfClients, const char *name) {
    for (size_t i = 0; i < numberOfClients; ++i)
        if (strcmp(name, client_name(clientNodes[i].client)) == 0)
            return clientNodes + i;

    return NULL;
}

supadrive_t *supadrive_create(size_t capacity) {
    supadrive_t *supadrive = malloc(sizeof(supadrive_t));
    supadrive->files = malloc(0);
    supadrive->numberOfFiles = 0;
    supadrive->clientNodes = malloc(0);
    supadrive->numberOfClients = 0;
    supadrive->capacity = capacity;
    return supadrive;
}

void supadrive_subscribe(supadrive_t *supadrive, client_t *client, supadrive_new_file_func_t supadrive_new_file_func, supadrive_overflow_func_t supadrive_overflow_func) {
    ++supadrive->numberOfClients;
    supadrive->clientNodes = realloc(supadrive->clientNodes, supadrive->numberOfClients * sizeof(supadrive_clientNode_t));
    supadrive->clientNodes[supadrive->numberOfClients - 1].client = client;
    supadrive->clientNodes[supadrive->numberOfClients - 1].supadrive_new_file_func = supadrive_new_file_func;
    supadrive->clientNodes[supadrive->numberOfClients - 1].supadrive_overflow_func = supadrive_overflow_func;
}

void supadrive_uploadFile(supadrive_t *supadrive, client_t *client, file_t *file) {
    if ((supadrive_used(supadrive) + file_size(file)) > supadrive->capacity) {
        for (size_t i = 0; i < supadrive->numberOfClients; ++i)
            supadrive->clientNodes[i].supadrive_overflow_func(supadrive->clientNodes[i].client, client, file);
    } else {
        ++supadrive->numberOfFiles;
        supadrive->files = realloc(supadrive->files, supadrive->numberOfFiles * sizeof(file_t *));
        supadrive->files[supadrive->numberOfFiles - 1] = file;

        for (size_t i = 0; i < supadrive->numberOfClients; ++i)
            supadrive->clientNodes[i].supadrive_new_file_func(supadrive->clientNodes[i].client, client, file);
    }
}

file_t *supadrive_downloadFile(supadrive_t *supadrive, client_t *client, const char *fileName) {
    return *findFile(supadrive->files, supadrive->numberOfFiles, fileName);
}

void supadrive_deleteFile(supadrive_t *supadrive, client_t *client, const char *fileName) {
    size_t fileIndex = findFile(supadrive->files, supadrive->numberOfFiles, fileName) - supadrive->files;

    memmove(supadrive->files + fileIndex, supadrive->files + fileIndex + 1, (supadrive->numberOfFiles - fileIndex - 1) * sizeof(file_t *));
    --supadrive->numberOfFiles;
    supadrive->files = realloc(supadrive->files, supadrive->numberOfFiles * sizeof(file_t *));
}

size_t supadrive_capacity(supadrive_t *supadrive) {
    return supadrive->capacity;
}

size_t supadrive_used(supadrive_t *supadrive) {
    size_t used = 0;
    for (size_t i = 0; i < supadrive->numberOfFiles; ++i)
        used += file_size(supadrive->files[i]);
    return used;
}

void supadrive_print(supadrive_t *supadrive) {
    printf("Supadrive File Storage (Used: %u, Capacity: %u):\n", supadrive_used(supadrive), supadrive->capacity);
    for (size_t i = 0; i < supadrive->numberOfFiles; ++i)
        file_print(supadrive->files[i]);
}

void supadrive_delete(supadrive_t *supadrive) {
    free(supadrive->files);
    free(supadrive->clientNodes);
    free(supadrive);
}
