#ifndef TREE_H
#define TREE_H

#include "defines.h"

typedef struct tree_node {
    TYPE data;
    int key;
    struct tree_node *left_child, *right_child;
} tree_node;

typedef struct tree {
    struct tree_node *root;
} tree;

tree *create_tree();

tree_node *new_tree_node(int key, TYPE data);

tree_node *find_tree_node(tree *tree, int key);

tree_node *tree_node_successor(tree_node *node);

void insert_tree_node(tree *tree, int key, TYPE data);

void delete_tree_node(tree *tree, int key);

void _delete_tree(tree_node *local_root);

void delete_tree(tree *tree, tree_node *local_root);

void pre_order_traversal(tree_node *local_root);

void in_order_traversal(tree_node *local_root);

void post_order_traversal(tree_node *local_root);

#endif
