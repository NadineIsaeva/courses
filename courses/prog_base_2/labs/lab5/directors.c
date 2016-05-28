#include "directors.h"

#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>

struct directors_s {
    sqlite3 *db;
};

directors_t *directors_create() {
    const char *sql;
    sqlite3_stmt *stmt;

    directors_t *directors = malloc(sizeof(directors_t));
    sqlite3_open("directors.db", &directors->db);

    sql = "SELECT name FROM sqlite_master WHERE type='table' AND name='startups';";
    sqlite3_prepare_v2(directors->db, sql, -1, &stmt, NULL);

    int status = sqlite3_step(stmt);
    if (status != SQLITE_ROW) {
        sql =   "CREATE TABLE `startups` (" \
                "`id` INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT UNIQUE," \
                "`name` TEXT NOT NULL," \
                "`country` TEXT NOT NULL);";
        sqlite3_prepare_v2(directors->db, sql, -1, &stmt, NULL);
        sqlite3_step(stmt);
    }
    sqlite3_finalize(stmt);

    sql = "SELECT name FROM sqlite_master WHERE type='table' AND name='directors';";
    sqlite3_prepare_v2(directors->db, sql, -1, &stmt, NULL);

    status = sqlite3_step(stmt);
    if (status != SQLITE_ROW) {
        sqlite3_finalize(stmt);

        sql =   "CREATE TABLE `directors` (" \
                "`id` INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT UNIQUE," \
                "`name` TEXT NOT NULL," \
                "`surname` TEXT NOT NULL," \
                "`salary` INTEGER NOT NULL DEFAULT 0," \
                "`rating` REAL NOT NULL," \
                "`birthdate` TEXT NOT NULL," \
                "`startup_id` INTEGER NOT NULL," \
                "FOREIGN KEY(startup_id) REFERENCES startups(id));";
        sqlite3_prepare_v2(directors->db, sql, -1, &stmt, NULL);
        sqlite3_step(stmt);
    }
    sqlite3_finalize(stmt);

    return directors;
}

size_t directors_count(directors_t *directors) {
    const char *sql;
    sqlite3_stmt *stmt;

    sql = "SELECT COUNT(*) FROM directors;";
    sqlite3_prepare_v2(directors->db, sql, -1, &stmt, NULL);
    sqlite3_step(stmt);
    size_t count = sqlite3_column_int(stmt, 0);
    sqlite3_finalize(stmt);
    return count;
}

void directors_insert(directors_t *directors, const director_t *director) {
    const char *sql;
    sqlite3_stmt *stmt;

    sql =   "INSERT INTO " \
            "startups (name,country)" \
            "VALUES (?,?);";
    sqlite3_prepare_v2(directors->db, sql, -1, &stmt, NULL);

    sqlite3_bind_text(stmt, 1, director->startup.name, -1, NULL);
    sqlite3_bind_text(stmt, 2, director->startup.country, -1, NULL);

    sqlite3_step(stmt);
    sqlite3_finalize(stmt);

    sql = "SELECT id FROM startups ORDER BY id DESC LIMIT 1;";
    sqlite3_prepare_v2(directors->db, sql, -1, &stmt, NULL);
    sqlite3_step(stmt);
    size_t lastStartupId = sqlite3_column_int(stmt, 0);
    sqlite3_finalize(stmt);

    sql =   "INSERT INTO " \
            "directors (name,surname,salary,rating,birthdate,startup_id)" \
            "VALUES (?,?,?,?,?,?);";
    sqlite3_prepare_v2(directors->db, sql, -1, &stmt, NULL);

    sqlite3_bind_text(stmt, 1, director->name, -1, NULL);
    sqlite3_bind_text(stmt, 2, director->surname, -1, NULL);
    sqlite3_bind_int(stmt, 3, director->salary);
    sqlite3_bind_double(stmt, 4, director->rating);
    char buffer[64];
    sprintf(buffer, "%i-%i-%i", director->birthdate.tm_year + 1900, director->birthdate.tm_mon + 1, director->birthdate.tm_mday);
    sqlite3_bind_text(stmt, 5, buffer, -1, NULL);
    sqlite3_bind_int(stmt, 6, lastStartupId);

    sqlite3_step(stmt);
    sqlite3_finalize(stmt);
}

director_t *directorPersistantPtr = NULL;

const director_t *directors_get(directors_t *directors, size_t id) {
    if (directorPersistantPtr) {
        free(directorPersistantPtr);
        directorPersistantPtr = NULL;
    }

    const char *sql;
    sqlite3_stmt *stmt;

    sql = "SELECT * FROM directors WHERE id=?;";
    sqlite3_prepare_v2(directors->db, sql, -1, &stmt, NULL);
    sqlite3_bind_int(stmt, 1, id);
    int status = sqlite3_step(stmt);

    if (status == SQLITE_ROW) {
        directorPersistantPtr = malloc(sizeof(director_t));

        directorPersistantPtr->id = sqlite3_column_int(stmt, 0);
        strcpy(directorPersistantPtr->name, (const char *)sqlite3_column_text(stmt, 1));
        strcpy(directorPersistantPtr->surname, (const char *)sqlite3_column_text(stmt, 2));
        directorPersistantPtr->salary = sqlite3_column_int(stmt, 3);
        directorPersistantPtr->rating = sqlite3_column_double(stmt, 4);
        sscanf((const char *)sqlite3_column_text(stmt, 5), "%i-%i-%i", &directorPersistantPtr->birthdate.tm_year, &directorPersistantPtr->birthdate.tm_mon, &directorPersistantPtr->birthdate.tm_mday);
        directorPersistantPtr->birthdate.tm_year -= 1900;
        directorPersistantPtr->birthdate.tm_mon -= 1;

        size_t startupId = sqlite3_column_int(stmt, 6);

        sqlite3_finalize(stmt);

        sql = "SELECT * FROM startups WHERE id=?;";
        sqlite3_prepare_v2(directors->db, sql, -1, &stmt, NULL);
        sqlite3_bind_int(stmt, 1, startupId);
        sqlite3_step(stmt);

        strcpy(directorPersistantPtr->startup.name, (const char *)sqlite3_column_text(stmt, 1));
        strcpy(directorPersistantPtr->startup.country, (const char *)sqlite3_column_text(stmt, 2));
    }

    sqlite3_finalize(stmt);

    return directorPersistantPtr;
}

void directors_get_all(directors_t *directors, const director_t **directorArray, size_t *count) {
    if (directorPersistantPtr)
        free(directorPersistantPtr);
    directorPersistantPtr = malloc(0);

    const char *sql;
    sqlite3_stmt *stmt;

    sql = "SELECT * FROM directors;";
    sqlite3_prepare_v2(directors->db, sql, -1, &stmt, NULL);
    int status;
    *count = 0;
    while (1) {
        status = sqlite3_step(stmt);

        if (status == SQLITE_ROW) {
            const char *startupSql = "SELECT * FROM startups;";
            sqlite3_stmt *startupStmt;

            directorPersistantPtr = realloc(directorPersistantPtr, (*count + 1) * sizeof(director_t));

            directorPersistantPtr[*count].id = sqlite3_column_int(stmt, 0);
            strcpy(directorPersistantPtr[*count].name, (const char *)sqlite3_column_text(stmt, 1));
            strcpy(directorPersistantPtr[*count].surname, (const char *)sqlite3_column_text(stmt, 2));
            directorPersistantPtr[*count].salary = sqlite3_column_int(stmt, 3);
            directorPersistantPtr[*count].rating = sqlite3_column_double(stmt, 4);
            sscanf((const char *)sqlite3_column_text(stmt, 5), "%i-%i-%i", &directorPersistantPtr[*count].birthdate.tm_year, &directorPersistantPtr[*count].birthdate.tm_mon, &directorPersistantPtr[*count].birthdate.tm_mday);
            directorPersistantPtr[*count].birthdate.tm_year -= 1900;
            directorPersistantPtr[*count].birthdate.tm_mon -= 1;

            size_t startupId = sqlite3_column_int(stmt, 6);

            startupSql = "SELECT * FROM startups WHERE id=?;";
            sqlite3_prepare_v2(directors->db, startupSql, -1, &startupStmt, NULL);
            sqlite3_bind_int(startupStmt, 1, startupId);
            sqlite3_step(startupStmt);

            strcpy(directorPersistantPtr[*count].startup.name, (const char *)sqlite3_column_text(startupStmt, 1));
            strcpy(directorPersistantPtr[*count].startup.country, (const char *)sqlite3_column_text(startupStmt, 2));

            sqlite3_finalize(startupStmt);

            ++(*count);
        } else
            break;
    }

    *directorArray = directorPersistantPtr;

    sqlite3_finalize(stmt);
}

int directors_remove(directors_t *directors, size_t id) {
    const char *sql;
    sqlite3_stmt *stmt;

    sql = "SELECT startup_id FROM directors WHERE id=?;";
    sqlite3_prepare_v2(directors->db, sql, -1, &stmt, NULL);
    sqlite3_bind_int(stmt, 1, id);
    sqlite3_step(stmt);
    size_t startupId = sqlite3_column_int(stmt, 0);
    sqlite3_finalize(stmt);

    sql =   "DELETE FROM directors " \
            "WHERE id=?;";
    sqlite3_prepare_v2(directors->db, sql, -1, &stmt, NULL);
    sqlite3_bind_int(stmt, 1, id);
    sqlite3_step(stmt);
    sqlite3_finalize(stmt);

    sql =   "DELETE FROM startups " \
            "WHERE id=?;";
    sqlite3_prepare_v2(directors->db, sql, -1, &stmt, NULL);
    sqlite3_bind_int(stmt, 1, startupId);
    sqlite3_step(stmt);
    sqlite3_finalize(stmt);

    return 1;
}

void directors_filter(directors_t *directors, const director_t **directorArray, size_t *count, size_t k, size_t p) {
    if (directorPersistantPtr)
        free(directorPersistantPtr);
    directorPersistantPtr = malloc(0);

    const char *sql;
    sqlite3_stmt *stmt;

    sql = "SELECT * FROM directors WHERE birthdate < date('now','-%u years') AND salary < %u;";
    char buffer[1024];
    sprintf(buffer, sql, p, k);
    sqlite3_prepare_v2(directors->db, buffer, -1, &stmt, NULL);
    int status;
    *count = 0;
    while (1) {
        status = sqlite3_step(stmt);

        if (status == SQLITE_ROW) {
            const char *startupSql = "SELECT * FROM startups;";
            sqlite3_stmt *startupStmt;

            directorPersistantPtr = realloc(directorPersistantPtr, (*count + 1) * sizeof(director_t));

            directorPersistantPtr[*count].id = sqlite3_column_int(stmt, 0);
            strcpy(directorPersistantPtr[*count].name, (const char *)sqlite3_column_text(stmt, 1));
            strcpy(directorPersistantPtr[*count].surname, (const char *)sqlite3_column_text(stmt, 2));
            directorPersistantPtr[*count].salary = sqlite3_column_int(stmt, 3);
            directorPersistantPtr[*count].rating = sqlite3_column_double(stmt, 4);
            sscanf((const char *)sqlite3_column_text(stmt, 5), "%i-%i-%i", &directorPersistantPtr[*count].birthdate.tm_year, &directorPersistantPtr[*count].birthdate.tm_mon, &directorPersistantPtr[*count].birthdate.tm_mday);
            directorPersistantPtr[*count].birthdate.tm_year -= 1900;
            directorPersistantPtr[*count].birthdate.tm_mon -= 1;

            size_t startupId = sqlite3_column_int(stmt, 6);

            startupSql = "SELECT * FROM startups WHERE id=?;";
            sqlite3_prepare_v2(directors->db, startupSql, -1, &startupStmt, NULL);
            sqlite3_bind_int(startupStmt, 1, startupId);
            sqlite3_step(startupStmt);

            strcpy(directorPersistantPtr[*count].startup.name, (const char *)sqlite3_column_text(startupStmt, 1));
            strcpy(directorPersistantPtr[*count].startup.country, (const char *)sqlite3_column_text(startupStmt, 2));

            sqlite3_finalize(startupStmt);

            ++(*count);
        } else
            break;
    }

    *directorArray = directorPersistantPtr;

    sqlite3_finalize(stmt);
}

void directors_delete(directors_t *directors) {
    sqlite3_close(directors->db);
    free(directors);
}
