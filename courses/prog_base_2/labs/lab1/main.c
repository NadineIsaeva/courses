#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include <Windows.h>
#include "hall.h"
#include "place.h"
#include "user.h"

static void user_create__name__mustEqual(void **state) {
    user_t *user = user_create("vasia");
    assert_string_equal("vasia", user_name(user));
    user_destroy(user);
}

static void users_get__name__mustEqual(void **state) {
    users_t *users = users_create();
    user_t *user = users_get(users, "vasia");
    assert_string_equal("vasia", user_name(user));
    users_destroy(users);
}

static void place_create__void__statusMustBeFree_userMustBeNull(void **state) {
    place_t *place = place_create();
    assert_true(place_status(place) == place_status_free);
    assert_null(place_user(place));
    place_destroy(place);
}

static void place_buy__void__checkingStatus(void **state) {
    place_t *place = place_create();
    user_t *user1 = user_create("vasia");
    user_t *user2 = user_create("petro");

    place_error_t place_error = place_buy(place, user1);
    assert_true(place_status(place) == place_status_not_free);
    assert_true(place_user(place) == user1);
    assert_true(place_error == place_error_ok);

    place_error = place_buy(place, user2);
    assert_true(place_user(place) == user1);
    assert_true(place_error == place_error_not_free);

    place_destroy(place);
    user_destroy(user1);
    user_destroy(user2);
}

static void place_reserve__void__checkingStatus(void **state) {
    place_t *place = place_create();
    user_t *user1 = user_create("vasia");
    user_t *user2 = user_create("petro");

    place_error_t place_error = place_reserve(place, user1);
    assert_true(place_status(place) == place_status_reserved);
    assert_true(place_user(place) == user1);
    assert_true(place_error == place_error_ok);

    place_error = place_reserve(place, user2);
    assert_true(place_user(place) == user1);
    assert_true(place_error == place_error_reserved);

    place_error = place_buy(place, user1);
    assert_true(place_user(place) == user1);
    assert_true(place_error == place_error_ok);

    place_destroy(place);
    user_destroy(user1);
    user_destroy(user2);
}

static void place_dereserve__void__checkingStatus(void **state) {
    place_t *place = place_create();
    user_t *user1 = user_create("vasia");
    user_t *user2 = user_create("petro");

    place_reserve(place, user1);

    place_error_t place_error = place_dereserve(place, user2);
    assert_true(place_user(place) == user1);
    assert_true(place_error == place_error_forbidden);

    place_error = place_dereserve(place, user1);
    assert_true(place_status(place) == place_status_free);
    assert_true(place_error == place_error_ok);

    place_destroy(place);
    user_destroy(user1);
    user_destroy(user2);
}

static void hall_create__twoValues__checkWidthLength(void **state) {
    hall_t *hall = hall_create("Superhall", 5, 4);
    //assert_int_equal(hall_width(hall), 5);
    //assert_int_equal(hall_length(hall), 4);
    hall_destroy(hall);
}

int main()
{
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(user_create__name__mustEqual),
        cmocka_unit_test(users_get__name__mustEqual),
        cmocka_unit_test(place_create__void__statusMustBeFree_userMustBeNull),
        cmocka_unit_test(place_buy__void__checkingStatus),
        cmocka_unit_test(place_reserve__void__checkingStatus),
        cmocka_unit_test(place_dereserve__void__checkingStatus),
        cmocka_unit_test(hall_create__twoValues__checkWidthLength)
    };

    cmocka_run_group_tests(tests, NULL, NULL);

    system("pause");
    system("cls");

    char buffer[1024];
    unsigned int width, length;
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(h, 0x000f);
    printf("Enter width: ");
    scanf("%u", &width);
    printf("Enter length: ");
    scanf("%u", &length);
    printf("Enter hall name: ");
    scanf("%s", buffer);

    hall_t *hall = hall_create(buffer, width, length);

    users_t *users = users_create();
    user_t *user = NULL;

    while (1) {
        system("cls");

        if (!user) {
            printf("Enter user name: ");
            scanf("%s", buffer);

            user = users_get(users, buffer);
        } else {
            char ch;

            printf("User %s\n", user_name(user));
            hall_print(hall, user);
            printf("\n");
            printf("1. Reserve place\n");
            printf("2. Dereserve place\n");
            printf("3. Buy place\n");
            printf("e. Logout\n");
            printf("\n");
            printf("Your choose: ");
            scanf("%c", &ch);

            switch (ch) {
                case '1': {
                    unsigned int row, column;
                    place_t *place;
                    printf("\n");
                    printf("Enter row: ");
                    scanf("%u", &row);
                    printf("Enter column: ");
                    scanf("%u", &column);

                    hall_error_t hall_error = hall_get_place(hall, row, column, &place);
                    if (hall_error != hall_error_ok) {
                        printf("%s\n", hall_errstr(hall_error));
                        system("pause");
                    } else {
                        place_error_t place_error = place_reserve(place, user);
                        if (place_error != place_error_ok) {
                            printf("%s\n", place_errstr(place_error));
                            system("pause");
                        }
                    }

                    break;
                }
                case '2': {
                    unsigned int row, column;
                    place_t *place;
                    printf("\n");
                    printf("Enter row: ");
                    scanf("%u", &row);
                    printf("Enter column: ");
                    scanf("%u", &column);

                    hall_error_t hall_error = hall_get_place(hall, row, column, &place);
                    if (hall_error != hall_error_ok) {
                        printf("%s\n", hall_errstr(hall_error));
                        system("pause");
                    } else {
                        place_error_t place_error = place_dereserve(place, user);
                        if (place_error != place_error_ok) {
                            printf("%s\n", place_errstr(place_error));
                            system("pause");
                        }
                    }

                    break;
                }
                case '3': {
                    unsigned int row, column;
                    place_t *place;
                    printf("\n");
                    printf("Enter row: ");
                    scanf("%u", &row);
                    printf("Enter column: ");
                    scanf("%u", &column);

                    hall_error_t hall_error = hall_get_place(hall, row, column, &place);
                    if (hall_error != hall_error_ok) {
                        printf("%s\n", hall_errstr(hall_error));
                        system("pause");
                    } else {
                        place_error_t place_error = place_buy(place, user);
                        if (place_error != place_error_ok) {
                            printf("%s\n", place_errstr(place_error));
                            system("pause");
                        }
                    }

                    break;
                }
                case 'e':
                    user = NULL;
                    break;
            }
        }
    }

    return 0;
}
