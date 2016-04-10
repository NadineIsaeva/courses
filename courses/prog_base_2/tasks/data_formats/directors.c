#include "directors.h"

#include <stdio.h>
#include <time.h>
#include "cJSON.h"

typedef struct {
    char *name;
    char *country;
} startup_t;

typedef struct {
    char *name;
    char *surname;
    struct tm birth_date;
    startup_t startup;
    int salary;
    double rating;
} director_t;

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
