#include <stdlib.h>
#include <string.h>
#include "../include/list.h"

list *create_list(size_t data_size) {
    list *list = malloc(sizeof(struct list));
    list->tail = NULL;
    list->head = NULL;
    list->data_size = data_size;
    list->size = 0;

    return list;
}

list_node *new_list_node(list *list, void *data) {
    list_node *temp = malloc(sizeof(list_node));
    temp->prev = NULL;
    temp->next = NULL;
    temp->data = malloc(list->data_size);
    memcpy(temp->data, data, list->data_size);

    return temp;
}

list_node *get_list_element(list *list, size_t index) {
    if(index < 0 || index >= list->size) {
        return NULL;
    }

    int counter = 0;
    list_node *temp_node = list->head;
    while (counter < index) {
        temp_node = temp_node->next;
        counter++;
    }

    return temp_node;
}

void list_push_front(list *list, void *data) {
    list_node *temp = new_list_node(list, data);
    list->size++;

    if (list->head == NULL) {
        list->head = list->tail = temp;
        return;
    }

    temp->next = list->head;
    list->head->prev = temp;
    list->head = temp;
}

void list_push_back(list *list, void *data) {
    list_node *temp = new_list_node(list, data);
    list->size++;

    if (list->head == NULL) {
        list->head = list->tail = temp;
        return;
    }

    list->tail->next = temp;
    temp->prev = list->tail;
    list->tail = temp;
}

void list_insert(list *list, int index, void *data) {
    if (index < 0 || index > list->size - 1) {
        return;
    }
    list_node *index_node;

    if (index <= (list->size - 1) / 2) {
        index_node = list->head;

        size_t i;
        for (i = 0; i < index; i++) {
            index_node = index_node->next;
        }
    } else {
        index_node = list->tail;

        size_t i;
        for (i = list->size - 1; i > index; i--) {
            index_node = index_node->prev;
        }
    }

    list_node *previous_node = index_node->prev;
    list_node *n_node = new_list_node(list, data);
    n_node->prev = previous_node;
    n_node->next = index_node;
    index_node->prev = n_node;
    if (previous_node != NULL) {
        previous_node->next = n_node;
    }

    if (index == 0) {
        list->head = n_node;
    } else if (index == list->size - 1) {
        list->tail = n_node;
    }
    list->size++;
}

void list_pop(list *list, int index) {
    if (index < 0 || index > list->size - 1) {
        return;
    }

    list_node *index_node;

    if (index <= (list->size - 1) / 2) {
        index_node = list->head;
        size_t i;
        for (i = 0; i < index; i++) {
            index_node = index_node->next;
        }
    } else {
        index_node = list->tail;
        size_t i;
        for (i = list->size - 1; i > index; i--) {
            index_node = index_node->prev;
        }
    }

    list_node *previous_node = index_node->prev;
    list_node *next_node = index_node->next;
    if (previous_node != NULL) {
        previous_node->next = next_node;
    }
    if (next_node != NULL) {
        next_node->prev = previous_node;
    }

    if (index == 0) {
        list->head = next_node;
    } else if (index == list->size - 1) {
        list->tail = previous_node;
    }
    free(index_node->data);
    free(index_node);
    list->size--;
}

void list_pop_front(list *list) {
    if (list->size < 1) {
        return;
    }

    list_node *removable_head = list->head;
    list->head = removable_head->next;

    if (list->head != NULL) {
        list->head->prev = NULL;
    }

    free(removable_head->data);
    free(removable_head);
    list->size--;
}

void list_pop_back(list *list) {
    if (list->size < 1) {
        return;
    }
    list_node *removable_tail = list->tail;
    list->tail = removable_tail->prev;

    if (list->tail != NULL) {
        list->tail->next = NULL;
    }

    free(removable_tail->data);
    free(removable_tail);
    list->size--;
}

void delete_list(list *list) {
    while (list->size > 0) {
        list_pop_front(list);
    }
    free(list);
}
