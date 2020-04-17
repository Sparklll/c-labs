#ifndef QUEUE_H
#define QUEUE_H

#include "../defines.h"

typedef struct node {
    TYPE data;
    struct node *next;
} node;

typedef struct queue {
    struct node *rear, *front;
    size_t size;
} queue;

queue *create_queue();

node *new_node(TYPE data);

void queue_push(queue *queue, TYPE data);

void queue_pop(queue *queue);

int queue_empty(queue *queue);

void delete_queue(queue *queue);

#endif
