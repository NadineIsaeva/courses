#include "set.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct set_s {
    unsigned int size;
    unsigned int *elements;
};

set_t *set_create(void) {
    set_t *set = malloc(sizeof(set_t));
    set->size = 0;
    set->elements = malloc(0);
    return set;
}

void set_print(set_t *set) {
    int i;
    printf("(");
    for (i = 0; i < set->size; ++i) {
        printf("%u", set->elements[i]);
        if (i < set->size - 1)
            printf(",");
    }
    printf(")\n");
}

int set_check(set_t *set, unsigned int num) {
    int i;
    for (i = 0; i < set->size; ++i) {
        if (set->elements[i] == num)
            return 1;
    }
    return 0;
}

void set_add_elem(set_t *set, unsigned int num) {
    if ((num >= set_min) && (num <set_max)) {
        if (!set_check(set, num)) {
            ++set->size;
            set->elements = realloc(set->elements, set->size * sizeof(int));
            set->elements[set->size - 1] = num;
        }
    }
}

void set_remove_elem(set_t *set, unsigned int num) {
    int pos = -1;
    int i;
    for (i = 0; i < set->size; ++i) {
        if (set->elements[i] == num)
            pos = i;
    }

    if (pos != -1) {
        memmove(set->elements + pos, set->elements + pos + 1, (set->size - pos - 1) * sizeof(int));
        --set->size;
        set->elements = realloc(set->elements, set->size * sizeof(int));
    }
}

set_t *set_create_random(unsigned int size) {
    set_t *set = set_create();

    if (size > (set_max - set_min))
        return set;

    while (1) {
        int num = rand() % (set_max - set_min) + set_min;
        set_add_elem(set, num);
        if (set->size == size)
            break;
    }

    return set;
}

set_t *set_intersect(set_t *set1, set_t *set2) {
    set_t *set = set_create();

    int i;
    for (i = 0; i < set1->size; ++i) {
        if (set_check(set2, set1->elements[i]))
            set_add_elem(set, set1->elements[i]);
    }

    return set;
}

set_t *set_unite(set_t *set1, set_t *set2) {
    set_t *set = set_create();

    int i;
    for (i = 0; i < set1->size; ++i) {
        set_add_elem(set, set1->elements[i]);
    }
    for (i = 0; i < set2->size; ++i) {
        set_add_elem(set, set2->elements[i]);
    }

    return set;
}

set_t *set_different(set_t *set1, set_t *set2) {
    set_t *set = set_create();

    int i;
    for (i = 0; i < set1->size; ++i) {
        if (!set_check(set2, set1->elements[i]))
            set_add_elem(set, set1->elements[i]);
    }

    return set;
}

unsigned int set_size(set_t *set) {
    return set->size;
}

void set_delete(set_t *set) {
    free(set->elements);
    free(set);
}
