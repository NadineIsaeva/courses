#include "doc.h"
#include "user.h"

#include <stdlib.h>
#include <string.h>

struct doc_s {
    char *name;
    char *text;
    doc_user_t *users;
    size_t numberOfUsers;
    doc_modification_t *modifications;
    size_t numberOfModifications;
    doc_callback_func_t *callbacks;
    size_t numberOfCallbacks;
};

doc_t *doc_create(const char *name, const char *text) {
    doc_t *doc = malloc(sizeof(doc_t));
    doc->name = malloc((strlen(name) + 1) * sizeof(char));
    strcpy(doc->name, name);
    doc->text = malloc((strlen(text) + 1) * sizeof(char));
    strcpy(doc->text, text);
    doc->users = malloc(0);
    doc->numberOfUsers = 0;
    doc->modifications = malloc(0);
    doc->numberOfModifications = 0;
    doc->callbacks = malloc(0);
    doc->numberOfCallbacks = 0;
    return doc;
}

doc_user_t *findUser(user_t *user, doc_user_t *users, size_t numberOfUsers) {
    for (size_t i = 0; i < numberOfUsers; ++i)
        if (users[i].user == user)
        return users + i;
    return NULL;
}

const doc_user_t *doc_users(doc_t *doc, size_t *numberOfUsers) {
    *numberOfUsers = doc->numberOfUsers;
    return doc->users;
}

void doc_addUser(doc_t *doc, user_t *user, int canEdit) {
    if (!findUser(user, doc->users, doc->numberOfUsers)) {
        ++doc->numberOfUsers;
        doc->users = realloc(doc->users, sizeof(doc_user_t) * doc->numberOfUsers);
        doc->users[doc->numberOfUsers - 1].user = user;
        doc->users[doc->numberOfUsers - 1].canEdit = canEdit;
    }
}

void doc_removeUser(doc_t *doc, user_t *user) {
    doc_user_t *userToDelete = findUser(user, doc->users, doc->numberOfUsers);

    if (userToDelete) {
        memmove(userToDelete, userToDelete + 1, (doc->numberOfUsers - (userToDelete - doc->users) - 1) * sizeof(doc_user_t));
        --doc->numberOfUsers;
        doc->users = realloc(doc->users, doc->numberOfUsers * sizeof(doc_user_t));
    }
}

const char *doc_name(doc_t *doc) {
    return doc->name;
}

void doc_changeName(doc_t *doc, const char *name) {
    free(doc->name);
    doc->name = malloc((strlen(name) + 1) * sizeof(char));
    strcpy(doc->name, name);
}

const doc_modification_t *doc_modifications(doc_t *doc, size_t *numberOfModifications) {
    *numberOfModifications = doc->numberOfModifications;
    return doc->modifications;
}

int doc_text(doc_t *doc, user_t *user, char *text) {
    if (findUser(user, doc->users, doc->numberOfUsers)) {
        strcpy(text, doc->text);

        for (size_t i = 0; i < doc->numberOfModifications; ++i) {
            memmove(text + doc->modifications[i].pos, text + doc->modifications[i].pos + doc->modifications[i].length, ((strlen(text) + 1) - (doc->modifications[i].pos + doc->modifications[i].length)) * sizeof(char));
            memmove(text + doc->modifications[i].pos + strlen(doc->modifications[i].text), text + doc->modifications[i].pos, ((strlen(text) + 1) - doc->modifications[i].pos) * sizeof(char));
            memmove(text + doc->modifications[i].pos, doc->modifications[i].text, strlen(doc->modifications[i].text) * sizeof(char));
        }

        return 1;
    }

    return 0;
}

int doc_modify(doc_t *doc, user_t *user, size_t pos, size_t length, const char *text) {
    doc_user_t *docUser = findUser(user, doc->users, doc->numberOfUsers);
    if (docUser && docUser->canEdit) {
        ++doc->numberOfModifications;
        doc->modifications = realloc(doc->modifications, doc->numberOfModifications * sizeof(doc_modification_t));
        doc->modifications[doc->numberOfModifications - 1].pos = pos;
        doc->modifications[doc->numberOfModifications - 1].length = length;
        doc->modifications[doc->numberOfModifications - 1].user = user;
        doc->modifications[doc->numberOfModifications - 1].text = malloc((strlen(text) + 1) * sizeof(char));
        strcpy(doc->modifications[doc->numberOfModifications - 1].text, text);
        time_t currentTime = time(NULL);
        memcpy(&doc->modifications[doc->numberOfModifications - 1].time, localtime(&currentTime), sizeof(struct tm));

        for (size_t i = 0; i < doc->numberOfCallbacks; ++i)
            doc->callbacks[i](doc, &doc->modifications[doc->numberOfModifications - 1]);

        return 1;
    }

    return 0;
}

void doc_subscribe(doc_t *doc, doc_callback_func_t doc_callback_func) {
    ++doc->numberOfCallbacks;
    doc->callbacks = realloc(doc->callbacks, doc->numberOfCallbacks * sizeof(doc_callback_func_t));
    doc->callbacks[doc->numberOfCallbacks - 1] = doc_callback_func;
}

void doc_delete(doc_t *doc) {
    for (size_t i = 0; i < doc->numberOfModifications; ++i)
        free(doc->modifications[i].text);
    free(doc->users);
    free(doc->modifications);
    free(doc->callbacks);
    free(doc);
}
