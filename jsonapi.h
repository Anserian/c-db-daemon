#ifndef JSON_PARSE_DB_UTIL
#define JSON_PARSE_DB_UTIL

#include "include/cJSON.h"

#include "database.h"
#include "sqlite.h"
#include "utils.h"

void show_json_error();

void extract_json_value(cJSON *, const cJSON **, char *);

char *extract_string_from_json(cJSON *, const cJSON **, char *);

const cJSON *extract_object_from_json(cJSON *, const cJSON **, char *);

void extract_field_list_from_json(const cJSON *, database_table_t *);

void extract_table_list_from_json(const cJSON *, database_instance_t *);

database_instance_t *parse_initialization_request(const char *json_string);

#endif
