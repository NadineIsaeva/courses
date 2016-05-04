#ifndef STACK_H
#define STACK_H

#include <stdlib.h>

typedef struct stack_s stack_t;

typedef void (*stack_fill_func_t)(stack_t *);
typedef void (*stack_overflowReact_func_t)(stack_t *);

stack_t *stack_create();
size_t stack_size(stack_t *stack);
void stack_push(stack_t *stack, const char *str);
void stack_pop(stack_t *stack, char *str);
void stack_peek(stack_t *stack, char *str);
void stack_print(stack_t *stack);
void stack_delete(stack_t *stack);

#endif // STACK_H
