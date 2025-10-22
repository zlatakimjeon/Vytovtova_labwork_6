#include "../include/cbs.h"
#include <stdio.h>
#include <stdlib.h>

void iterator_init(iterator_t *i, unsigned n) {
    i->n = n;
    i->finished = 0;
    i->value.n = n;
    i->value.str = (char *)malloc(2 * n + 1);
    if (!i->value.str) {
        fprintf(stderr, "Error\n");
        exit(1);
    }
    for (unsigned j = 0; j < 2 * n + 1; j++)
    i->value.str[j] = '\0';
}

const cbs_t *iterator_value(const iterator_t *i) {
    return &i->value;
}

int iterator_has_next(const iterator_t *i) {
    return !i->finished;
}

void iterator_next(iterator_t *i) {
    if (i->finished) return;
    unsigned n = i->n;
    if (i->value.str[0] == '\0') {
        if (n == 0) {
            i->value.str[0] = '\0';
            i->finished = 1;
            return;
        }
        for (unsigned j = 0; j < n; j++) i->value.str[j] = '(';
        for (unsigned j = n; j < 2 * n; j++) i->value.str[j] = ')';
        i->value.str[2 * n] = '\0';
        return;
    }
    int balance = 0;
    int pos = 2 * n - 1;
    while (pos >= 0) {
        if (i->value.str[pos] == '(') balance--;
        else balance++;
        if (i->value.str[pos] == '(' && balance > 0) break;
        pos--;
    }
    if (pos < 0) {
        i->finished = 1;
        return;
    }
    i->value.str[pos] = ')';
    unsigned opens = 0, closes = 0;
    for (int j = 0; j <= pos; j++) {
        if (i->value.str[j] == '(') opens++;
        else closes++;
    }
    for (unsigned j = (unsigned)(pos + 1); j < 2 * n; j++) {
        if (opens < n) {
            i->value.str[j] = '(';
            opens++;
        }
        else {
            i->value.str[j] = ')';
            closes++;
        }
    }
    i->value.str[2 * n] = '\0';
}

void iterator_destroy(iterator_t *i) {
    if (i->value.str) {
        free(i->value.str);
        i->value.str = NULL;
    }
}
