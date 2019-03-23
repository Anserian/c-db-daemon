#ifndef DATABASE_CNTRL
#define DATABASE_CNTRL

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "utils.h"

#define DATABASE_ERROR "Database error: %s: %s"

#define CREATE_TABLE "CREATE TABLE IF NOT EXISTS "
#define START_LIST " ("
#define END_LIST ") "
#define FIELD_SEPARATOR ","
#define TERMINATE_SQL ";\0"

typedef struct ListNode field_node_t;
typedef struct ListNode table_node_t;

typedef struct DatabaseConfig
{
    char *driver;
    bool verbose;
    char *path;
} database_config_t;

typedef struct DatabaseTable
{
    char *name;
    field_node_t *fields;
} database_table_t;

typedef struct DatabaseField
{
    char *name;
    char *data_type;
} database_field_t;

typedef struct DatabaseInstance
{
    struct DatabaseConfig config;
    void *connection;
    table_node_t *tables;
    char *prepared_statement;
    void *(*initialize_database)(struct DatabaseInstance *);
    void *(*show_database_error)(struct DatabaseInstance *, char *);
    void *(*async_execute_sql)(struct DatabaseInstance *, char *);
    bool (*execute_sql)(struct DatabaseInstance *, char *);
} database_instance_t;

void *free_instance(database_instance_t *);

void *free_table(void *);

void *initialize_table_node(table_node_t *);

database_table_t *add_table(database_instance_t *, char *);

bool match_table_node(void *, void *);

database_table_t *get_table_from_node(void *);

database_table_t *find_table(database_instance_t *, char *);

void *initialize_field_node(field_node_t *);

database_field_t *add_table_field(database_table_t *, char *, char *);

database_field_t *get_field_from_node(void *);

char *build_field_init_string(void *);

void *prepare_create_table(database_instance_t *, database_table_t *);

bool create_table(database_instance_t *, database_table_t *);

#endif
