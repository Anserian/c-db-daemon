#include "sqlite.h"

database_instance_t* create_sqlite_instance(database_config_t config)
{
    database_instance_t* instance = (database_instance_t*) malloc(sizeof(database_instance_t));

    instance->connection = malloc(sizeof(sqlite3*));

    instance->config = config;

    instance->tables = NULL;

    instance->initialize_database = initialize_database_sqlite;
    instance->show_database_error = show_sqlite_error;
    instance->async_execute_sql = async_execute_sql_sqlite;

    return instance;
}

void* show_sqlite_error(database_instance_t* instance, char* error_message)
{
    fprintf(stderr, DATABASE_ERROR, error_message, sqlite3_errmsg(instance->connection));

    return NULL;
}

int default_sqlite_callback(void *null_arg, int argc, char **argv, char **col_name) {
    int i;
    
    for(i = 0; i<argc; i++) {
        printf("%s = %s\n", col_name[i], argv[i] ? argv[i] : "NULL");
    }
    
    printf("\n");
    return 0;
}

void* initialize_database_sqlite(database_instance_t* instance)
{
    sqlite3* db;

    int return_code = sqlite3_open(instance->config.path, &db);

    if (return_code)
    {
        instance->show_database_error(instance, "Couldn't open database");

        exit(1);
    }

    instance->connection = db;

    return NULL;
}

void* async_execute_sql_sqlite(database_instance_t* instance, char* sql_statement)
{
    char* error_message = 0;

    int return_code = sqlite3_exec(instance->connection, sql_statement, default_sqlite_callback, 0, &error_message);

    if (return_code != 0)
    {
        instance->show_database_error(instance, "Error executing sql");
    }

    return NULL;
}
