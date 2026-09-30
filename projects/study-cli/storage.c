#include <stddef.h>
#include <string.h>
#include <stdio.h>
#include "storage.h"
#include "record.h"

int file_read(Rec *r, const char *file, size_t *err_line){
    FILE *f = fopen(file, "r");
    if (f == NULL){ return STORAGE_ERR_IO; }
    char buf[1024];
    size_t line = 1;
    // When exceed 1024, the rest of 1024 would be left, parsing error caused.

    // Header read & check
    if (fgets(buf, sizeof(buf), f) == NULL){
        if (ferror(f)){ fclose(f); return STORAGE_ERR_IO; }
        if (err_line != NULL){ *err_line = line; }
        fclose(f); return STORAGE_ERR_FORMAT;
    }

    char *h_nl = strchr(buf, '\n');
    if (h_nl != NULL){ *h_nl = '\0'; }
    if (strcmp(buf, "subject\tminutes") != 0){
        if (err_line != NULL){ *err_line = line; }
        fclose(f); return STORAGE_ERR_FORMAT;
    }

    while (fgets(buf, sizeof(buf), f) != NULL){
        line++;
        // 1. Check '\n' and delete it.
        char *newline = strchr(buf, '\n');
        if (newline != NULL){
            *newline = '\0'; // change '\n' to '\0'
        }

        // 2. Search '\t'
        char *tab = strchr(buf, '\t');
        if (tab == NULL){
            if (err_line != NULL){
                *err_line = line;
            } fclose(f); return STORAGE_ERR_FORMAT;
        }

        // 3. Separate string: By making '\t' NULL, separate name and minutes.
        *tab = '\0';
        char *name = buf;
        char *minutes_text = tab + 1;

        // 4. Validation Check.
        int minutes = 0;
        if (!valid_subject(name) || !minutes_parse(minutes_text, &minutes)){
            if (err_line != NULL){ *err_line = line; }
            fclose(f); return STORAGE_ERR_FORMAT;
        }

        // 5. Add struct
        if (!Sub_add(r, name, minutes)){
            fclose(f); return STORAGE_ERR_NOMEM;
        }
    }

    if (ferror(f)){ fclose(f); return STORAGE_ERR_IO; }
    fclose(f); return STORAGE_OK;
}
