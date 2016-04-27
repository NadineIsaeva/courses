#include "directors.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "cJSON.h"

struct directors_s {
    director_t *dirs;
    size_t size;
};

directors_t *directors_create(const char *file_name) {
    FILE *jsonFile = fopen(file_name, "r");

    fseek(jsonFile, 0, SEEK_END);
    long fileSize = ftell(jsonFile);
    fseek(jsonFile, 0, SEEK_SET);

    char *fileStr = malloc((fileSize + 1) * sizeof(char));
    fread(fileStr, fileSize, 1, jsonFile);
    fileStr[fileSize] = '\0';

    directors_t *directors = malloc(sizeof(directors_t));

    cJSON *jList = cJSON_Parse(fileStr);
    directors->size = cJSON_GetArraySize(jList);

    directors->dirs = malloc(directors->size * sizeof(director_t));

    for (int i = 0; i < directors->size; ++i) {
        cJSON *jItem = cJSON_GetArrayItem(jList, i);

        char *name = cJSON_GetObjectItem(jItem, "name")->valuestring;
        char *surname = cJSON_GetObjectItem(jItem, "surname")->valuestring;
        char *birthdate = cJSON_GetObjectItem(jItem, "birthdate")->valuestring;
        int salary = cJSON_GetObjectItem(jItem, "salary")->valueint;
        double rating = cJSON_GetObjectItem(jItem, "rating")->valuedouble;
        cJSON *startup = cJSON_GetObjectItem(jItem, "startup");
        char *startup_name = cJSON_GetObjectItem(startup, "name")->valuestring;
        char *startup_country = cJSON_GetObjectItem(startup, "country")->valuestring;

        directors->dirs[i].name = malloc((strlen(name) + 1) * sizeof(char));
        strcpy(directors->dirs[i].name, name);

        directors->dirs[i].surname = malloc((strlen(surname) + 1) * sizeof(char));
        strcpy(directors->dirs[i].surname, surname);

        memset(&directors->dirs[i].birth_date, 0, sizeof(struct tm));
        sscanf(birthdate, "%i-%i-%i", &directors->dirs[i].birth_date.tm_year, &directors->dirs[i].birth_date.tm_mday, &directors->dirs[i].birth_date.tm_mon);

        directors->dirs[i].startup.name = malloc((strlen(startup_name) + 1) * sizeof(char));
        strcpy(directors->dirs[i].startup.name, startup_name);

        directors->dirs[i].startup.country = malloc((strlen(startup_country) + 1) * sizeof(char));
        strcpy(directors->dirs[i].startup.country, startup_country);

        directors->dirs[i].salary = salary;
        directors->dirs[i].rating = rating;
    }

    cJSON_Delete(jList);
    free(fileStr);
    fclose(jsonFile);

    return directors;
}

size_t directors_size(directors_t *directors) {
    return directors->size;
}

director_t *directors_get(directors_t *directors, size_t index) {
    if (index < directors->size)
        return directors->dirs + index;

    return NULL;
}

void directors_remove(directors_t *directors, size_t index) {
    if (index < directors->size) {
        director_t *director = directors->dirs + index;

        free(director->startup.name);
        free(director->startup.country);
        free(director->surname);
        free(director->name);

        memmove(directors->dirs + index, directors->dirs + index + 1, (directors->size - index - 1) * sizeof(director_t));
        --directors->size;
        directors->dirs = realloc(directors->dirs, directors->size * sizeof(director_t));
    }
}

void directors_print(directors_t *directors) {
    for (int i = 0; i < directors->size; ++i) {
        printf("Startup director #%i\n", i + 1);
        printf("Name: %s\n", directors->dirs[i].name);
        printf("Surname: %s\n", directors->dirs[i].surname);
        printf("Birthdate: %i-%i-%i\n", directors->dirs[i].birth_date.tm_year, directors->dirs[i].birth_date.tm_mday, directors->dirs[i].birth_date.tm_mon);
        printf("Startup: \n");
        printf("  Name: %s\n", directors->dirs[i].startup.name);
        printf("  Country: %s\n", directors->dirs[i].startup.country);
        printf("Salary: %i\n", directors->dirs[i].salary);
        printf("Rating: %f\n\n", directors->dirs[i].rating);
    }
}

void directors_delete(directors_t *directors) {
    for (int i = 0; i < directors->size; ++i) {
        free(directors->dirs[i].startup.country);
        free(directors->dirs[i].startup.name);
        free(directors->dirs[i].surname);
        free(directors->dirs[i].name);
    }

    free(directors->dirs);
    free(directors);
}

void director_update(director_t *director,
                     const char *name,
                     const char *surname,
                     const int *birthYear,
                     const int *birthDay,
                     const int *birthMonth,
                     const char *startupName,
                     const char *startupCountry,
                     const int *salary,
                     const double *rating)
{
    if (name) {
        free(director->name);
        director->name = malloc((strlen(name) + 1) * sizeof(char));
        strcpy(director->name, name);
    }
    if (surname) {
        free(director->surname);
        director->surname = malloc((strlen(surname) + 1) * sizeof(char));
        strcpy(director->surname, surname);
    }
    if (birthYear)
        director->birth_date.tm_year = *birthYear;
    if (birthDay)
        director->birth_date.tm_mday = *birthDay;
    if (birthMonth)
        director->birth_date.tm_mon = *birthMonth;
    if (startupName) {
        free(director->startup.name);
        director->startup.name = malloc((strlen(startupName) + 1) * sizeof(char));
        strcpy(director->startup.name, startupName);
    }
    if (startupCountry) {
        free(director->startup.country);
        director->startup.country = malloc((strlen(startupCountry) + 1) * sizeof(char));
        strcpy(director->startup.country, startupCountry);
    }
    if (salary)
        director->salary = *salary;
    if (rating)
        director->rating = *rating;
}
