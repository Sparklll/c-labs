#ifndef STACK_H
#define STACK_H

#include "../defines.h"

typedef struct stack_node {
    TYPE data;
    struct stack_node *next;
} stack_node;

typedef struct stack {
    struct stack_node *top;
    size_t size;
} stack;

stack *create_stack();

stack_node *new_stack_node(TYPE data);

void stack_push(stack *stack, TYPE data);

stack_node *stack_peek(stack *stack);

void stack_pop(stack *stack);

void delete_stack(stack *stack);

#endif
