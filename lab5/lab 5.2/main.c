#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "binary search tree/tree.h"
#include "linked list/list.h"
#include "stack/stack.h"


/* Tree in-order traversal for our case with filling stacks */
void custom_in_order_traversal(tree_node *local_root, stack *even_numbers, stack *odd_numbers) {
    if (local_root != NULL) {
        custom_in_order_traversal(local_root->left_child, even_numbers , odd_numbers);
        if (local_root->key % 2 == 0) {
            stack_push(even_numbers, local_root->key);
        } else {
            stack_push(odd_numbers, local_root->key);
        }
        custom_in_order_traversal(local_root->right_child, even_numbers , odd_numbers);
    }
}

void display_stack(stack *stack) {
    stack_node *current = stack->top;
    while (current != NULL) {
        printf("%d, ", current->data);
        current = current->next;
    }
}


int main() {
    srand(time(0));

    int number_of_integers = 30; /* E.g number of integers */
    list *list = create_list(); /* Stores 30 random integers in range [0..100] */
    tree *tree = create_tree();
    stack *even_numbers = create_stack();
    stack *odd_numbers = create_stack();

    /* Filling list */
    printf("Linked list values : ");
    int i;
    for (i = 0; i < number_of_integers; i++) {
        int random_value = rand() % 101;
        list_push_back(list, random_value);
        printf("%d, ", random_value);
    }

    /* Filling tree, data field is 0 value(unused in our case) */
    list_node *current = list->head;
    while (current != NULL) {
        insert_tree_node(tree, current->data, 0);
        current = current->next;
    }

    custom_in_order_traversal(tree->root, even_numbers, odd_numbers);

    printf("\nStack of even numbers : ");
    display_stack(even_numbers);
    printf("\nStack of odd numbers : ");
    display_stack(odd_numbers);


    delete_list(list);
    delete_tree(tree, tree->root);
    delete_stack(even_numbers);
    delete_stack(odd_numbers);
    return 0;
}