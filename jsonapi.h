#ifndef JSON_PARSE_DB_UTIL
#define JSON_PARSE_DB_UTIL

#include "include/cJSON.h"

#include "database.h"
#include "sqlite.h"

void show_json_error();

char* extract_json_string(cJSON*, const cJSON**, char*);

database_instance_t* parse_initialization_request(const char* json_string);

#endif
