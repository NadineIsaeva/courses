#include <stdio.h>
#include <stdlib.h>
#include "directors.h"

int main()
{
    directors_t *directors = directors_create("directors.json");
    directors_print(directors);
    directors_delete(directors);
    return 0;
}
