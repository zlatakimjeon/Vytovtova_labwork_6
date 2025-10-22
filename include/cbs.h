#ifndef CBS_H
#define CBS_H

#include <stddef.h>

typedef struct CBS {
    char *str;
    unsigned n;
} cbs_t;

typedef struct CbsIterator {
    cbs_t value;
    unsigned n;
    int finished;
} iterator_t;

void iterator_init(iterator_t *i, unsigned n);

const cbs_t *iterator_value(const iterator_t *i);

int iterator_has_next(const iterator_t *i);

void iterator_next(iterator_t *i);

void iterator_destroy(iterator_t *i);

#endif
