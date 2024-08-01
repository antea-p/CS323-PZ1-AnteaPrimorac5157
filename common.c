#include "header/common.h"
#include <stdio.h>
#include <limits.h>
#include <ctype.h>
#include <string.h>

FILE *check_file(FILE *file, const char *filename) {
    if (file == NULL) {
        fprintf(stderr, "Error: Couldn't open file %s\n", filename);
        exit(EXIT_FAILURE);
    }
    return file;
}

int is_valid_id(const char *id) {
    if (id == NULL || strlen(id) == 0 || strlen(id) > MAX_ID_LENGTH) {
        return 0;
    }

    // Provjeri da li su svi karakteri cifre
    for (const char *p = id; *p; p++) {
        if (!isdigit(*p)) {
            return 0;
        }
    }

    // Pretvori karakter u u long radi sigurne provjere da li je <= najvecem intu
    long num_id = atol(id);
    return (num_id > 0 && num_id <= INT_MAX) ? 1 : 0;
}

char *prepare_filename(const char *id) {
    static char filename[FILENAME_MAX_LENGTH];
    snprintf(filename, sizeof(filename), "%s.txt", id);
    return filename;
}