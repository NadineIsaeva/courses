#include "main.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <conio.h>

fp = int ** (*func) (int *);

void stack_fill(stack_t *stack) {
    printf("Press any key to push random str: ");
    _getch();
    printf("\n");
    char buffer[11];
    size_t strLen = rand() % 11;
    buffer[strLen] = '\0';
    for (size_t i = 0; i < strLen; ++i)
        buffer[i] = (rand() % ('z' - 'a' + 1)) + 'a';
    stack_push(stack, buffer);
}

void stack_overflowReact(stack_t *stack) {
    char buffer[11];
    stack_peek(stack, buffer);
    size_t popNum = strlen(buffer);
    for (size_t i = 0; i < popNum; ++i)
        stack_pop(stack, NULL);
}

extern "C" DLL_EXPORT BOOL APIENTRY DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
    srand(time(NULL));

    return TRUE;
}
