#include <stdlib.h>
#include <time.h>
#include "set.h"

int main()
{
    srand(time(NULL));

    set_t *set = set_create();
    set_print(set);
    set_add_elem(set, 5);
    set_print(set);
    set_add_elem(set, 5);
    set_print(set);
    set_add_elem(set, 6);
    set_print(set);
    set_add_elem(set, 9);
    set_print(set);
    set_remove_elem(set, 5);
    set_print(set);

    set_t *set2 = set_create_random(5);
    set_print(set2);

    set_t *set3 = set_intersect(set, set2);
    set_print(set3);

    set_t *set4 = set_unite(set, set2);
    set_print(set4);

    set_t *set5 = set_different(set, set2);
    set_print(set5);

    set_delete(set4);

    return 0;
}
