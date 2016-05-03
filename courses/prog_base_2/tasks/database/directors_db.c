#include "directors_db.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sqlite3.h>

struct directors_db_s {
    sqlite3 *db;
};

directors_db_t *directors_db_open(const char *fileName) {
    const char *sql;
    sqlite3_stmt *stmt;
    directors_db_t *directors_db = malloc(sizeof(directors_db_t));
    sqlite3_open(fileName, &directors_db->db);

    sql = "SELECT name FROM sqlite_master WHERE type='table' AND name='directors';";
    sqlite3_prepare_v2(directors_db->db, sql, -1, &stmt, NULL);

    int status = sqlite3_step(stmt);
    if (status != SQLITE_ROW) {
        sqlite3_finalize(stmt);

        sql =   "CREATE TABLE `directors` (" \
                "`id` INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT UNIQUE," \
                "`name` TEXT NOT NULL," \
                "`surname` TEXT NOT NULL," \
                "`investments` INTEGER NOT NULL," \
                "`rating` REAL NOT NULL," \
                "`birthdate` TEXT NOT NULL);";
        sqlite3_prepare_v2(directors_db->db, sql, -1, &stmt, NULL);
        sqlite3_step(stmt);
    }

    sqlite3_finalize(stmt);

    return directors_db;
}

void directors_db_insert(directors_db_t *directors_db, director_t *director) {
    const char *sql;
    sqlite3_stmt *stmt;

    sql =   "INSERT INTO " \
            "directors (name,surname,investments,rating,birthdate)" \
            "VALUES (?,?,?,?,?);";
    sqlite3_prepare_v2(directors_db->db, sql, -1, &stmt, NULL);

    sqlite3_bind_text(stmt, 1, director->name, -1, NULL);
    sqlite3_bind_text(stmt, 2, director->surname, -1, NULL);
    sqlite3_bind_int(stmt, 3, director->investments);
    sqlite3_bind_double(stmt, 4, director->rating);
    char buffer[64];
    sprintf(buffer, "%u-%u-%u", director->year, director->month, director->day);
    sqlite3_bind_text(stmt, 5, buffer, -1, NULL);

    sqlite3_step(stmt);

    sqlite3_finalize(stmt);
}

void directors_db_readAll(directors_db_t *directors_db, director_t *directorArr, size_t *ammount) {
    const char *sql;
    sqlite3_stmt *stmt;

    sql = "SELECT * FROM directors;";
    sqlite3_prepare_v2(directors_db->db, sql, -1, &stmt, NULL);
    int status;
    *ammount = 0;
    while (1) {
        status = sqlite3_step(stmt);

        if (status == SQLITE_ROW) {
            directorArr[*ammount].id = sqlite3_column_int(stmt, 0);
            strcpy(directorArr[*ammount].name, (const char *)sqlite3_column_text(stmt, 1));
            strcpy(directorArr[*ammount].surname, (const char *)sqlite3_column_text(stmt, 2));
            directorArr[*ammount].investments = sqlite3_column_int(stmt, 3);
            directorArr[*ammount].rating = sqlite3_column_double(stmt, 4);

            sscanf((const char *)sqlite3_column_text(stmt, 5), "%u-%u-%u", &directorArr[*ammount].year, &directorArr[*ammount].month, &directorArr[*ammount].day);

            ++(*ammount);
        } else
            break;
    }

    sqlite3_finalize(stmt);
}

int directors_db_readById(directors_db_t *directors_db, director_t *director, size_t id) {
    const char *sql;
    sqlite3_stmt *stmt;

    sql = "SELECT * FROM directors WHERE id=?;";
    sqlite3_prepare_v2(directors_db->db, sql, -1, &stmt, NULL);
    sqlite3_bind_int(stmt, 1, id);
    int status = sqlite3_step(stmt);

    if (status == SQLITE_ROW) {
        director->id = sqlite3_column_int(stmt, 0);
        strcpy(director->name, (const char *)sqlite3_column_text(stmt, 1));
        strcpy(director->surname, (const char *)sqlite3_column_text(stmt, 2));
        director->investments = sqlite3_column_int(stmt, 3);
        director->rating = sqlite3_column_double(stmt, 4);

        sscanf((const char *)sqlite3_column_text(stmt, 5), "%u-%u-%u", &director->year, &director->month, &director->day);

        return 1;
    }

    return 0;
}

void directors_db_update(directors_db_t *directors_db, director_t *director) {
    const char *sql;
    sqlite3_stmt *stmt;

    sql =   "UPDATE directors " \
            "SET name=?,surname=?,investments=?,rating=?,birthdate=? " \
            "WHERE id=?;";
    sqlite3_prepare_v2(directors_db->db, sql, -1, &stmt, NULL);

    sqlite3_bind_text(stmt, 1, director->name, -1, NULL);
    sqlite3_bind_text(stmt, 2, director->surname, -1, NULL);
    sqlite3_bind_int(stmt, 3, director->investments);
    sqlite3_bind_double(stmt, 4, director->rating);
    char buffer[64];
    sprintf(buffer, "%u-%u-%u", director->year, director->month, director->day);
    sqlite3_bind_text(stmt, 5, buffer, -1, NULL);

    sqlite3_bind_int(stmt, 6, director->id);

    sqlite3_step(stmt);

    sqlite3_finalize(stmt);
}

void directors_db_delete(directors_db_t *directors_db, size_t id) {
    const char *sql;
    sqlite3_stmt *stmt;

    sql =   "DELETE FROM directors " \
            "WHERE id=?;";
    sqlite3_prepare_v2(directors_db->db, sql, -1, &stmt, NULL);
    sqlite3_bind_int(stmt, 1, id);
    sqlite3_step(stmt);
    sqlite3_finalize(stmt);
}

size_t directors_db_count(directors_db_t *directors_db) {
    const char *sql;
    sqlite3_stmt *stmt;

    sql = "SELECT COUNT(*) FROM directors;";
    sqlite3_prepare_v2(directors_db->db, sql, -1, &stmt, NULL);
    sqlite3_step(stmt);
    size_t count = sqlite3_column_int(stmt, 0);
    sqlite3_finalize(stmt);
    return count;
}

void directors_db_filter(directors_db_t *directors_db, director_t *directorArr, size_t *ammount, size_t k, size_t p) {
    const char *sql;
    sqlite3_stmt *stmt;

    sql = "SELECT * FROM directors WHERE birthdate < date('now','-%u years') AND investments < %u;";
    char buffer[1024];
    sprintf(buffer, sql, p, k);
    sqlite3_prepare_v2(directors_db->db, buffer, -1, &stmt, NULL);
    int status;
    *ammount = 0;
    while (1) {
        status = sqlite3_step(stmt);

        if (status == SQLITE_ROW) {
            directorArr[*ammount].id = sqlite3_column_int(stmt, 0);
            strcpy(directorArr[*ammount].name, (const char *)sqlite3_column_text(stmt, 1));
            strcpy(directorArr[*ammount].surname, (const char *)sqlite3_column_text(stmt, 2));
            directorArr[*ammount].investments = sqlite3_column_int(stmt, 3);
            directorArr[*ammount].rating = sqlite3_column_double(stmt, 4);

            sscanf((const char *)sqlite3_column_text(stmt, 5), "%u-%u-%u", &directorArr[*ammount].year, &directorArr[*ammount].month, &directorArr[*ammount].day);

            ++(*ammount);
        } else
            break;
    }

    sqlite3_finalize(stmt);
}

void directors_db_close(directors_db_t *directors_db) {
    sqlite3_close(directors_db->db);
    free(directors_db);
}

void director_print(director_t *director) {
    printf("%u) %s %s: %u, %f, %u.%u.%u\n",
           director->id,
           director->name,
           director->surname,
           director->investments,
           director->rating,
           director->day,
           director->month,
           director->year);
}

void directors_print(director_t *directorArr, size_t ammount) {
    for (size_t i = 0; i < ammount; ++i)
        director_print(directorArr + i);
    printf("\n");
}
