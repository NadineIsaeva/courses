#include "middleware.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include "cJSON.h"
#include "list.h"
#include "director.h"

struct middleware_s {
    http_client_t *http_client;
    db_t *db;
};

typedef struct {
    char key[128];
    char value[128];
} pair_t;

typedef struct {
    pair_t *pairs;
    size_t numberOfPairs;
} url_params_t;

url_params_t *url_params_parse(const char *urlParamsStr) {
    url_params_t *url_params = malloc(sizeof(url_params_t));
    url_params->pairs = malloc(0);
    url_params->numberOfPairs = 0;

    const char *paramStart = urlParamsStr;
    while (1) {
        const char *paramEnd = strchr(paramStart, '&');
        if (!paramEnd)
            paramEnd = strchr(paramStart, '\0');

        const char *equalCh = strchr(paramStart, '=');
        if (equalCh && (equalCh != paramStart) && (equalCh < paramEnd)) {
            pair_t pair;
            memcpy(pair.key, paramStart, equalCh - paramStart);
            pair.key[equalCh - paramStart] = '\0';
            memcpy(pair.value, equalCh + 1, paramEnd - (equalCh + 1));
            pair.value[paramEnd - (equalCh + 1)] = '\0';

            ++url_params->numberOfPairs;
            url_params->pairs = realloc(url_params->pairs, url_params->numberOfPairs * sizeof(pair_t));
            url_params->pairs[url_params->numberOfPairs - 1] = pair;
        }

        if (*paramEnd && *(paramEnd + 1))
            paramStart = paramEnd + 1;
        else
            break;
    }

    return url_params;
}

const char *url_params_get(url_params_t *url_params, const char *key) {
    for (size_t i = 0; i < url_params->numberOfPairs; ++i)
        if (strcmp(url_params->pairs[i].key, key) == 0)
            return url_params->pairs[i].value;
    return NULL;
}

void url_params_delete(url_params_t *url_params) {
    free(url_params->pairs);
    free(url_params);
}

int callback(middleware_t *middleware, http_method_t http_method, const char *url, const char *urlParamStr, const char *request, char *response) {
    if (strcmp(url, "/info") == 0) {
        cJSON *json = cJSON_CreateObject();
        cJSON_AddStringToObject(json, "student", "Nadine Isaeva");
        cJSON_AddStringToObject(json, "group", "KP-51");
        cJSON_AddNumberToObject(json, "variant", 37);
        strcpy(response, cJSON_Print(json));
        cJSON_Delete(json);
        return 1;
    } else if (strcmp(url, "/external") == 0) {
        char buffer[1024];
        http_client_request(middleware->http_client, "pb-homework.appspot.com", "/test/var/37?format=json", "GET", NULL, buffer);

        time_t currentTime = time(NULL);
        struct tm currentTimeTm = *localtime(&currentTime);
        char timeBuffer[128];
        sprintf(timeBuffer, "%i-%i-%i", currentTimeTm.tm_year + 1900, currentTimeTm.tm_mon + 1, currentTimeTm.tm_mday);

        cJSON *json = cJSON_Parse(buffer);
        cJSON_AddStringToObject(json, "time", timeBuffer);
        strcpy(response, cJSON_Print(json));
        cJSON_Delete(json);

        return 1;
    } else if (strcmp(url, "/database") == 0) {
        list_t *directors = db_directors(middleware->db);
        cJSON *json = cJSON_CreateArray();

        url_params_t *url_params = url_params_parse(urlParamStr);
        const char *nameStr = url_params_get(url_params, "name");
        const char *surnameStr = url_params_get(url_params, "surname");

        for (size_t i = 0; i < list_size(directors); ++i) {
            director_t *director = list_get(directors, i);
            if (nameStr && surnameStr)
                continue;
            if (nameStr && (strcmp(nameStr, director->name) != 0))
                continue;
            if (surnameStr && (strcmp(surnameStr, director->surname) != 0))
                continue;

            cJSON *jsonDir = cJSON_CreateObject();

            cJSON_AddNumberToObject(jsonDir, "id", director->id);
            cJSON_AddStringToObject(jsonDir, "name", director->name);
            cJSON_AddStringToObject(jsonDir, "surname", director->surname);
            cJSON_AddNumberToObject(jsonDir, "salary", director->salary);
            cJSON_AddNumberToObject(jsonDir, "rating", director->rating);
            char birthdateStr[128];
            sprintf(birthdateStr, "%i-%i-%i", director->birthDate.tm_year + 1900, director->birthDate.tm_mon + 1, director->birthDate.tm_mday);
            cJSON_AddStringToObject(jsonDir, "birthDate", birthdateStr);
            cJSON *jsonStartup = cJSON_CreateObject();
            cJSON_AddStringToObject(jsonStartup, "name", director->startup.name);
            cJSON_AddStringToObject(jsonStartup, "country", director->startup.country);
            cJSON_AddItemToObject(jsonDir, "startup", jsonStartup);

            cJSON_AddItemToArray(json, jsonDir);
        }

        strcpy(response, cJSON_Print(json));

        cJSON_Delete(json);
        list_delete(directors);
        return 1;
    }

    /*if (strcmp(url, "/api/directors") == 0) {
        if (http_method == http_method_get) {
            cJSON *json = cJSON_CreateArray();

            const director_t *directorArray;
            size_t numberOfDirectors;

            url_params_t *url_params = url_params_parse(urlParamStr);
            const char *kStr = url_params_get(url_params, "k");
            const char *pStr = url_params_get(url_params, "p");
            if (kStr && pStr) {
                size_t k = atoi(kStr);
                size_t p = atoi(pStr);

                directors_filter(middleware->directors, &directorArray, &numberOfDirectors, k, p);
            } else
                directors_get_all(middleware->directors, &directorArray, &numberOfDirectors);

            url_params_delete(url_params);

            for (size_t i = 0; i < numberOfDirectors; ++i) {
                const director_t *director = directorArray + i;

                cJSON *jsonDir = cJSON_CreateObject();
                cJSON_AddNumberToObject(jsonDir, "id", director->id);
                cJSON_AddStringToObject(jsonDir, "name", director->name);
                cJSON_AddStringToObject(jsonDir, "surname", director->surname);
                cJSON_AddNumberToObject(jsonDir, "salary", director->salary);
                cJSON_AddNumberToObject(jsonDir, "rating", director->rating);
                char birthdateStr[128];
                sprintf(birthdateStr, "%i-%i-%i", director->birthdate.tm_year + 1900, director->birthdate.tm_mon + 1, director->birthdate.tm_mday);
                cJSON_AddStringToObject(jsonDir, "birthdate", birthdateStr);
                cJSON *jsonStartup = cJSON_CreateObject();
                cJSON_AddStringToObject(jsonStartup, "name", director->startup.name);
                cJSON_AddStringToObject(jsonStartup, "country", director->startup.country);
                cJSON_AddItemToObject(jsonDir, "startup", jsonStartup);

                cJSON_AddItemToArray(json, jsonDir);
            }

            strcpy(response, cJSON_Print(json));
            cJSON_Delete(json);

            return 1;
        } else if (http_method == http_method_post) {
            cJSON *json = cJSON_Parse(request);

            if (json) {
                cJSON *jsonName = cJSON_GetObjectItem(json, "name");
                cJSON *jsonSurname = cJSON_GetObjectItem(json, "surname");
                cJSON *jsonSalary = cJSON_GetObjectItem(json, "salary");
                cJSON *jsonRating = cJSON_GetObjectItem(json, "rating");
                cJSON *jsonBirthdate = cJSON_GetObjectItem(json, "birthdate");
                cJSON *jsonStartup = cJSON_GetObjectItem(json, "startup");
                if (jsonName && jsonSurname && jsonSalary && jsonRating && jsonBirthdate && jsonStartup) {
                    cJSON *jsonStartupName = cJSON_GetObjectItem(jsonStartup, "name");
                    cJSON *jsonStartupCountry = cJSON_GetObjectItem(jsonStartup, "country");
                    if (jsonStartupName && jsonStartupCountry) {
                        director_t director;
                        strcpy(director.name, jsonName->valuestring);
                        strcpy(director.surname, jsonSurname->valuestring);
                        director.salary = jsonSalary->valueint;
                        director.rating = jsonRating->valuedouble;
                        memset(&director.birthdate, 0, sizeof(struct tm));
                        sscanf(jsonBirthdate->valuestring, "%i-%i-%i", &director.birthdate.tm_year, &director.birthdate.tm_mon, &director.birthdate.tm_mday);
                        director.birthdate.tm_year -= 1900;
                        director.birthdate.tm_mon -= 1;
                        strcpy(director.startup.name, jsonStartupName->valuestring);
                        strcpy(director.startup.country, jsonStartupCountry->valuestring);

                        directors_insert(middleware->directors, &director);
                        cJSON_Delete(json);

                        strcpy(response, "OK");

                        return 1;
                    }
                }
            }

            cJSON_Delete(json);
        }
    } else if (strncmp(url, "/api/directors/", strlen("/api/directors/")) == 0) {
        size_t directorId = atoi(strstr(strstr(url + 1, "/") + 1, "/") + 1);

        if (http_method == http_method_get) {
            const director_t *director = directors_get(middleware->directors, directorId);
            if (director) {
                cJSON *json = cJSON_CreateObject();

                cJSON_AddNumberToObject(json, "id", director->id);
                cJSON_AddStringToObject(json, "name", director->name);
                cJSON_AddStringToObject(json, "surname", director->surname);
                cJSON_AddNumberToObject(json, "salary", director->salary);
                cJSON_AddNumberToObject(json, "rating", director->rating);
                char birthdateStr[128];
                sprintf(birthdateStr, "%i-%i-%i", director->birthdate.tm_year + 1900, director->birthdate.tm_mon + 1, director->birthdate.tm_mday);
                cJSON_AddStringToObject(json, "birthdate", birthdateStr);
                cJSON *jsonStartup = cJSON_CreateObject();
                cJSON_AddStringToObject(jsonStartup, "name", director->startup.name);
                cJSON_AddStringToObject(jsonStartup, "country", director->startup.country);
                cJSON_AddItemToObject(json, "startup", jsonStartup);

                strcpy(response, cJSON_Print(json));
                cJSON_Delete(json);

                return 1;
            }
        } else if (http_method == http_method_delete) {
            if (directors_remove(middleware->directors, directorId)) {
                strcpy(response, "OK");
                return 1;
            }
        }
    } else if (strcmp(url, "/") == 0) {
        response[0] = 0;
        stradd(response, "<html><body><h1>Hello!</h1><br>");
        stradd(response, "<h2>Navigate to <a href=\"/directors\">directors list</a></h2><br>");
        stradd(response, "<h2>Navigate to <a href=\"/api/directors\">api</a></h2><br>");
        stradd(response, "<body><html>");
        return 1;
    } else if (strcmp(url, "/directors") == 0) {
        if (http_method == http_method_get) {
            response[0] = 0;
            stradd(response, "<html><body><h1>Directors</h1><br><ul>");

            const director_t *directorArray;
            size_t numberOfDirectors;

            url_params_t *url_params = url_params_parse(urlParamStr);
            const char *kStr = url_params_get(url_params, "k");
            const char *pStr = url_params_get(url_params, "p");
            if (kStr && pStr) {
                size_t k = atoi(kStr);
                size_t p = atoi(pStr);

                directors_filter(middleware->directors, &directorArray, &numberOfDirectors, k, p);
            } else
                directors_get_all(middleware->directors, &directorArray, &numberOfDirectors);

            url_params_delete(url_params);

            for (size_t i = 0; i < numberOfDirectors; ++i) {
                const director_t *director = directorArray + i;

                stradd(response, "<li>");
                char hrefBuffer[32];
                sprintf(hrefBuffer, "<a href=\"/directors/%u\">", director->id);
                stradd(response, hrefBuffer);
                stradd(response, director->name);
                stradd(response, " ");
                stradd(response, director->surname);
                stradd(response, "</a>");
                stradd(response, "</li>");
            }

            stradd(response, "</ul>");
            stradd(response, "<h2>Navigate to <a href=\"/new-director\">new director creation page</a></h2>");
            stradd(response, "</body></html>");

            return 1;
        } else if (http_method == http_method_post) {
            url_params_t *url_params = url_params_parse(request);

            const char *name = url_params_get(url_params, "name");
            const char *surname = url_params_get(url_params, "surname");
            const char *salary = url_params_get(url_params, "salary");
            const char *rating = url_params_get(url_params, "rating");
            const char *birthdate = url_params_get(url_params, "birthdate");
            const char *startupName = url_params_get(url_params, "startup_name");
            const char *startupCountry = url_params_get(url_params, "startup_country");

            director_t director;
            strcpy(director.name, name);
            strcpy(director.surname, surname);
            director.salary = atoi(salary);
            director.rating = atof(rating);
            memset(&director.birthdate, 0, sizeof(struct tm));
            sscanf(birthdate, "%i-%i-%i", &director.birthdate.tm_year, &director.birthdate.tm_mon, &director.birthdate.tm_mday);
            director.birthdate.tm_year -= 1900;
            director.birthdate.tm_mon -= 1;
            strcpy(director.startup.name, startupName);
            strcpy(director.startup.country, startupCountry);

            directors_insert(middleware->directors, &director);

            strcpy(response, "<html><body><h2>Successfully added</h2><br><h1><a href=\"/directors\">Go back</a></h2><br><h2><a href=\"/new-director\">Add new</a></h2></body></html>");

            return 1;
        }
    } else if (strncmp(url, "/directors/", strlen("/directors/")) == 0) {
        size_t directorId = atoi(strstr(url + 1, "/") + 1);

        if (http_method == http_method_get) {
            const director_t *director = directors_get(middleware->directors, directorId);
            if (director) {
                response[0] = 0;

                stradd(response, "<html><body><h1>Director: ");
                stradd(response, director->name);
                stradd(response, " ");
                stradd(response, director->surname);
                stradd(response, "</h1><br><ul>");

                char buffer[32];

                stradd(response, "<li>");
                stradd(response, "Salary: ");
                sprintf(buffer, "%u", director->salary);
                stradd(response, buffer);
                stradd(response, "</li>");

                stradd(response, "<li>");
                stradd(response, "Rating: ");
                sprintf(buffer, "%f", director->rating);
                stradd(response, buffer);
                stradd(response, "</li>");

                stradd(response, "<li>");
                stradd(response, "Birthdate: ");
                sprintf(buffer, "%i-%i-%i", director->birthdate.tm_year + 1900, director->birthdate.tm_mon + 1, director->birthdate.tm_mday);
                stradd(response, buffer);
                stradd(response, "</li>");

                stradd(response, "<li>Startup: <ul><li>");
                stradd(response, "Name: ");
                stradd(response, director->startup.name);
                stradd(response, "</li><li>");
                stradd(response, "Country: ");
                stradd(response, director->startup.country);
                stradd(response, "</li></ul></li></ul>");

                stradd(response, "<form method=\"post\" action=\"");
                stradd(response, url);
                stradd(response, "\"><button type=\"submit\"><h1>Delete</h1></button>");

                stradd(response, "</body></html>");

                return 1;
            }
        } else if (http_method == http_method_post) {
            if (directors_remove(middleware->directors, directorId)) {
                strcpy(response, "<html><body><h2>Successfully deleted</h2><br><h1><a href=\"/directors\">Go back</a></h2></body></html>");
                return 1;
            }
        }
    } else if (strcmp(url, "/new-director") == 0) {
        response[0] = 0;

        stradd(response, "<html><body><h1>Add new director</h1><br>");
        stradd(response, "<form method=\"post\" action=\"/directors\">");
        stradd(response, "Name: <input type=\"text\" name=\"name\"><br><br>");
        stradd(response, "Surname: <input type=\"text\" name=\"surname\"><br><br>");
        stradd(response, "Salary: <input type=\"text\" name=\"salary\"><br><br>");
        stradd(response, "Rating: <input type=\"text\" name=\"rating\"><br><br>");
        stradd(response, "Birthdate: <input type=\"text\" name=\"birthdate\"><br><br>");
        stradd(response, "Startup name: <input type=\"text\" name=\"startup_name\"><br><br>");
        stradd(response, "Startup country: <input type=\"text\" name=\"startup_country\"><br><br>");
        stradd(response, "<button type=\"Submit\">Submit</button>");
        stradd(response, "</form></body></html>");

        return 1;
    }*/

    return 0;
}

middleware_t *middleware_create(http_client_t *http_client, db_t *db) {
    middleware_t *middleware = malloc(sizeof(middleware_t));
    middleware->http_client = http_client;
    middleware->db = db;
    return middleware;
}

http_server_callback_t middleware_callback() {
    return callback;
}

void middleware_delete(middleware_t *middleware) {
    free(middleware);
}
