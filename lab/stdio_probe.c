#include <stdio.h>

int main(void)
{
    /* A relative path starts at the process's current working directory. */
    const char *path = "stdio_probe_output.txt";
    const char *message = "Mina: C study";

    /* path and mode go in; an open stream (or NULL) comes back. */
    FILE *stream = fopen(path, "w");
    if (stream == NULL) {
        perror("fopen");
        return 1;
    }

    /* stream, format, and message go in; a byte count comes back. */
    int written = fprintf(stream, "%s\n", message);
    if (written < 0) {
        perror("fprintf");
        (void)fclose(stream);
        return 1;
    }

    /* Buffered output is sent onward; the stream stays open. */
    int flush_result = fflush(stream);
    if (flush_result == EOF) {
        perror("fflush");
        (void)fclose(stream);
        return 1;
    }

    /* Closing also flushes any remaining output. Do not use stream again. */
    int close_result = fclose(stream);
    stream = NULL;
    if (close_result == EOF) {
        perror("fclose");
        return 1;
    }

    /* printf writes to stdout; it does not write to the file above. */
    int printed = printf("saved %d bytes to %s\n", written, path);
    if (printed < 0) {
        perror("printf");
        return 1;
    }

    return 0;
}
