#include "main.h"

#include <stdio.h>
#include <string.h>

void stack_fill(stack_t *stack) {
    char buffer[1024];
    do {
        printf("Enter string to add (max length - 10): ");
        scanf("%s", buffer);
    } while (strlen(buffer) > 10);
    stack_push(stack, buffer);
}

void stack_overflowReact(stack_t *stack) {
    size_t popNum;
    do {
        printf("Enter number of string to pop (max - %u): ", stack_size(stack));
        scanf("%u", &popNum);
    } while (popNum > stack_size(stack));
    for (size_t i = 0; i < popNum; ++i)
        stack_pop(stack, NULL);
}
