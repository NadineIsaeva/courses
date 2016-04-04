#include "array.h"
#include "consumer.h"
#include "producer.h"
#include <time.h>
#include <stdlib.h>
#include <windows.h>

int main()
{
    srand(time(NULL));
    HANDLE mutex = CreateMutex(NULL, FALSE, NULL);

    array_t *array = array_create(4);
    consumer_t *consumer1 = consumer_create(array, mutex, 1);
    consumer_t *consumer2 = consumer_create(array, mutex, 2);
    producer_t *producer1 = producer_create(array, mutex);
    producer_t *producer2 = producer_create(array, mutex);

    Sleep(5000);

    consumer_destroy(consumer1);
    consumer_destroy(consumer2);
    producer_destroy(producer1);
    producer_destroy(producer2);
    CloseHandle(mutex);

    return 0;
}
