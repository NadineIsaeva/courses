#include "file.h"
#include "client.h"
#include "supadrive.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>

static void file_create__twoValues__nameEqualsAndDataSameSize(void **state) {
    file_t *file = file_create("main.c", "ololo");
    assert_string_equal(file_name(file), "main.c");
    assert_int_equal(file_size(file), strlen("ololo"));
    file_delete(file);
}

static void file_createRandom__twoValues__nameEqualsAndDataSameSize(void **state) {
    file_t *file = file_createRandom("main.c", 8);
    assert_string_equal(file_name(file), "main.c");
    assert_int_equal(file_size(file), 8);
    file_delete(file);
}

static void file_createRandomSized__oneValue__nameEquals(void **state) {
    file_t *file = file_createRandomSized("main.c");
    assert_string_equal(file_name(file), "main.c");
    file_delete(file);
}

void unitTesting() {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(file_create__twoValues__nameEqualsAndDataSameSize),
        cmocka_unit_test(file_createRandom__twoValues__nameEqualsAndDataSameSize),
        cmocka_unit_test(file_createRandomSized__oneValue__nameEquals)
    };

    cmocka_run_group_tests(tests, NULL, NULL);
}

void nadineOverflowFunc(client_t *receiver, client_t *emitter, file_t *file) {
    printf("Supadrive overflow by %s. User Nadine yells: Oh my god!!!\n", client_name(emitter));
}

void ruslanOverflowFunc(client_t *receiver, client_t *emitter, file_t *file) {
    printf("Supadrive overflow by %s. User Ruslan yells: Ok\n", client_name(emitter));
}

void zgurovskiyOverflowFunc(client_t *receiver, client_t *emitter, file_t *file) {
    printf("Supadrive overflow by %s. User Zgurovskiy yells: Treba stvoriti robochu grupu\n", client_name(emitter));
}

void nadineNewFileFunc(client_t *receiver, client_t *emitter, file_t *file) {
    printf("Supadrive file upload: '%s' by '%s'. User Nadine\n", file_name(file), client_name(emitter));
}

void ruslanNewFileFunc(client_t *receiver, client_t *emitter, file_t *file) {
    printf("Supadrive file upload: '%s' by '%s'. User Ruslan\n", file_name(file), client_name(emitter));
}

void zgurovskiyNewFileFunc(client_t *receiver, client_t *emitter, file_t *file) {
    printf("Supadrive file upload: '%s' by '%s'. User Zgurovskiy\n", file_name(file), client_name(emitter));
}

int main()
{
    unitTesting();
    system("pause");
    system("cls");

    srand(time(NULL));

    file_t *file1 = file_createRandom("manual.txt", 5);
    file_t *file2 = file_createRandom("gameofthrones.mkv", 10);
    file_t *file3 = file_createRandom("main.c", 8);
    file_t *file4 = file_createRandom("eps1.9_zer0-day.avi", 5);

    client_t *client1 = client_create("Nadine");
    client_t *client2 = client_create("Ruslan");
    client_t *client3 = client_create("Zgurovskiy");

    supadrive_t *supadrive = supadrive_create(25);

    supadrive_subscribe(supadrive, client1, nadineNewFileFunc, nadineOverflowFunc);
    supadrive_subscribe(supadrive, client2, ruslanNewFileFunc, ruslanOverflowFunc);
    supadrive_subscribe(supadrive, client3, zgurovskiyNewFileFunc, zgurovskiyOverflowFunc);

    supadrive_uploadFile(supadrive, client1, file1);
    supadrive_uploadFile(supadrive, client2, file2);
    supadrive_uploadFile(supadrive, client3, file3);
    supadrive_uploadFile(supadrive, client1, file4);

    printf("\n");
    supadrive_print(supadrive);

    supadrive_deleteFile(supadrive, client1, "main.c");

    printf("\n");
    supadrive_print(supadrive);
    printf("\n");

    supadrive_uploadFile(supadrive, client1, file4);

    printf("\n");
    supadrive_print(supadrive);

    supadrive_delete(supadrive);

    client_delete(client3);
    client_delete(client2);
    client_delete(client1);

    file_delete(file4);
    file_delete(file3);
    file_delete(file2);
    file_delete(file1);

    return 0;
}
