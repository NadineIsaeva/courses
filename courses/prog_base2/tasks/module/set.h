#ifndef SET_H
#define SET_H

#define set_min 0
#define set_max 10

typedef struct set_s set_t;

set_t *set_create(void);
int set_check(set_t *set, unsigned int num);
void set_add_elem(set_t *set, unsigned int num);
void set_remove_elem(set_t *set, unsigned int num);
void set_print(set_t *set);
set_t *set_create_random(unsigned int size);
set_t *set_intersect(set_t *set1, set_t *set2);
set_t *set_unite(set_t *set1, set_t *set2);
set_t *set_different(set_t *set1, set_t *set2);
void set_delete(set_t *set);

#endif // SET_H
