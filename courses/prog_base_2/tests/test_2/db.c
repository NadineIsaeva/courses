#include "db.h"

#include <stdlib.h>
#include <sqlite3.h>
#include "director.h"

struct db_s {
    sqlite3 *db;
};

db_t *db_create() {
    const char *sql;
    sqlite3_stmt *stmt;

    db_t *db = malloc(sizeof(db_t));
    sqlite3_open("directors.db", &db->db);
    sql = "SELECT name FROM sqlite_master WHERE type='table' AND name='directors';";
    sqlite3_prepare_v2(db->db, sql, -1, &stmt, NULL);

    int status = sqlite3_step(stmt);
    if (status != SQLITE_ROW) {
        sqlite3_finalize(stmt);

        sql =   "CREATE TABLE `directors` (" \
                "`id` INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT UNIQUE," \
                "`name` TEXT NOT NULL," \
                "`surname` TEXT NOT NULL," \
                "`salary` INTEGER NOT NULL," \
                "`rating` REAL NOT NULL," \
                "`birthdate` TEXT NOT NULL," \
                "`startup_name` TEXT NOT NULL," \
                "`startup_country` TEXT NOT NULL);";
        sqlite3_prepare_v2(db->db, sql, -1, &stmt, NULL);
        sqlite3_step(stmt);
    }

    sqlite3_finalize(stmt);

    return db;
}

list_t *db_directors(db_t *db) {
    const char *sql;
    sqlite3_stmt *stmt;

    list_t *directors = list_create(director_dealloc);

    sql = "SELECT * FROM directors;";
    sqlite3_prepare_v2(db->db, sql, -1, &stmt, NULL);
    int status;
    while (1) {
        status = sqlite3_step(stmt);

        if (status == SQLITE_ROW) {
            director_t *director = malloc(sizeof(director_t));
            memset(director, 0, sizeof(director_t));

            director->id = sqlite3_column_int(stmt, 0);
            strcpy(director->name, (const char *)sqlite3_column_text(stmt, 1));
            strcpy(director->surname, (const char *)sqlite3_column_text(stmt, 2));
            director->salary = sqlite3_column_int(stmt, 3);
            director->rating = sqlite3_column_double(stmt, 4);

            sscanf((const char *)sqlite3_column_text(stmt, 5), "%i-%i-%i", &director->birthDate.tm_year, &director->birthDate.tm_mon, &director->birthDate.tm_mday);
            director->birthDate.tm_year -= 1900;
            director->birthDate.tm_mon -= 1;

            strcpy(director->startup.name, (const char *)sqlite3_column_text(stmt, 6));
            strcpy(director->startup.country, (const char *)sqlite3_column_text(stmt, 7));

            list_push(directors, director);
        } else
            break;
    }

    sqlite3_finalize(stmt);

    return directors;
}

void db_delete(db_t *db) {
    sqlite3_close(db->db);
    free(db);
}
