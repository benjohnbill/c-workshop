#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "record.h"

void print_input(const char *name, int minutes){
    printf("Subject : %s\n- Minutes : %d\n", name, minutes);
}

void print_total(int minutes){
    printf("Total: %d minutes\n", minutes);
}

void print_subject(const char *name){
    printf("Subject : %s\n", name);
} // Reparing needed || This func might be unnecessary.

int argc_check(int argc){
    if (argc % 2 == 1){ // Check paring.
        fprintf(stderr, "Please pairing your subject and minutes\n"); return 2;
    }
    return 0;
}

int argv_check(Rec *r, int argc, char *argv[]){
    for (int i = 3; i <= argc; i += 2){
        int minutes;
        if (!valid_subject(argv[i - 1])){
            fprintf(stderr, "Please input a subject name without tab or newline\n");
            // status = 2; goto cleanup;
            return 2;
        } if (i > 3 && strcmp(argv[i - 1], argv[i - 3]) == 0){ // Previous pair's subject.
            fprintf(stderr, "You entered same sub/values. Are you that steady at %s? or just double entered?\n\n", argv[i - 1]);
        }

        if (!minutes_parse(argv[i], &minutes)){
            fprintf(stderr, "Minutes must be an integer from %d to %d\n", MINUTES_MIN, MINUTES_MAX);
            // status = 2; goto cleanup;
            return 2;
        }
        if (!Sub_add(r, argv[i - 1], minutes)){
            perror("Allocation failed");
            // status = 1; goto cleanup;
            return 1;
        }
    } // Store the pair of argv(Subject-Minute) in Struct Sub.
    return 0;
}

int main(int argc, char *argv[]){
    int status = 0;

    Rec *r = new_record();
    if (!r){ perror("Allocation failed"); exit(1); }

    if (argv[1] != NULL && strcmp(argv[1], "list") == 0){
        if (argc == 2){ // Because argv[0] is command & argv[1] is sub-command.
            fprintf(stdout, "No entries.\n");
        } status = argc_check(argc);
        if (status){ goto cleanup; }
        status = argv_check(r, argc, argv);
        if (status){ goto cleanup; }
        Read_list(r, print_input);
    }
    else if (argv[1] != NULL && strcmp(argv[1], "total") == 0){
        status = argc_check(argc);
        if (status){ goto cleanup; }
        status = argv_check(r, argc, argv);
        if (status){ goto cleanup; }
        Read_total(r, print_total);
    }
    else {
        fprintf(stderr, "Please input ./study with subcommands\n");
        status = 2;
    }

    cleanup:
    record_free(r);
    exit(status);
}
