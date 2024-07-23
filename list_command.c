#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "common.h"
#include "list_command.h"
#define INITIAL_CAPACITY 10

int list_vault_logs() {
    FILE *p_index_file;
    char line[LINE_SIZE];
    size_t capacity = INITIAL_CAPACITY;
    size_t size = 0;

    IndexSummary_t *p_vault_logs_summaries = malloc(capacity * sizeof(IndexSummary_t));
    if (p_vault_logs_summaries == NULL) {
        fprintf(stderr, "Error allocating the space for an array of structs!\n");
        return -1;
    }

    p_index_file = fopen(INDEX_FILE, "r");
    if (p_index_file == NULL) {
        p_index_file = fopen(INDEX_FILE, "w");
        printf("Your index.txt is empty! Try adding something to it!");
    }

    if (p_index_file != NULL) {
        while (fgets(line, sizeof(line), p_index_file) != NULL) {
            if (size >= capacity) {
                capacity *= 2;
                IndexSummary_t *p_temp = realloc(p_vault_logs_summaries, capacity * sizeof(IndexSummary_t));
                if (p_temp == NULL) {
                    fprintf(stderr, "Memory reallocation failed\n");
                    free(p_vault_logs_summaries);
                    fclose(p_index_file);
                    return -1;
                }
                p_vault_logs_summaries = p_temp;
            }
            IndexSummary_t currentIndexSummary = parse_index_line(line);
            p_vault_logs_summaries[size] = currentIndexSummary;
            size++;
        }
        fclose(p_index_file);
    }
    else {
        fprintf(stderr, "Couldn't open Index.txt!\n");
        free(p_vault_logs_summaries);
        return 1;
    }


    for (size_t i = 0; i < size; ++i) {
        if (strlen(p_vault_logs_summaries[i].summary) < SUMMARY_LENGTH) {
            printf("ID: %s | Summary: %s\n",
                   p_vault_logs_summaries[i].id,
                   p_vault_logs_summaries[i].summary);
        }
        else {
            printf("ID: %s | Summary: %s...\n",
                   p_vault_logs_summaries[i].id,
                   p_vault_logs_summaries[i].summary);
        }
    }
    free(p_vault_logs_summaries);
    return 0;
}

IndexSummary_t parse_index_line(char *line) {

    // Alternativno mozemo koristiti {{0}}
    IndexSummary_t indexSummary = {};
    char *p_token = strtok(line, "|");
    if (p_token != NULL) {

        strncpy(indexSummary.id, p_token, MAX_ID_LENGTH - 1);
        indexSummary.id[MAX_ID_LENGTH - 1]  = '\0';
        p_token = strtok(NULL, "\n"); // Nastavi citati odakle se stalo proslog puta
        if (p_token != NULL) {
            p_token++; // Preskoci drugo "|"
            strncpy(indexSummary.summary, p_token, SUMMARY_LENGTH);
            indexSummary.summary[SUMMARY_LENGTH] = '\0';
        }
        else {
            strncpy(indexSummary.summary, "No summary exists", SUMMARY_LENGTH);
            indexSummary.summary[SUMMARY_LENGTH] = '\0';
        }
    }
    else {
        strncpy(indexSummary.id, "Invalid ID", MAX_ID_LENGTH - 1);
        indexSummary.id[MAX_ID_LENGTH - 1] = '\0';
    }

    return indexSummary;
}