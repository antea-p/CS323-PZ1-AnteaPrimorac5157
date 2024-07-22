#ifndef COMMON_H
#define COMMON_H

#include <stdio.h>
#include <stdlib.h>

#define MAX_ID_LENGTH 16
#define SUMMARY_LENGTH 48
// duzina pojedinacne linije, 6 proizlazi od ||, ... i \n
#define LINE_SIZE (MAX_ID_LENGTH + SUMMARY_LENGTH + 6)
#define INDEX_FILE "index.txt"
#define TEMP_FILE "temp.txt"

typedef struct {
    char id[MAX_ID_LENGTH];
    char summary[SUMMARY_LENGTH + 1];
} IndexSummary_t;

FILE *check_file(FILE *file, const char *filename);
int is_valid_id(int id);

#endif // COMMON_H
