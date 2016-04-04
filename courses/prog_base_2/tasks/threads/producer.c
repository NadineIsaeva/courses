#include "producer.h"

#include "array.h"
#include <windows.h>

struct producer_s {
    array_t *array;
    HANDLE mutex;
    HANDLE thread;
    size_t i;
};

DWORD producerRun(LPVOID aParams) {
    producer_t *producer = (producer_t *)aParams;

    while (1) {
        WaitForSingleObject(producer->mutex, INFINITE);
        array_insert(producer->array, producer->i, rand() % 10);
        ReleaseMutex(producer->mutex);
        ++producer->i;
        if (producer->i == array_size(producer->array))
            producer->i = 0;

        Sleep(1);
    }
}

producer_t *producer_create(array_t *array, HANDLE mutex) {
    producer_t *producer = malloc(sizeof(producer_t));
    producer->array = array;
    producer->mutex = mutex;
    producer->i = 0;
    producer->thread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)producerRun, producer, 0, NULL);

    return producer;
}

void producer_destroy(producer_t *producer) {
    TerminateThread(producer->thread, 0);
    CloseHandle(producer->thread);
    free(producer);
}
