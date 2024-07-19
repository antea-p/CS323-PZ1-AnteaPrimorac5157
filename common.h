#ifndef COMMON_H
#define COMMON_H

#define MAX_ID_LENGTH 16
#define SUMMARY_LENGTH 48
#define INDEX_FILE "index.txt"

typedef struct {
    int id;
    char *content;
} VaultLog_t;

#endif // COMMON_H
