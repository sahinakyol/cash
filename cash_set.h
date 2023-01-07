#ifndef CASH_CASH_SET_H
#define CASH_CASH_SET_H

#include <stdlib.h>
#include <stdio.h>

#define SET_SIZE 100

typedef struct cash_set {
    int size;
    char elements[SET_SIZE];
} CASH_SET;

CASH_SET *create_cash_set() {
    CASH_SET *cash_set = malloc(sizeof(CASH_SET));
    cash_set->size = 0;
    return cash_set;
}

void add_cash_set(CASH_SET *cash_set, char element) {
    for (int i = 0; i < cash_set->size; i++) {
        if (cash_set->elements[i] == element) {
            perror("Could not add !!");
            return;
        }
    }
    cash_set->elements[cash_set->size++] = element;
}

void remove_cash_set(CASH_SET *cash_set, char element) {
    for (int i = 0; i < cash_set->size; ++i) {
        if (cash_set->elements[i] == element) {
            cash_set->elements[i] = cash_set->elements[--cash_set->size];
            return;
        }
    }
    perror("Could not remove !!");
}

void destroy_cash_set(CASH_SET *cash_set) {
    free(cash_set);
}


#endif //CASH_CASH_SET_H
