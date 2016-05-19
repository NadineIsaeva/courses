#include "directors.h"

#include <stdlib.h>
#include <string.h>

struct directors_s {
    director_t *directorArray;
    size_t numberOfDirectors;
    size_t autoInc;
};

directors_t *directors_create() {
    directors_t *directors = malloc(sizeof(directors_t));
    directors->numberOfDirectors = 0;
    directors->directorArray = malloc(0);
    directors->autoInc = 1;
    return directors;
}

director_t *findDirector(director_t *directorArray, size_t size, size_t id) {
    for (size_t i = 0; i < size; ++i)
        if (directorArray[i].id == id)
            return directorArray + i;
    return NULL;
}

size_t directors_count(directors_t *directors) {
    return directors->numberOfDirectors;
}

void directors_insert(directors_t *directors, const director_t *director) {
    ++directors->numberOfDirectors;
    directors->directorArray = realloc(directors->directorArray, directors->numberOfDirectors * sizeof(director_t));
    directors->directorArray[directors->numberOfDirectors - 1] = *director;
    directors->directorArray[directors->numberOfDirectors - 1].id = directors->autoInc;
    ++directors->autoInc;
}

const director_t *directors_get(directors_t *directors, size_t id) {
    return findDirector(directors->directorArray, directors->numberOfDirectors, id);
}

void directors_get_all(directors_t *directors, const director_t **directorArray, size_t *count) {
    *directorArray = directors->directorArray;
    *count = directors->numberOfDirectors;
}

void directors_update(directors_t *directors, size_t id, const director_t *director) {
    director_t *directorToUpdate = findDirector(directors->directorArray, directors->numberOfDirectors, id);
    if (directorToUpdate) {
        *directorToUpdate = *director;
        directorToUpdate->id = id;
    }
}

int directors_remove(directors_t *directors, size_t id) {
    director_t *directorToDelete = findDirector(directors->directorArray, directors->numberOfDirectors, id);
    if (directorToDelete) {
        memmove(directorToDelete, directorToDelete + 1, (directors->numberOfDirectors - (directorToDelete - directors->directorArray) - 1) * sizeof(director_t));
        --directors->numberOfDirectors;
        directors->directorArray = realloc(directors->directorArray, directors->numberOfDirectors * sizeof(director_t));
        return 1;
    }
    return 0;
}

void directors_delete(directors_t *directors) {
    free(directors->directorArray);
    free(directors);
}
