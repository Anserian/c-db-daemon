#include "database.h"

// OBJECT MANAGEMENT

void *free_instance(database_instance_t *instance)
{
    for_each_list_node(instance->tables, free_table);

    free_all_nodes(instance->tables);

    return NULL;
}

void *free_table(void *node)
{
    table_node_t *table = (table_node_t *)node;

    database_table_t *table_item = (database_table_t *)table->item;

    free_all_nodes(table_item->fields);

    return NULL;
}

void *initialize_table_node(table_node_t *node)
{
    return (database_table_t *)malloc(sizeof(database_table_t));
}

database_table_t *add_table(database_instance_t *instance, char *name)
{
    table_node_t *new_table_node = append_list_node(instance->tables, initialize_table_node);

    if (instance->tables == NULL)
    {
        instance->tables = new_table_node;
    }

    database_table_t *table = new_table_node->item;

    table->name = name;
    table->fields = NULL;

    return table;
}

bool match_table_node(void *node, void *name)
{
    if (get_table_from_node(node)->name == (char *)name)
    {
        return true;
    }

    return false;
}

database_table_t *get_table_from_node(void *node)
{
    list_node_t *list_node = (list_node_t *)node;

    return (database_table_t *)list_node->item;
}

database_table_t *find_table(database_instance_t *instance, char *name)
{
    table_node_t *table_node = find_node(instance->tables, name, match_table_node);

    return (database_table_t *)table_node->item;
}

void *initialize_field_node(field_node_t *node)
{
    return (database_field_t *)malloc(sizeof(database_field_t));
}

database_field_t *add_table_field(database_table_t *table, char *name, char *data_type)
{
    field_node_t *new_field_node = append_list_node(table->fields, initialize_field_node);

    if (table->fields == NULL)
    {
        table->fields = new_field_node;
    }

    database_field_t *field = new_field_node->item;

    field->name = name;
    field->data_type = data_type;

    return field;
}

database_field_t *get_field_from_node(void *node)
{
    list_node_t *list_node = (list_node_t *)node;

    return (database_field_t *)list_node->item;
}

char *build_field_init_string(void *node)
{
    database_field_t *current_field = get_field_from_node(node);

    return space_separate(current_field->name, current_field->data_type);
}

// SQL

void *prepare_create_table(database_instance_t *instance, database_table_t *table)
{
    char *field_list = build_list((void *)table->fields, ", ", build_field_init_string, get_next_list_node);

    char *sql_statement = combine_strings(6, CREATE_TABLE, table->name, START_LIST, field_list, END_LIST, TERMINATE_SQL);

    instance->prepared_statement = strdup(sql_statement);

    free_all(2, sql_statement, field_list);

    return NULL;
}

bool create_table(database_instance_t *instance, database_table_t *table)
{
    prepare_create_table(instance, table);

    instance->async_execute_sql(instance, instance->prepared_statement);

    return true;
}
