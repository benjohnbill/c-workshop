// FAIL_AT=N (1-based): the Nth malloc/realloc made by the program returns NULL.
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

static int calls;

static int should_fail(void){
    const char *s = getenv("FAIL_AT");
    return s && ++calls == atoi(s);
}
void *fi_malloc(size_t n){
    if (should_fail()){ errno = ENOMEM; return NULL; }
    return malloc(n);
}
void *fi_realloc(void *p, size_t n){
    if (should_fail()){ errno = ENOMEM; return NULL; }
    return realloc(p, n);
}
