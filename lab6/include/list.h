#ifndef LIST_H
#define LIST_H

#include "defines.h"

typedef struct list_node {
    TYPE data;
    struct list_node *prev, *next;
} list_node;

typedef struct list {
    struct list_node *tail, *head;
    size_t size;
} list;

list *create_list();

list_node *new_list_node(TYPE data);

void list_push_front(list *list, TYPE data);

void list_push_back(list *list, TYPE data);

void list_insert(list *list, int index, TYPE data);

void list_pop(list *list, int index);

void list_pop_front(list *list);

void list_pop_back(list *list);

void delete_list(list *list);

#endif
