#include "consumer.h"

#include "array.h"
#include <windows.h>
#include <stdio.h>

struct consumer_s {
    array_t *array;
    HANDLE mutex;
    HANDLE thread;
    size_t number;
};

DWORD consumerRun(LPVOID aParams) {
    consumer_t *consumer = (consumer_t *)aParams;

    while (1) {
        size_t flag = 1;
        WaitForSingleObject(consumer->mutex, INFINITE);
        for (size_t i = 0; i < array_size(consumer->array) - 1; ++i) {
            if (array_get(consumer->array, i) > array_get(consumer->array, i + 1)) {
                flag = 0;
                break;
            }
        }

        if (flag) {
            printf("Consumer %u: (", consumer->number);
            for (size_t i = 0; i < array_size(consumer->array); ++i) {
                printf("%i", array_get(consumer->array, i));
                if (i != array_size(consumer->array) - 1)
                    printf(",");
            }
            printf(")\n");
        }
        ReleaseMutex(consumer->mutex);

        Sleep(1);
    }
}

consumer_t *consumer_create(array_t *array, HANDLE mutex, size_t number) {
    consumer_t *consumer = malloc(sizeof(consumer_t));
    consumer->array = array;
    consumer->mutex = mutex;
    consumer->thread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)consumerRun, consumer, 0, NULL);
    consumer->number = number;

    return consumer;
}

void consumer_destroy(consumer_t *consumer) {
    TerminateThread(consumer->thread, 0);
    CloseHandle(consumer->thread);
    free(consumer);
}
