#include "directors_db.h"

#include <conio.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
    directors_db_t *directors_db = directors_db_open("directors.db");

    while (1) {
        printf("1. Read\n");
        printf("2. Read by id\n");
        printf("3. Insert\n");
        printf("4. Update\n");
        printf("5. Delete\n");
        printf("6. Filter\n\n");
        printf("e. Exit\n");

        char ch = _getch();
        system("cls");

        if (ch == '1') {
            printf("Table (%u rows):\n", directors_db_count(directors_db));
            director_t directors[64];
            size_t directorsAmmount;
            directors_db_readAll(directors_db, directors, &directorsAmmount);
            directors_print(directors, directorsAmmount);
            printf("\nPress any key to menu\n");
            _getch();
            system("cls");
        } else if (ch == '2') {
            director_t director;

            printf("Enter id to read: ");
            size_t id;
            scanf("%u", &id);

            if (directors_db_readById(directors_db, &director, id)) {
                director_print(&director);
            } else
                printf("No such id\n");

            printf("\nPress any key to menu\n");
            _getch();
            system("cls");
        } else if (ch == '3') {
            director_t director;

            printf("Enter director name: ");
            scanf("%s", director.name);
            printf("Enter director surname: ");
            scanf("%s", director.surname);
            printf("Enter director investments: ");
            scanf("%u", &director.investments);
            printf("Enter director rating: ");
            scanf("%lf", &director.rating);
            printf("Enter director startup birthdate in format 'dd.mm.yyyy': ");
            scanf("%u.%u.%u", &director.day, &director.month, &director.year);

            directors_db_insert(directors_db, &director);

            system("cls");
        } else if (ch == '4') {
            director_t director;

            printf("Enter id to update: ");
            scanf("%u", &director.id);
            printf("\n");
            printf("Enter director name: ");
            scanf("%s", director.name);
            printf("Enter director surname: ");
            scanf("%s", director.surname);
            printf("Enter director investments: ");
            scanf("%u", &director.investments);
            printf("Enter director rating: ");
            scanf("%lf", &director.rating);
            printf("Enter director startup birthdate in format 'dd.mm.yyyy': ");
            scanf("%u.%u.%u", &director.day, &director.month, &director.year);

            directors_db_update(directors_db, &director);

            system("cls");
        } else if (ch == '5') {
            printf("Enter id to delete: ");
            size_t id;
            scanf("%u", &id);

            directors_db_delete(directors_db, id);

            system("cls");
        } else if (ch == '6') {
            size_t k;
            size_t p;
            printf("Enter K: ");
            scanf("%u", &k);
            printf("Enter P: ");
            scanf("%u", &p);
            printf("\n");

            director_t directors[64];
            size_t directorsAmmount;
            directors_db_filter(directors_db, directors, &directorsAmmount, k, p);
            directors_print(directors, directorsAmmount);
            printf("\nPress any key to menu\n");
            _getch();
            system("cls");
        } else if (ch == 'e') {
            break;
        }
    }

    directors_db_close(directors_db);

    return 0;
}
