#include <stdio.h>
#include <stdlib.h>
#include "header/add_command.h"
#include "header/common.h"

int add_vault_log(const char *content) {
    FILE *p_index_file;
    int next_id = 0;
    char line[LINE_SIZE];
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

    // Pripremi datoteku naziva <id>.txt (gdje +1 dodajemo zbog null terminatora), i zapisi ju u buffer
    char id_str[MAX_ID_LENGTH + 1];
    snprintf(id_str, sizeof(id_str), "%d", next_id);
    char *filename = prepare_filename(id_str);

    FILE *p_log_file = fopen(filename, "w");
    if (p_log_file == NULL) {
        fprintf(stderr, "Couldn't create file for vault log!");
        return 1;
    }

    fputs(content, p_log_file);
    fclose(p_log_file);

    p_index_file = fopen(INDEX_FILE, "a");
    if (p_index_file == NULL) {
        fprintf(stderr, "Couldn't open index file!");
        return 1;
    }

    // Zapisi <redni_broj>, zatim || (separator), pa `<sazetak sadrzaja>...`, i konacno novu liniju.
    fprintf(p_index_file, "%d||%.*s...\n", next_id, SUMMARY_LENGTH, content);
    fclose(p_index_file);

    printf("Created vault log %d.txt\n", next_id);

    return next_id;

}