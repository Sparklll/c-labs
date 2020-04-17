#include <stdlib.h>
#include "queue.h"

queue *create_queue() {
    queue *queue = malloc(sizeof(struct queue));
    queue->rear = NULL;
    queue->front = NULL;
    queue->size = 0;

    return queue;
}

node *new_node(TYPE data) {
    node *temp = malloc(sizeof(node));
    temp->data = data;
    temp->next = NULL;

    return temp;
}

void queue_push(queue *queue, TYPE data) {
    node *temp = new_node(data);
    queue->size++;

    if (queue->rear == NULL) {
        queue->front = queue->rear = temp;
        return;
    }

    queue->rear->next = temp;
    queue->rear = temp;
}

void queue_pop(queue *queue) {
    if (queue->front == NULL) {
        return;
    }

    node *temp = queue->front;
    queue->front = queue->front->next;

    if (queue->front == NULL)
        queue->rear = NULL;

    queue->size--;
    free(temp);
}

int queue_empty(queue *queue) {
    return queue->size > 0 ? 0 : 1;
}

void delete_queue(queue *queue) {

    while (queue->size > 0) {
        node *temp = queue->front;
        queue_pop(queue);
    }
    free(queue);
}
