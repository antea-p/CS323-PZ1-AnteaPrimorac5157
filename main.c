#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include "commands.h"

void print_usage(const Command_t *commands_array);
void print_banner(const char *text);

Command_t commands_array[] = {
    {"list",   parse_list_command,   "Show a summary of all vault logs"},
    {"view",   parse_view_command,   "Read the full contents of the chosen vault log"},
    {"add",    parse_add_command,    "Add a new vault log"},
    {"delete", parse_delete_command, "Delete the chosen vault log"},
    {"edit", parse_edit_command, "Edit an existing vault log"},
    {NULL, NULL, NULL} // sentinel vrijednost
};

int main(int argc, char *argv[]) {
    print_banner("VAULTMGR v1.0");

    if (argc < 2 || strcmp(argv[1], "help") == 0) {
        print_usage(commands_array);
        return 1;
    }

    for (int i = 0; commands_array[i].name != NULL; i++) {
        if (strcmp(argv[1], commands_array[i].name) == 0) {
            int result = commands_array[i].function(argc, argv);
            if (result != 0) {
                print_usage(commands_array);
            }
            return result;
        }
    }

    printf("Unknown command: %s\n", argv[1]);
    print_usage(commands_array);
    return 1;
}

void print_banner(const char *text) {
    // 37 karaktera sirine (eksperimentalna vrijednost, moze se podesiti po potrebi)
    printf("\n");
    printf("╔═════════════════════════════════════════╗\n");
    printf("║  VAULT-TEC UNIFIED OPERATING SYSTEM     ║\n");
    printf("║  ─────────────────────────────────────  ║\n");
    printf("║  %-37s  ║\n", text);
    printf("╚═════════════════════════════════════════╝\n");
    printf("\n");
}

void print_usage(const Command_t *commands_array) {
    printf("Usage:\n");
    for (int i = 0; commands_array[i].name != NULL; i++) {
        printf(" - vaultmgr %s - %s\n", commands_array[i].name, commands_array[i].description);
    }
}
