#ifndef USER_H
#define USER_H

typedef struct user_s user_t;
typedef struct users_s users_t;

user_t *user_create(const char *name);
char *user_name(user_t *user);
void user_destroy(user_t *user);

users_t *users_create();
user_t *users_get(users_t *users, const char *name);
void users_destroy(users_t *users);

#endif // USER_H
