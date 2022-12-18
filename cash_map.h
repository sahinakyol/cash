#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#ifndef CASH_CASH_MAP_H
#define CASH_CASH_MAP_H

#define MAP_SIZE 128

struct cash_map_node {
    char *key;
    char *value;
    struct cash_map_node *next;
};

typedef struct cash_map {
    struct cash_map_node *cash_map_nodes[MAP_SIZE];
} CASH_MAP;

struct cash_map *cash_map_create(void) {
    struct cash_map *map = malloc(sizeof(struct cash_map));

    if (map == NULL) {
        return NULL;
    }

    memset(map->cash_map_nodes, 0, sizeof(map->cash_map_nodes));

    return map;
}

void cash_map_destroy(struct cash_map *map) {
    if (map == NULL) {
        return;
    }

    for (int i = 0; i < MAP_SIZE; i++) {
        struct cash_map_node *cash_map_node = map->cash_map_nodes[i];
        while (cash_map_node != NULL) {
            struct cash_map_node *next = cash_map_node->next;
            free(cash_map_node->key);
            free(cash_map_node->value);
            free(cash_map_node);
            cash_map_node = next;
        }
    }

    free(map);
}

unsigned int hash(const char *key) {
    unsigned int h = 0;
    while (*key != '\0') {
        h = h * 31 + *key++;
    }
    return h % MAP_SIZE;
}

char *cash_map_get(struct cash_map *map, const char *key) {
    if (map == NULL || key == NULL) {
        return 0;
    }

    unsigned int hash_value = hash(key);

    struct cash_map_node *cash_map_node = map->cash_map_nodes[hash_value];
    while (cash_map_node != NULL) {
        if (strcmp(cash_map_node->key, key) == 0) {
            return cash_map_node->value;
        }
        cash_map_node = cash_map_node->next;
    }

    return 0;
}

void cash_map_put(struct cash_map *map, const char *key, void *value) {
    unsigned int hash_value = hash(key);
    struct cash_map_node *cash_map_node = map->cash_map_nodes[hash_value];
    while (cash_map_node != NULL) {
        if (strcmp(cash_map_node->key, key) == 0) {
            cash_map_node->value = value;
            return;
        }
        cash_map_node = cash_map_node->next;
    }
    cash_map_node = malloc(sizeof(struct cash_map_node));
    cash_map_node->key = strdup(key);
    cash_map_node->value = value;
    cash_map_node->next = map->cash_map_nodes[hash_value];
    map->cash_map_nodes[hash_value] = cash_map_node;
}

void cash_map_remove(struct cash_map *map, const char *key) {
    unsigned int hash_value = hash(key);
    struct cash_map_node **p_cash_map_node = &map->cash_map_nodes[hash_value];
    while (*p_cash_map_node != NULL) {
        if (strcmp((*p_cash_map_node)->key, key) == 0) {
            struct cash_map_node *cash_map_node = *p_cash_map_node;
            *p_cash_map_node = cash_map_node->next;
            free(cash_map_node->key);
            free(cash_map_node);
            return;
        }
        p_cash_map_node = &(*p_cash_map_node)->next;
    }
}

#endif //CASH_CASH_MAP_H
