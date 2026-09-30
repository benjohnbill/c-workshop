#include <stdlib.h>
#include <string.h>
#include "record.h"

#define DEFAULT 10

struct _subject{
    int minutes;
    char *name;
};

struct _Record{
    size_t count;
    size_t capacity;
    Sub **list; // In order to make Dynamic Array.
};

Rec *new_record(void){
    Rec *r = malloc(sizeof *r);
    if (!r){ return NULL; }
    *r = (Rec){
        .count = 0,
        .capacity = DEFAULT,
    };

    r->list = malloc(r->capacity * sizeof *r->list);
    if (!r->list){
        free(r); return NULL;
    } return r;
}

Sub *Sub_add(Rec *r, const char *name, int minutes){
    if (r->count == r->capacity){
        size_t new_capacity = r->capacity * 2;
        Sub **tmp = realloc(r->list, new_capacity * sizeof *r->list);
        if (!tmp){ return NULL; }
        r->list = tmp;
        r->capacity = new_capacity;
    }

    Sub *s = malloc(sizeof *s); // Create Sub *s.
    if (!s) { return NULL; }
    size_t bytes = strlen(name) + 1;
    s->name = malloc(bytes); // Pre-Create s->name's space.
    if (!s->name) {
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

int valid_subject(const char *name){
    return *name != '\0' && !strpbrk(name, "\n\t\r");
}

int minutes_parse(const char *text, int *out){
    int tmp = 0; // text[j] is individual char from argv[].
    for (size_t j = 0; text[j] != '\0'; j++){
        if (text[j] < '0' || text[j] > '9'){ return 0; } // Integer check.
        tmp = (10 * tmp) + (text[j] - '0');
        if (tmp > MINUTES_MAX){ return 0; }
    } // Check in iteration, so tmp never overflows.

    if (tmp < MINUTES_MIN){ return 0; }
    *out = tmp;
    return 1; // Normal Case. If error, all return 0.
}

void print_result(const Rec *r, result func){
    for (size_t i = 0; i < r->count; i++){
        func(r->list[i]->name, r->list[i]->minutes);
    }
}

void Read_list(const Rec *r, result func){
    for (size_t i = 0; i < r->count; i++){
        func(r->list[i]->name, r->list[i]->minutes);
    }
}

void Read_total(const Rec *r, Minutes func){
    int total = 0;
    for (size_t i = 0; i < r->count; i++){
        total += r->list[i]->minutes;
    } func(total);
}
