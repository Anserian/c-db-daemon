#include "jsonapi.h"

void show_json_error()
{
    const char *json_error = cJSON_GetErrorPtr();

    if (json_error != NULL)
    {
        fprintf(stderr, "Error before: %s\n", json_error);
    }
}

char* extract_json_string(cJSON* parent_object, const cJSON** target_object, char* key)
{
    *target_object = cJSON_GetObjectItemCaseSensitive(parent_object, key);

    const cJSON* object_value = *target_object;

    if (cJSON_IsString(object_value) && object_value->valuestring != NULL)
    {
        return object_value->valuestring;
    }

    return NULL;
};

database_instance_t* parse_initialization_request(const char* json_string)
{
    database_instance_t* instance = (database_instance_t*) malloc(sizeof(database_instance_t));
    instance->config;

    const cJSON* database_path = NULL;
    const cJSON* database_driver = NULL;
    const cJSON* tables = NULL;

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

    instance->config.path = extract_json_string(initialization_request, &database_path, "path");
    instance->config.driver = extract_json_string(initialization_request, &database_driver, "path");


    /*
    database_driver = cJSON_GetObjectItemCaseSensitive(initialization_request, "driver");
    if (cJSON_IsString(database_driver) && database_driver->valuestring != NULL)
    {
        instance->path = database_driver->valuestring;
    }
    */
}
