#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "archived_record.h"

Rec *new_record(void){
    Rec *r = malloc(sizeof *r);
    if (!r){ perror("Allocation failed"); return NULL; }
    *r = (Rec){
        .count = 0,
        .capacity = DEFAULT,
    };
    return r;
}

void list_add(Rec *r){
    r->list = malloc(r->capacity * sizeof *r->list);
    if (!r->list) {perror("malloc");
    return; }
}

Sub *Sub_add(Rec *r, const char *name, int minutes){
    if (r->count == r->capacity){
        size_t new_capacity = r->capacity * 2;
        Sub **tmp = realloc(r->list, new_capacity * sizeof *r->list);
        if (!tmp){ perror("Allocation failed"); return NULL; }
        r->list = tmp;
        r->capacity = new_capacity;
    }

    Sub *s = malloc(sizeof *s); // Create Sub *s.
    if (!s) { perror("malloc"); return NULL; }
    size_t bytes = strlen(name) + 1;
    s->name = malloc(bytes); // Pre-Create s->name's space.
    if (!s->name) { perror("malloc");
        free(s); return NULL;
    }

    memcpy(s->name, name, bytes);
    s->minutes = minutes;

    r->list[r->count++] = s;
    return s;
}

void record_free(Rec *r){
    for (size_t i = 0; i < r->count; i++){
        free(r->list[i]->name);
        free(r->list[i]);
    }
    free(r->list);
    free(r);
}
