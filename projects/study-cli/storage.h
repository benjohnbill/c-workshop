#ifndef STORAGE_H
#define STORAGE_H

#include <stddef.h>
typedef struct _Record Rec;

enum {
    STORAGE_OK         = 0,
    STORAGE_ERR_IO     = 1,
    STORAGE_ERR_FORMAT = 2,
    STORAGE_ERR_NOMEM  = 3,
};

int file_read(Rec *r, const char *file, size_t *err_line);

#endif
