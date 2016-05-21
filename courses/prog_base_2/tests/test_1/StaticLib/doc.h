#ifndef DOC_H
#define DOC_H

#include "user.h"
#include <stdlib.h>
#include <time.h>

typedef struct doc_s doc_t;

typedef struct {
    user_t *user;
    int canEdit;
} doc_user_t;

typedef struct {
    size_t pos;
    size_t length;
    user_t *user;
    char *text;
    struct tm time;
} doc_modification_t;

typedef void (*doc_callback_func_t)(doc_t *doc, doc_modification_t *modification);

doc_t *doc_create(const char *name, const char *text);
const doc_user_t *doc_users(doc_t *doc, size_t *numberOfUsers);
void doc_addUser(doc_t *doc, user_t *user, int canEdit);
void doc_removeUser(doc_t *doc, user_t *user);
const char *doc_name(doc_t *doc);
void doc_changeName(doc_t *doc, const char *name);
const doc_modification_t *doc_modifications(doc_t *doc, size_t *numberOfModifications);
int doc_text(doc_t *doc, user_t *user, char *text);
int doc_modify(doc_t *doc, user_t *user, size_t pos, size_t length, const char *text);
void doc_subscribe(doc_t *doc, doc_callback_func_t doc_callback_func);
void doc_delete(doc_t *doc);

#endif // DOC_H

