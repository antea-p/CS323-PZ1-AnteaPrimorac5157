#include <stdio.h>
#include <string.h>
#include "header/common.h"
#define CHUNK_SIZE 1024
#define INITIAL_BUFFER (CHUNK_SIZE * 2)

int view_vault_log(const char *id) {
    if (!is_valid_id(id)) {
        fprintf(stderr, "Invalid ID!\n");
        return 1;
    }

    FILE *p_file;
    char *p_content;
    size_t buffer_size, bytes_read, total_read;
    char chunk[CHUNK_SIZE];

    char *filename = prepare_filename(id);

    p_file = fopen(filename, "r");
    if (p_file == NULL) {
        fprintf(stderr, "The file %s.txt doesn't exist!\n", id);
        return 1;
    }

    total_read = 0;
    buffer_size = INITIAL_BUFFER;
    p_content = malloc(buffer_size);
    if (p_content == NULL) {
        fprintf(stderr, "Error allocating the space for file contents\n");
        return 1;
    }

    while ((bytes_read = fread(chunk, 1, CHUNK_SIZE, p_file)) > 0) {
        // +1 proizlazi od null terminatora kojeg ce se dodati
        if (total_read + bytes_read + 1 > buffer_size) {
            buffer_size *= 2;
            char *p_temp_content = realloc(p_content, buffer_size);
            if (p_temp_content == NULL) {
                fprintf(stderr, "Memory reallocation failed\n");
                free(p_content);
                fclose(p_file);
                return 1;
            }
            p_content = p_temp_content;
        }

        memcpy(p_content + total_read, chunk, bytes_read);
        total_read += bytes_read;
    }
    fclose(p_file);

    // Dodaje se jer memcpy to ne radi automatski
    p_content[total_read] = '\0';

    printf("%s\n", p_content);

    free (p_content);
    return 0;
}