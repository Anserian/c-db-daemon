#include "utils.h"

void* free_all(size_t nmemb, ...)
{
    va_list pointers;

    va_start(pointers, nmemb);

    for (int i = 0; i < nmemb; i++) {
        void* item = va_arg(pointers, void*);
        free(item);
    }

    return NULL;
}

list_node_t* initialize_list_node(list_node_t* node)
{
    node = (list_node_t*) malloc(sizeof(list_node_t));
    node->next = NULL;

    return node;
}

list_node_t* append_list_node(void* node)
{
    if ((list_node_t*) node == NULL)
    {
        return initialize_list_node((list_node_t*) node);
    }

    list_node_t* list_node = (list_node_t*) node;

    while(list_node != NULL)
    {
        list_node = (list_node_t*) get_next_list_node(list_node);
    }

    list_node->next = (list_node_t*) malloc(sizeof(list_node_t));

    if (list_node->next == NULL)
    {
        return NULL;
    }

    return list_node->next;
}

list_node_t* find_node(list_node_t* start_node, void* condition, bool (*condition_function) (void*, void*))
{
    list_node_t* index_node = start_node;

    while (index_node != NULL)
    {
        if (condition_function(index_node, condition))
        {
            return index_node;
        }

        index_node = (list_node_t*) get_next_list_node(index_node);
    }

    return NULL;
}

void* get_next_list_node(void* node)
{
    list_node_t* list_node = (list_node_t*) node;

    if (list_node->next != NULL)
    {
        return (void*) list_node->next;
    }

    return NULL;
}

void* for_each_list_node(void* first_node, void* (*operation_function) (void*))
{
    list_node_t* index_node = first_node;

    while (index_node != NULL)
    {
        operation_function(index_node);

        index_node = get_next_list_node(index_node);
    }

    return NULL;
}

char* build_list(void* item, char* separator, char* (*build_list_item) (void*), void* (*get_next) (void*))
{
    char* list = (char*) malloc(sizeof(char));

    if (list == NULL)
    {
        return NULL;
    }

    *list = '\0';

    while (item != NULL)
    {
        char* item_string = build_list_item(item);

        list = realloc(list, sizeof(char) * (strlen(list) + strlen(item_string)));

        if (list == NULL)
        {
            return NULL;
        }

        strcat(list, item_string);

        item = get_next(item);

        if (item != NULL)
        {
            list = realloc(list, sizeof(char) * (strlen(list) + strlen(separator)));

            if (list == NULL)
            {
                return NULL;
            }

            strcat(list, separator);
        }
    }

    return list;
}

char* combine_strings(size_t nmemb, ...)
{
    size_t total_length = 0;

    va_list strings;

    va_start(strings, nmemb);

    for (int i = 0; i < nmemb; i++) {
        const char* item = va_arg(strings, char*);
        total_length += strlen(item);
    }

    va_end(strings);

    char* combined_string = malloc(total_length + 1);

    if (combined_string == NULL)
    {
        return NULL;
    }

    char* destination = combined_string;

    va_start(strings, nmemb);

    for (int i = 0; i < nmemb; i++) {
        const char* source = va_arg(strings, char*);

        strcat(combined_string, source);
    }

    va_end(strings);

    return combined_string;
}

char* space_separate(char* first_item, char* second_item)
{
    char* separated_string = (char*) malloc(sizeof(char) * (strlen(first_item) + strlen(second_item) + 2));

    if (separated_string == NULL)
    {
        return NULL;
    }

    strcpy(separated_string, first_item);

    strcat(separated_string, " ");

    strcat(separated_string, second_item);

    return separated_string;
}
