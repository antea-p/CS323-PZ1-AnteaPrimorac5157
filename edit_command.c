#include <stdio.h>
#include <string.h>
#include "edit_command.h"
#include "common.h"

int edit_vault_log(const char *id, const char *new_content) {
    if (!is_valid_id(id)) {
        fprintf(stderr, "Invalid ID\n");
        return 1;
    }

    char *filename = prepare_filename(id);
    FILE *p_file = fopen(filename, "r+");
    if (p_file == NULL) {
        fprintf(stderr, "Couldn't open file %s for editing\n", filename);
        return 1;
    }

    fputs(new_content, p_file);
    fclose(p_file);

    FILE *p_index_file = fopen(INDEX_FILE, "r");
    FILE *p_temp_file = fopen(TEMP_FILE, "w");
    if (p_index_file == NULL || p_temp_file == NULL) {
        fprintf(stderr, "Error opening index or temporary file\n");
        if (p_index_file) fclose(p_index_file);
        if (p_temp_file) fclose(p_temp_file);
        return 1;
    }

    char line[LINE_SIZE];
    char current_id[MAX_ID_LENGTH];
    while (fgets(line, sizeof(line), p_index_file) != NULL) {
        sscanf(line, "%[^|]", current_id);
        if (strcmp(current_id, id) == 0) {
            fprintf(p_temp_file, "%s||%.*s...\n", id, SUMMARY_LENGTH, new_content);
        } else {
            fputs(line, p_temp_file);
        }
    }

    fclose(p_index_file);
    fclose(p_temp_file);

    remove(INDEX_FILE);
    rename(TEMP_FILE, INDEX_FILE);

    printf("Edited vault log %s.txt successfully\n", id);
    return 0;
}