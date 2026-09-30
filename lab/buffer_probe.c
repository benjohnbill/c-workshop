/* Probe, not an exercise file: where do the bytes sit after one read?
 * Setup: printf 'subject\tminutes\nC\t30\nOS\t45\n' > /tmp/probe.tsv
 * Run:   c dbg lab/buffer_probe.c
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
    FILE *f = fopen("/tmp/probe.tsv", "r");
    if (f == NULL)
        return 1;

    char mine[9] = {0};
    size_t got = fread(mine, 1, 8, f);
    if (got != 8)
        return 1;
    char *copy = malloc(sizeof(*copy) * 9);
    memcpy(copy, mine, 9);
    printf("%s\n", copy);

    fclose(f);
    free(copy);
    return 0;
}
