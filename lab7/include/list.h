#ifndef LIST_H
#define LIST_H
#include <stdlib.h>

/* Generic list */

typedef struct list_node {
    void *data;
    struct list_node *prev, *next;
} list_node;

typedef struct list {
    struct list_node *tail, *head;
    size_t data_size;
    size_t size;
} list;

list *create_list(size_t data_size);

list_node *new_list_node(list *list, void *data);

list_node *get_list_element(list *list, size_t index);

void list_push_front(list *list, void *data);

void list_push_back(list *list, void *data);

void list_insert(list *list, int index, void *data);

void list_pop(list *list, int index);

void list_pop_front(list *list);

void list_pop_back(list *list);

void delete_list(list *list);

#endif