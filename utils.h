#ifndef DATABASE_UTILS
#define DATABASE_UTILS

#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

typedef struct ListNode
{
    void* item;
    struct ListNode* next;
} list_node_t;

void* free_all(size_t, ...);

void* get_next_list_node(void*);

char* combine_strings(size_t, ...);

char* build_list(void*, char*, char*(*)(void*), void*(*)(void*));

char* space_separate(char*, char*);

#endif
