#include <stdio.h>
#include <string.h>
#include "header/delete_command.h"

int delete_vault_log(const char *id) {
    if (!is_valid_id(id)) {
        fprintf(stderr, "Invalid ID!\n");
        return 1;
    }

    FILE *p_index_file, *p_temp_file;
    char line[LINE_SIZE];
    char current_id[MAX_ID_LENGTH];;

    char *filename = prepare_filename(id);

    if (remove(filename) != 0) {
        fprintf(stderr, "Couldn't delete %s, or it doesn't exist!", filename);
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
            // Procitaj liniju do | separatora
            sscanf(line, "%[^|]", current_id);
            if (strcmp(current_id, id) != 0) {
                fputs(line, p_temp_file);
            }
        }
    }
    else {
        fprintf(stderr, "Index.txt doesn't exist!\n");
        fclose(p_temp_file);
        return 1;
    }

    fclose(p_temp_file);
    fclose(p_index_file);

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

    return 0;
}