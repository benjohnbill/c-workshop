#ifndef RECORD_H
#define RECORD_H

#include <stddef.h>
#define DEFAULT 10

typedef struct _subject{
    int minutes;
    char *name;
} Sub;

typedef struct _Record{
    size_t count;
    size_t capacity;
    Sub **list; // In order to make Dynamic Array.
} Rec;

Rec *new_record(void);
void list_add(Rec *r);
Sub *Sub_add(Rec *r, const char *name, int minutes);
void record_free(Rec *r);

#endif
