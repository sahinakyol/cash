#ifndef CASH_CASH_BINARY_TREE_H
#define CASH_CASH_BINARY_TREE_H

#define TREE_KEY_NUMBER 1024

#include <stdlib.h>
#include <printf.h>

typedef struct cash_binary_tree_node {
    char *value;
    unsigned int key;
    struct cash_binary_tree_node *left;
    struct cash_binary_tree_node *right;
} CASH_BINARY_TREE;


unsigned int cash_binary_tree_hash(const char *value) {
    unsigned int h = 0;
    while (*value != '\0') {
        h = h * 31 + *value++;
    }
    return h % TREE_KEY_NUMBER;
}


CASH_BINARY_TREE *create_cash_binary_tree(char *value) {
    CASH_BINARY_TREE *cash_binary_tree_node = malloc(sizeof(CASH_BINARY_TREE));
    cash_binary_tree_node->value = value;
    cash_binary_tree_node->key = cash_binary_tree_hash(value);
    cash_binary_tree_node->left = NULL;
    cash_binary_tree_node->right = NULL;
    return cash_binary_tree_node;
}

void insert_cash_binary_tree(CASH_BINARY_TREE **cash_binary_tree_node, char *value) {
    unsigned int hashed_value = cash_binary_tree_hash(value);
    if (*cash_binary_tree_node == NULL) {
        *cash_binary_tree_node = create_cash_binary_tree(value);
    } else if (hashed_value <= (*cash_binary_tree_node)->key) {
        if ((*cash_binary_tree_node)->left == NULL) {
            (*cash_binary_tree_node)->left = create_cash_binary_tree(value);
        } else {
            insert_cash_binary_tree(&(*cash_binary_tree_node)->left, value);
        }
    } else {
        if ((*cash_binary_tree_node)->right == NULL) {
            (*cash_binary_tree_node)->right = create_cash_binary_tree(value);
        } else {
            insert_cash_binary_tree(&(*cash_binary_tree_node)->right, value);
        }
    }
}

CASH_BINARY_TREE *search_cash_binary_tree(CASH_BINARY_TREE *cash_binary_tree_node, char *value) {
    if (cash_binary_tree_node == NULL || cash_binary_tree_node->key == cash_binary_tree_hash(value)) {
        return cash_binary_tree_node;
    }
    if (cash_binary_tree_hash(value) < cash_binary_tree_node->key) {
        return search_cash_binary_tree(cash_binary_tree_node->left, value);
    }

    return search_cash_binary_tree(cash_binary_tree_node->right, value);
}

void traverse_cash_binary_tree(CASH_BINARY_TREE *cash_binary_tree_node) {
    if (cash_binary_tree_node != NULL) {
        printf("Key is %d Value is %s \n", cash_binary_tree_node->key, cash_binary_tree_node->value);
        traverse_cash_binary_tree(cash_binary_tree_node->left);
        traverse_cash_binary_tree(cash_binary_tree_node->right);
    }
}

CASH_BINARY_TREE *find_min_cash_binary_tree(CASH_BINARY_TREE *cash_binary_tree_node) {
    if (cash_binary_tree_node == NULL) {
        return NULL;
    }
    while (cash_binary_tree_node->left != NULL) {
        cash_binary_tree_node = cash_binary_tree_node->left;
    }

    return cash_binary_tree_node;
}

CASH_BINARY_TREE *find_max_cash_binary_tree(CASH_BINARY_TREE *cash_binary_tree_node) {
    if (cash_binary_tree_node == NULL) {
        return NULL;
    }
    while (cash_binary_tree_node->right != NULL) {
        cash_binary_tree_node = cash_binary_tree_node->right;
    }

    return cash_binary_tree_node;
}


int height_cash_binary_tree(CASH_BINARY_TREE *cash_binary_tree_node) {
    if (cash_binary_tree_node == NULL) {
        return -1;
    }

    int left_height = height_cash_binary_tree(cash_binary_tree_node->left);
    int right_height = height_cash_binary_tree(cash_binary_tree_node->right);

    if (left_height > right_height) {
        return left_height + 1;
    }

    return right_height + 1;
}

void delete_cash_binary_tree(CASH_BINARY_TREE **cash_binary_tree_node, char *value) {
    if (*cash_binary_tree_node == NULL) {
        return;
    }

    if (cash_binary_tree_hash(value) < (*cash_binary_tree_node)->key) {
        delete_cash_binary_tree(&(*cash_binary_tree_node)->left, value);
    } else if (cash_binary_tree_hash(value) > (*cash_binary_tree_node)->key) {
        delete_cash_binary_tree(&(*cash_binary_tree_node)->right, value);
    } else {
        if ((*cash_binary_tree_node)->left == NULL && (*cash_binary_tree_node)->right == NULL) {
            free(*cash_binary_tree_node);
            *cash_binary_tree_node = NULL;
        } else if ((*cash_binary_tree_node)->left == NULL) {
            CASH_BINARY_TREE *temp = *cash_binary_tree_node;
            *cash_binary_tree_node = (*cash_binary_tree_node)->right;
            free(temp);
        } else if ((*cash_binary_tree_node)->right == NULL) {
            CASH_BINARY_TREE *temp = *cash_binary_tree_node;
            *cash_binary_tree_node = (*cash_binary_tree_node)->left;
            free(temp);
        } else {
            CASH_BINARY_TREE *temp = find_min_cash_binary_tree((*cash_binary_tree_node)->right);
            (*cash_binary_tree_node)->value = temp->value;
            (*cash_binary_tree_node)->key = temp->key;
            delete_cash_binary_tree(&(*cash_binary_tree_node)->right, temp->value);
        }
    }
}

#endif //CASH_CASH_BINARY_TREE_H
