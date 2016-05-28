#ifndef DB_H
#define DB_H

#include "list.h"

typedef struct db_s db_t;

db_t *db_create();
list_t *db_directors(db_t *db);
void db_delete(db_t *db);

#endif // DB_H
