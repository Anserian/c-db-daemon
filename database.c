#include "database.h"

void show_database_error(sqlite3* database, char* error_message)
{
    fprintf(stderr, DATABASE_ERROR, error_message, sqlite3_errmsg(database));
}

int default_sqlite_callback(void *null_arg, int argc, char **argv, char **col_name) {
    int i;
    
    for(i = 0; i<argc; i++) {
        printf("%s = %s\n", col_name[i], argv[i] ? argv[i] : "NULL");
    }
    
    printf("\n");
    return 0;
}

bool initialize_database(sqlite3** database, database_config_t config)
{
    int return_code = sqlite3_open(config.path, database);

    if (return_code)
    {
        show_database_error(*database, "Couldn't open database");

        return false;
    }

    return true;
}

void* async_execute_sql(sqlite3* database, char* sql_statement)
{
    char* error_message = 0;

    int return_code = sqlite3_exec(database, sql_statement, default_sqlite_callback, 0, &error_message);

    if (return_code != SQLITE_OK)
    {
        show_database_error(database, "Error executing sql");
    }

    return NULL;
}

char* build_field_init_string(void* node)
{
    list_node_t* list_node = (list_node_t*) node; 

    database_field_t* current_field = (database_field_t*) list_node->item;

    return space_separate(current_field->name, current_field->data_type);
}

char* prepare_create_table(sqlite3* database, database_table_t table)
{
    char* create_table = space_separate(CREATE_TABLE, table.name);

    char* sql_statement = combine_strings(2, create_table, START_LIST);

    char* field_list = build_list((void*) table.fields, ", ", build_field_init_string, get_next_list_node);

    sql_statement = combine_strings(4, sql_statement, field_list, END_LIST, TERMINATE_SQL);

    free_all(2, create_table, sql_statement, field_list);

    return sql_statement;
}
