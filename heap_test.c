#include <string.h>
#include <stdio.h>

#include "heap.h"

struct test {
    int (*testfn)(struct heap *);
    const char *msg;
};

static int
intcmp(void *context, const void *first, const void *second)
{
    return *(const int *)first - *(const int *)second;
}

#define TESTSET_SIZE 6
#define TESTSET_BYTES (TESTSET_SIZE * sizeof(int))
#define TEST_COMPARE(expect, result) (!memcmp(expect, result, TESTSET_BYTES))


static const int init_testset[TESTSET_SIZE] = { 1, 3, 4, 2, 5, 6 };

static const int heapify_expect[TESTSET_SIZE] = { 6, 5, 4, 2, 3, 1 };
static const int sort_expect[TESTSET_SIZE] = { 1, 2, 3, 4, 5, 6 };

static const int bubbledown_expect[TESTSET_SIZE] = { 4, 3, 6, 2, 5, 1 };
static const int bubbleup_expect[TESTSET_SIZE] = { 6, 3, 1, 2, 5, 4 };


void
test_init(struct heap *target)
{
    target->nelems = 6;
    target->elemsize = sizeof(int);
    target->order = intcmp;
    target->context = 0;

    memcpy(target->base, init_testset, TESTSET_BYTES);
}

int
test_run(int (*testfn)(struct heap *))
{
    struct heap test;
    int backing_store[TESTSET_SIZE];

    test.base = backing_store;
    test_init(&test);

    return testfn(&test);
}

int
test_heap_bubbleup(struct heap *test)
{
    heap_bubbleup(test, 5);
    return TEST_COMPARE(test->base, bubbleup_expect);
}

int
test_heap_bubbledown(struct heap *test)
{
    heap_bubbledown(test, 0);
    return TEST_COMPARE(test->base, bubbledown_expect);
}

int
test_heap_rebuild(struct heap *test)
{
    heap_rebuild(test);
    return TEST_COMPARE(test->base, heapify_expect);
}

int
test_heap_sort(struct heap *test)
{
    heap_rebuild(test);
    heap_sort(test);
    return TEST_COMPARE(test->base, sort_expect);
}

int
main(void)
{
    const char *msg;
    size_t ix;
    struct test tests[] = {
        { test_heap_bubbleup, "heap_bubbleup" },
        { test_heap_bubbledown, "heap_bubbledown" },
        { test_heap_rebuild, "heap_rebuild" },
        { test_heap_sort, "heap_sort" }
    };

    for (ix = 0; ix < sizeof tests / sizeof *tests; ++ix) {
        msg = test_run(tests[ix].testfn) ? "PASS" : "FAIL";
        fprintf(stderr, "Test %s: %s\n", tests[ix].msg, msg);
    }

    return 0;
}



