#include "jsonapi.h"

void show_json_error()
{
    const char *json_error = cJSON_GetErrorPtr();

    if (json_error != NULL)
    {
        fprintf(stderr, "JSON API error: %s\n", json_error);
    }
}

void extract_json_value(cJSON *parent_object, const cJSON **target_object, char *key)
{
    *target_object = cJSON_GetObjectItemCaseSensitive(parent_object, key);
}

char *extract_string_from_json(cJSON *parent_object, const cJSON **target_object, char *key)
{
    extract_json_value(parent_object, target_object, key);

    if (cJSON_IsString(*target_object) && (*target_object)->valuestring != NULL)
    {
        return (*target_object)->valuestring;
    }

    return NULL;
};

const cJSON *extract_object_from_json(cJSON *parent_object, const cJSON **target_object, char *key)
{
    extract_json_value(parent_object, target_object, key);

    if (cJSON_IsObject(*target_object) && (*target_object)->child != NULL)
    {
        return (*target_object)->child;
    }

    return NULL;
}

void extract_field_list_from_json(const cJSON *fields_object, database_table_t *table)
{
    cJSON *current_field_object = NULL;

    cJSON_ArrayForEach(current_field_object, fields_object)
    {
        const cJSON *field_name = NULL;
        const cJSON *data_type = NULL;

        database_field_t *current_field = add_table_field(table, extract_string_from_json(current_field_object, &field_name, "name"),
                                                          extract_string_from_json(current_field_object, &data_type, "data_type"));
    }
}

void extract_table_list_from_json(const cJSON *tables_object, database_instance_t *instance)
{
    cJSON *current_table_object = NULL;

    cJSON_ArrayForEach(current_table_object, tables_object)
    {
        const cJSON *table_name = NULL;
        const cJSON *fields = NULL;

        database_table_t *current_table = add_table(instance, extract_string_from_json(current_table_object, &table_name, "name"));

        extract_object_from_json(current_table_object, &fields, "fields");

        extract_field_list_from_json(fields, current_table);
    }
}

database_instance_t *parse_initialization_request(const char *json_string)
{
    database_config_t config;

    const cJSON *database_path = NULL;
    const cJSON *database_driver = NULL;
    const cJSON *tables = NULL;

    cJSON *initialization_request = cJSON_Parse(json_string);

    if (initialization_request == NULL)
    {
        const char *json_error = cJSON_GetErrorPtr();

        if (json_error != NULL)
        {
            show_json_error();
            return NULL;
        }
    }

    config.path = extract_string_from_json(initialization_request, &database_path, "path");
    config.driver = extract_string_from_json(initialization_request, &database_driver, "path");

    database_instance_t *instance = create_sqlite_instance(config);
    instance->initialize_database(instance);

    extract_object_from_json(initialization_request, &tables, "tables");
    extract_table_list_from_json(tables, instance);

    return instance;
}
