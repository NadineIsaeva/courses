#ifndef USER_H
#define USER_H

typedef struct user_s user_t;

user_t *user_create(const char *name);
const char *user_name(user_t *user);
void user_delete(user_t *user);

#endif // USER_H
