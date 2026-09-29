// Force-included with gcc -include: routes the program's malloc/realloc
// through counters so the Nth call can fail. The source file is not changed.
#include <stdlib.h>
void *fi_malloc(size_t n);
void *fi_realloc(void *p, size_t n);
#define malloc(n) fi_malloc(n)
#define realloc(p, n) fi_realloc(p, n)
