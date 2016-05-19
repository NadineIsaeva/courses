#ifndef __MAIN_H__
#define __MAIN_H__

#include <windows.h>

#ifdef BUILD_DLL
    #define DLL_EXPORT __declspec(dllexport)
#else
    #define DLL_EXPORT __declspec(dllimport)
#endif


#ifdef __cplusplus
extern "C"
{
#endif

#include "stack.h"

void DLL_EXPORT stack_fill(stack_t *stack);
void DLL_EXPORT stack_overflowReact(stack_t *stack);

#ifdef __cplusplus
}
#endif

#endif // __MAIN_H__
