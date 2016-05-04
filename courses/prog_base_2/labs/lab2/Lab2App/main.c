#include <stdio.h>
#include <windows.h>
#include "../Lab2StaticLib/stack.h"

const char *dll1 = "Lab2DLL1.dll";
const char *dll2 = "Lab2DLL2.dll";

int main() {
    stack_t *stack = stack_create();

    size_t libChoice;
    printf("Choose your library ('1' or '2'): ");
    scanf("%u", &libChoice);

    HINSTANCE hLib = libChoice == 1 ? LoadLibrary(dll1) : LoadLibrary(dll2);

    stack_fill_func_t stack_fill_func = (stack_fill_func_t)GetProcAddress(hLib, "stack_fill");
    stack_overflowReact_func_t stack_overflowReact_func = (stack_overflowReact_func_t)GetProcAddress(hLib, "stack_overflowReact");

    while (1) {
        if (stack_size(stack) == 10) {
            printf("Stack Overflow\n");
            stack_overflowReact_func(stack);
            stack_print(stack);
        }

        stack_fill_func(stack);
        stack_print(stack);
    }

    stack_delete(stack);

    return 0;
}
