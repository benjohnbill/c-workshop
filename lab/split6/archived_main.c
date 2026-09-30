#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "archived_record.h"

int main(int argc, char *argv[]){
    int status = 0;
    if (argc == 1){ // Because argv[0] is the programm itself.
        fprintf(stdout, "No entries.\n"); exit(0);
    } else if (argc % 2 == 0){
        fprintf(stderr, "Please pairing your subject and minutes\n"); exit(2);
    }

    Rec *r;
    r = new_record();
    if (!r){ status = 1; exit(status); }
    list_add(r);
    if (!r->list){ status = 1; goto cleanup; }

    const char *set = "\n\t\r";
    for (int i = 2; i <= argc; i += 2){
        int tmp = 0; // argv[i][j] is individual char from input.
        if (*argv[i - 1] == '\0'){
            fprintf(stderr, "Please input a subject name\n");
            status = 2; goto cleanup;
        } else if (strpbrk(argv[i - 1], set)){
            fprintf(stderr, "Please input a plain string name\n");
            status = 2; goto cleanup;
        } if (r->count > 0){
            if (strcmp(argv[i - 1], r->list[r->count-1]->name) == 0){
            fprintf(stderr, "You entered same sub/values. Are you that steady at %s? or just double entered?\n\n", argv[i - 1]);
            }
        }

        for (int j = 0; j < (int)strlen(argv[i]); j++){
            if (argv[i][j] - '0' > 9 || argv[i][j] - '0' < 0){
                fprintf(stderr, "Please insert the minute as integer.\n");
                status = 2; goto cleanup; // Integer check.
            } tmp = (10 * tmp) + (argv[i][j] - '0');
            if (tmp > 1440){
                fprintf(stderr, "Minutes should be at most 1440(24 hours)\n");
                status = 2; goto cleanup; // Maximum minutes check.
            }
        } // Making One Pair of Sub-Min.
        if (tmp < 1){
            fprintf(stderr, "Study Minutes should be recorded as number.\n");
            status = 2; goto cleanup;
        } Sub *s = Sub_add(r, argv[i - 1], tmp);
        if (!s){ status = 1; goto cleanup; }
    } // Store the pair of argv(Subject-Minute) in Struct Sub.

    for (size_t i = 0; i < r->count; i++){
        printf("Subject : %s\n- Minutes : %d\n", r->list[i]->name, r->list[i]->minutes);
    }

    cleanup:
    record_free(r);
    exit(status);
}
