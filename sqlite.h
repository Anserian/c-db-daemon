#include <sqlite3.h>

#include "database.h"

typedef struct DatabaseInstance sqlite_instance_t;

database_instance_t* create_sqlite_instance(database_config_t);

int default_sqlite_callback(void*, int, char**, char**);

void* show_sqlite_error(database_instance_t*, char*);

void* initialize_database_sqlite(database_instance_t*);

void* async_execute_sql_sqlite(database_instance_t*, char*);
