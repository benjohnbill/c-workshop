#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "record.h"

int main(int argc, char *argv[]){
    int status = 0;
    if (argc == 1){ // Because argv[0] is the programm itself.
        fprintf(stdout, "No entries.\n"); exit(0);
    } else if (argc % 2 == 0){
        fprintf(stderr, "Please pairing your subject and minutes\n"); exit(2);
    }

    Rec *r = new_record();
    if (!r){ perror("Allocation failed"); exit(1); }

    for (int i = 2; i <= argc; i += 2){
        int minutes;
        if (!valid_subject(argv[i - 1])){
            fprintf(stderr, "Please input a subject name without tab or newline\n");
            status = 2; goto cleanup;
        } if (i > 2 && strcmp(argv[i - 1], argv[i - 3]) == 0){ // Previous pair's subject.
            fprintf(stderr, "You entered same sub/values. Are you that steady at %s? or just double entered?\n\n", argv[i - 1]);
        }

        if (!minutes_parse(argv[i], &minutes)){
            fprintf(stderr, "Minutes must be an integer from %d to %d\n", MINUTES_MIN, MINUTES_MAX);
            status = 2; goto cleanup;
        }
        if (!Sub_add(r, argv[i - 1], minutes)){
            perror("Allocation failed");
            status = 1; goto cleanup;
        }
    } // Store the pair of argv(Subject-Minute) in Struct Sub.

    // The last leak: main walks the array itself. Stage 7 replaces this loop.
    for (size_t i = 0; i < r->count; i++){
        printf("Subject : %s\n- Minutes : %d\n", r->list[i]->name, r->list[i]->minutes);
    }

    cleanup:
    record_free(r);
    exit(status);
}
