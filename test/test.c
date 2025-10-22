#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../include/cbs.h"

static void expect(int cond, const char *msg) {
    if (!cond) {
        fprintf(stderr, "FAIL: %s\n", msg);
        exit(1);
    }
}

static void test_n_equals_0(void) {
    iterator_t it;
    iterator_init(&it, 0);

    expect(iterator_has_next(&it), "n=0: has_next true before next");
    iterator_next(&it);
    const cbs_t *v = iterator_value(&it);
    expect(v != NULL, "n=0: value non-null");
    expect(strcmp(v->str, "") == 0, "n=0: sequence is empty string");

    iterator_next(&it);
    expect(!iterator_has_next(&it), "n=0: has_next false after exhaust");

    iterator_destroy(&it);
}

static void test_n_equals_1(void) {
    iterator_t it;
    iterator_init(&it, 1);

    iterator_next(&it);
    expect(strcmp(iterator_value(&it)->str, "()") == 0, "n=1: first is ()");

    iterator_next(&it);
    expect(!iterator_has_next(&it), "n=1: only one sequence");

    iterator_destroy(&it);
}

static void test_n_equals_3(void) {
    const char *expecteds[] = {"((()))","(()())","(())()","()(())","()()()"};

    iterator_t it;
    iterator_init(&it, 3);

    int idx = 0;
    while (iterator_has_next(&it)) {
        iterator_next(&it);
        if (!iterator_has_next(&it)) break;
        const char *s = iterator_value(&it)->str;
        expect(strcmp(s, expecteds[idx]) == 0, "n=3: sequence mismatch");
        idx++;
    }

    expect(idx == 5, "n=3: should produce 5 sequences");

    iterator_next(&it);
    iterator_destroy(&it);
}


int main(void) {
    test_n_equals_0();
    test_n_equals_1();
    test_n_equals_3();

    printf("All tests passed.\n");
    return 0;
}