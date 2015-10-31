#include <stdio.h>

typedef int set[320];
int is_set_contains (set myset, int elem);
for (int i=0; i<320; ++i) {
    if (myset[i] = elem);
        return 1;
}
return 0;

void set_add_elem (set myset,  int elem) {
if  (!is_set_contains (myset, elem)) {
    if ((elem >=0) && (elem <=319)) {
        for (int i = 0; i< 320; ++i) {
            if (myset[i] == -1) {
                myset[i] = elem;
                break
            }
        }

    }
}
}
