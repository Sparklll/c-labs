#include <stdlib.h>
#include <stdio.h>
#include "stack.h"

stack *create_stack() {
    stack *stack = malloc(sizeof(struct stack));
    stack->top = NULL;
    stack->size = 0;

    return stack;
}

stack_node *new_stack_node(TYPE data) {
    stack_node *temp = malloc(sizeof(stack_node));
    temp->data = data;
    temp->next = NULL;

    return temp;
}

void stack_push(stack *stack, TYPE data) {
    stack_node *temp = new_stack_node(data);
    temp->next = stack->top;
    stack->top = temp;
    stack->size++;
}

stack_node *stack_peek(stack *stack) {
    return stack->size > 0 ? stack->top : NULL;
}

void stack_pop(stack *stack) {
    if (stack->top == NULL) {
        return;
    }

    stack_node *temp = stack->top;
    stack->top = stack->top->next;
    stack->size--;
    free(temp);
}

void delete_stack(stack *stack) {
    while (stack->size > 0) {
        stack_pop(stack);
    }
    free(stack);
}
