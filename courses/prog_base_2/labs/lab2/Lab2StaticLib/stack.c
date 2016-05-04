#include "stack.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

struct stack_s {
    char **strArr;
    size_t size;
};

stack_t *stack_create() {
    stack_t *stack = malloc(sizeof(stack_t));
    stack->size = 0;
    stack->strArr = malloc(0);
}

size_t stack_size(stack_t *stack) {
    return stack->size;
}

void stack_push(stack_t *stack, const char *str) {
    char *strCopy = malloc((strlen(str) + 1) * sizeof(char));
    strcpy(strCopy, str);
    ++stack->size;
    stack->strArr = realloc(stack->strArr, stack->size * sizeof(char *));
    stack->strArr[stack->size - 1] = strCopy;
}

void stack_pop(stack_t *stack, char *str) {
    if (str)
        strcpy(str, stack->strArr[stack->size - 1]);
    free(stack->strArr[stack->size - 1]);
    --stack->size;
    stack->strArr = realloc(stack->strArr, stack->size * sizeof(char *));
}

void stack_peek(stack_t *stack, char *str) {
    strcpy(str, stack->strArr[stack->size - 1]);
}

void stack_print(stack_t *stack) {
    printf("Stack Head:\n");
    for (size_t i = stack->size - 1; (i + 1) > 0; --i)
        printf("%u: %s\n", i, stack->strArr[i]);
    printf("\n");
}

void stack_delete(stack_t *stack) {
    for (size_t i = 0; i < stack->size; ++i)
        free(stack->strArr[i]);
    free(stack->strArr);
    free(stack);
}
