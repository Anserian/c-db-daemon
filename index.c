#include "database.h"

int main()
{
    sqlite3* database;

    database_config_t config = {
        .path = "./test.db"
    };

    list_node_t* field_list = (list_node_t*) malloc(sizeof(list_node_t));
    field_list->item = (database_field_t*) malloc(sizeof(database_field_t));

    database_field_t* field = field_list->item;

    field->name = "testcolumn";
    field->data_type = "CHAR(50)";
    field_list->next = NULL;

    database_table_t test_table = {
        .name = "testtable",
        .fields = field_list
    };

    initialize_database(&database, config);

    prepare_create_table(database, test_table);

    sqlite3_close(database);
    
    free(field_list->item);
    free(field_list);
};
