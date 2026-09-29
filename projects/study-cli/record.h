#ifndef RECORD_H
#define RECORD_H

#include <stddef.h>

#define MINUTES_MIN 1
#define MINUTES_MAX 1440

typedef struct _subject Sub;
typedef struct _Record Rec;

// Stage 7: the definition moves into record.c once main no longer reads it.

// Each returns NULL; perror is conducted on main.c
Rec *new_record(void);
Sub *Sub_add(Rec *r, const char *name, int minutes);
void record_free(Rec *r);

// Each returns 1 if valid, 0 if not(exit code). minutes_parse stores the value in *out.
int valid_subject(const char *name);
int minutes_parse(const char *text, int *out);

#endif
