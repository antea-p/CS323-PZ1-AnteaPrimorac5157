#include <stdio.h>
#include <string.h>
#include "delete_command.h"

int delete_vault_log(char *id) {
    // TODO: validacija ID-ja

    FILE *p_index_file, *p_temp_file;
    char line[LINE_SIZE];
    char current_id[MAX_ID_LENGTH];;

    char filename[MAX_ID_LENGTH + 4];
    snprintf(filename, sizeof(filename), "%s.txt", id);

    if (remove(filename) != 0) {
        fprintf(stderr, "Couldn't delete %s", filename);
        return 1;
    }

    p_temp_file = fopen(TEMP_FILE, "w");
    if (p_temp_file == NULL) {
        fprintf(stderr, "Couldn't create temporary file!");
        return 1;
    }

    p_index_file = fopen(INDEX_FILE, "r");
    if (p_index_file != NULL) {
        while (fgets(line, sizeof(line), p_index_file) != NULL) {
            sscanf(line, "%[^|]", current_id);
            if (strcmp(current_id, id) != 0) {
                fputs(line, p_temp_file);
            }
        }
    }
    else {
        fprintf(stderr, "Index.txt doesn't exist!\n");
        return 1;
    }

    if (remove(INDEX_FILE) != 0) {
        fprintf(stderr, "Failed to remove temporary file!\n");
        return 1;
    }

    if (rename(TEMP_FILE, INDEX_FILE) != 0) {
        fprintf(stderr, "Failed to rename temporary file!\n");
        fclose(p_temp_file);
        return 1;
    }

    printf("Deleted file %s.txt successfully!", id);
    fclose(p_temp_file);
    fclose(p_index_file);
    return 0;
}