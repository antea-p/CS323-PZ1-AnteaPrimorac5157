#ifndef COMMON_H
#define COMMON_H

#define MAX_ID_LENGTH 16
#define SUMMARY_LENGTH 48
// duzina pojedinacne linije, 6 proizlazi od ||, ... i \n
#define LINE_SIZE (MAX_ID_LENGTH + SUMMARY_LENGTH + 6)
#define INDEX_FILE "index.txt"

typedef struct {
    int id;
    char *content;
} VaultLog_t;

typedef struct {
    char *id;
    char *summary;
} IndexSummary_t;

#endif // COMMON_H
