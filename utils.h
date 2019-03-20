#ifndef DATABASE_UTILS
#define DATABASE_UTILS

#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <stdbool.h>

typedef struct ListNode
{
    void* item;
    struct ListNode* next;
} list_node_t;

void* free_all(size_t, ...);

list_node_t* initialize_list_node(list_node_t*);

list_node_t* append_list_node(void*);

list_node_t* find_node(list_node_t*, void*, bool (*) (void*, void*));

void* get_next_list_node(void*);

void* for_each_list_node(void*, void* (*) (void*));

char* combine_strings(size_t, ...);

char* build_list(void*, char*, char*(*)(void*), void*(*)(void*));

char* space_separate(char*, char*);

#endif
