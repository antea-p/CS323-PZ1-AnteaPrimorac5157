#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include "commands.h"

Command_t commands[] = {
    {"list",   parse_list_command,   "Show a summary of all vault logs"},
    {"view",   parse_view_command,   "Read the full contents of the chosen vault log"},
    {"add",    parse_add_command,    "Add a new vault log"},
    {"delete", parse_delete_command, "Delete the chosen vault log"},
    {NULL, NULL, NULL}
};

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

int main(int argc, char *argv[]) {
    print_banner("VAULTMGR v1.0");

    if (argc < 2) {
        printf("Usage:\n");
        for (int i = 0; commands[i].name != NULL; i++) {
            printf(" - vaultmgr %s - %s\n", commands[i].name, commands[i].description);
        }
        return 1;
    }

    for (int i = 0; commands[i].name != NULL; i++) {
        if (strcmp(argv[1], commands[i].name) == 0) {
            return commands[i].function(argc, argv);
        }
    }

    printf("Unknown command: %s\n", argv[1]);
    return 1;
}

