// common.c
#include "common.h"
#include <stdio.h>

FILE *check_file(FILE *file, const char *filename) {
    if (file == NULL) {
        fprintf(stderr, "Error: Couldn't open file %s\n", filename);
        exit(EXIT_FAILURE);
    }
    return file;
}

int is_valid_id(int id) {
    if (id <= 0) {
        return 0;
    }

    char filename[MAX_ID_LENGTH + 4];
    snprintf(filename, sizeof(filename), "%d.txt", id);

    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        return 0;
    }
    fclose(file);

    return 1;
}