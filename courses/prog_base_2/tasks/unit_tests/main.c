#include <stdlib.h>  // !
#include <stdarg.h>  // !
#include <stddef.h>  // !
#include <setjmp.h>  // !

#include <cmocka.h>

#include "set.h"

static void create_void_zeroCount(void **state) {
    set_t *set = set_create();
    assert_int_equal(set_size(set), 0);
    set_delete(set);
}

static void add_oneValue_exists(void **state) {
    set_t *set = set_create();
    set_add_elem(set, 5);
    assert_true(set_check(set, 5));
    set_delete(set);
}

static void remove_oneValue_notExists(void **state) {
    set_t *set = set_create();
    set_add_elem(set, 5);
    set_remove_elem(set, 5);
    assert_false(set_check(set, 5));
    set_delete(set);
}

static void create_random__oneValue__countEquals(void **state) {
    set_t *set = set_create_random(6);
    assert_int_equal(set_size(set), 6);
    set_delete(set);
}

static void intersect_twoSets_intersects(void **state) {
    set_t *set1 = set_create();
    set_add_elem(set1, 5);
    set_add_elem(set1, 8);
    set_t *set2 = set_create();
    set_add_elem(set2, 5);
    set_add_elem(set2, 9);
    set_t *set3 = set_intersect(set1, set2);
    assert_true(set_check(set3, 5));
    assert_false(set_check(set3, 8));
    assert_false(set_check(set3, 9));
    set_delete(set1);
    set_delete(set2);
    set_delete(set3);
}

static void unite_twoSets_unites(void **state) {
    set_t *set1 = set_create();
    set_add_elem(set1, 5);
    set_add_elem(set1, 8);
    set_t *set2 = set_create();
    set_add_elem(set2, 5);
    set_add_elem(set2, 9);
    set_t *set3 = set_unite(set1, set2);
    assert_true(set_check(set3, 5));
    assert_true(set_check(set3, 8));
    assert_true(set_check(set3, 9));
    set_delete(set1);
    set_delete(set2);
    set_delete(set3);
}

static void different_twoSets_differents(void **state) {
    set_t *set1 = set_create();
    set_add_elem(set1, 5);
    set_add_elem(set1, 8);
    set_t *set2 = set_create();
    set_add_elem(set2, 5);
    set_add_elem(set2, 9);
    set_t *set3 = set_different(set1, set2);
    assert_false(set_check(set3, 5));
    assert_true(set_check(set3, 8));
    assert_false(set_check(set3, 9));
    set_delete(set1);
    set_delete(set2);
    set_delete(set3);
}



int main(void) {
    const struct CMUnitTest tests[] =
    {
        cmocka_unit_test(create_void_zeroCount),
        cmocka_unit_test(add_oneValue_exists),
        cmocka_unit_test(remove_oneValue_notExists),
        cmocka_unit_test(create_random__oneValue__countEquals),
        cmocka_unit_test(intersect_twoSets_intersects),
        cmocka_unit_test(unite_twoSets_unites),
        cmocka_unit_test(different_twoSets_differents)

    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}

