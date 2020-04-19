#include <stdlib.h>
#include "../include/tree.h"

tree *create_tree() {
    tree *tree = malloc(sizeof(struct tree));
    tree->root = NULL;

    return tree;
}

tree_node *new_tree_node(int key, TYPE data) {
    tree_node *temp = malloc(sizeof(tree_node));
    temp->key = key;
    temp->data = data;
    temp->left_child = NULL;
    temp->right_child = NULL;

    return temp;
}

tree_node *find_tree_node(tree *tree, int key) {
    tree_node *current = tree->root;

    if (current != NULL) {
        while (current->key != key) {
            if (key < current->key) {
                current = current->left_child;
            } else {
                current = current->right_child;
            }

            if (current == NULL) {
                return NULL;
            }
        }
    }
    return current;
}

tree_node *tree_node_successor(tree_node *node) {
    tree_node *successor_parent = node;
    tree_node *successor = node;
    tree_node *current = node->right_child;

    while (current != NULL) {
        successor_parent = successor;
        successor = current;
        current = current->left_child;
    }

    if (successor != node->right_child) {
        successor_parent->left_child = successor->right_child;
        successor->right_child = node->right_child;
    }
    return successor;
}

void insert_tree_node(tree *tree, int key, TYPE data) {
    tree_node *new_node = new_tree_node(key, data);

    if (tree->root == NULL) {
        tree->root = new_node;
    } else {
        tree_node *current = tree->root;
        tree_node *parent;
        int search_position = 1;

        while (search_position) {
            parent = current;

            if (key < current->key) {
                current = current->left_child;
                if (current == NULL) {
                    parent->left_child = new_node;
                    search_position = 0;
                }

            } else if (key == current->key) {
                current->data = data;
                free(new_node);
                search_position = 0;
            } else if (key > current->key) {
                current = current->right_child;
                if (current == NULL) {
                    parent->right_child = new_node;
                    search_position = 0;
                }
            }
        }
    }
}

void delete_tree_node(tree *tree, int key) {
    tree_node *current = tree->root;
    tree_node *parent = tree->root;
    int is_left_child = 1;

    if (current != NULL) {
        while (current->key != key) {
            parent = current;
            if (key < current->key) {
                is_left_child = 1;
                current = current->left_child;
            } else {
                is_left_child = 0;
                current = current->right_child;
            }
            if (current == NULL) {
                return;
            }
        }

        if (current->left_child == NULL && current->right_child == NULL) {
            if (current == tree->root) {
                tree->root = NULL;
            } else if (is_left_child) {
                parent->left_child = NULL;
            } else {
                parent->right_child = NULL;
            }
        } else if (current->right_child == NULL) {
            if (current == tree->root) {
                tree->root = current->left_child;
            } else if (is_left_child) {
                parent->left_child = current->left_child;
            } else {
                parent->right_child = current->left_child;
            }
        } else if (current->left_child == NULL) {
            if (current == tree->root) {
                tree->root = current->right_child;
            } else if (is_left_child) {
                parent->left_child = current->right_child;
            } else {
                parent->right_child = current->right_child;
            }
        } else {
            tree_node *successor = tree_node_successor(current);

            if (current == tree->root) {
                tree->root = successor;
            } else if (is_left_child) {
                parent->left_child = successor;
            } else {
                parent->right_child = successor;
            }

            successor->left_child = current->left_child;
        }
        free(current);
    }
}

void _delete_tree(tree_node *local_root) {
    if (local_root == NULL) {
        return;
    }

    _delete_tree(local_root->left_child);
    _delete_tree(local_root->right_child);
    free(local_root);
}

void delete_tree(tree *tree, tree_node *local_root) {
    int is_node_root = tree->root == local_root;
    _delete_tree(local_root);
    if (is_node_root) {
        free(tree);
    }
}

/* TODO: Balance tree function */

void pre_order_traversal(tree_node *local_root) {
    if (local_root != NULL) {
        /* Manipulate with key/data */
        pre_order_traversal(local_root->left_child);
        pre_order_traversal(local_root->right_child);
    }
}

void in_order_traversal(tree_node *local_root) {
    if (local_root != NULL) {
        in_order_traversal(local_root->left_child);
        /* Manipulate with key/data */
        in_order_traversal(local_root->right_child);
    }
}

void post_order_traversal(tree_node *local_root) {
    if (local_root != NULL) {
        post_order_traversal(local_root->left_child);
        post_order_traversal(local_root->right_child);
        /* Manipulate with key/data */
    }
}
