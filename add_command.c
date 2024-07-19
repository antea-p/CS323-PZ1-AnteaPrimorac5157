#include <stdio.h>
#include <stdlib.h>
#include "add_command.h"
#include "common.h"

int add_vault_log(const char *content) {
    FILE *p_index_file;
    int next_id = 0;
    // duzina pojedinacne linije, 3 proizlazi od || i \n
    char line[MAX_ID_LENGTH + SUMMARY_LENGTH + 3];
    p_index_file = fopen(INDEX_FILE, "r");

    if (p_index_file != NULL) {
        while (fgets(line, sizeof(line), p_index_file) != NULL) {
            int current_id = atoi(line);
            if (current_id > next_id) {
                next_id = current_id;
            }
        }
        fclose(p_index_file);
    }

    next_id++;

    // Pripremi datoteku naziva <id>.txt i zapisi ju u buffer
    char filename[MAX_ID_LENGTH + 4];
    snprintf(filename, sizeof(filename), "%d.txt", next_id);

    FILE *p_log_file = fopen(filename, "w");
    // TODO: refaktorirati
    if (p_log_file == NULL) {
        fprintf(stderr, "Couldn't create file for vault log!");
        return -1;
    }

    fputs(content, p_log_file);
    fclose(p_log_file);

    p_index_file = fopen(INDEX_FILE, "a");
    if (p_index_file == NULL) {
        fprintf(stderr, "Couldn't open index file!");
        return -1;
    }

    // Zapisi <redni_broj>, zatim || (separator), pa `<sazetak sadrzaja>...`, i konacno novu liniju.
    fprintf(p_index_file, "%d||%.*s...\n", next_id, SUMMARY_LENGTH, content);
    fclose(p_index_file);

    printf("Created vault log %d.txt\n", next_id);

    return next_id;

}