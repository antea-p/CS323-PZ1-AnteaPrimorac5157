#ifndef COMMON_H
#define COMMON_H

#include <stdio.h>
#include <stdlib.h>

// maks duzina ID-ja 10 cifara - dovoljno za najveci int
#define MAX_ID_LENGTH 10
#define SUMMARY_LENGTH 48
// duzina pojedinacne linije, 6 proizlazi od ||, ... i \n
#define LINE_SIZE (MAX_ID_LENGTH + SUMMARY_LENGTH + 6)
#define FILENAME_MAX_LENGTH (MAX_ID_LENGTH + 4)  // +4 zbog ".txt"
#define INDEX_FILE "index.txt"
#define TEMP_FILE "temp.txt"

typedef struct {
    char id[MAX_ID_LENGTH];
    char summary[SUMMARY_LENGTH + 1];
} IndexSummary_t;

FILE *check_file(FILE *file, const char *filename);
int is_valid_id(const char *id);
char *prepare_filename(const char *id);
int is_whitespace_only(const char *str);

#endif // COMMON_H
