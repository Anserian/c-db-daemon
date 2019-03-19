#ifndef DATABASE_CNTRL
#define DATABASE_CNTRL

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <sqlite3.h>

#include "utils.h"

#define DATABASE_ERROR "Database error: %s: %s"

#define CREATE_TABLE "CREATE TABLE"
#define START_LIST " ("
#define END_LIST ") "
#define FIELD_SEPARATOR ","
#define TERMINATE_SQL ";\0"

typedef struct DatabaseConfig
{
    char* path;
} database_config_t;

typedef struct DatabaseTable
{
    char* name;
    struct ListNode* fields;
} database_table_t;

typedef struct DatabaseField
{
    char* name;
    char* data_type;
} database_field_t;

typedef struct DatabaseInstance
{
    sqlite3* connection;
    bool verbose;
} database_instance_t;

void show_database_error(sqlite3*, char*);

int default_sqlite_callback(void*, int, char**, char**);

void* async_execute_sql(sqlite3*, char*);

bool initialize_database(sqlite3**, database_config_t);

char* prepare_create_table(sqlite3*, database_table_t);

#endif
