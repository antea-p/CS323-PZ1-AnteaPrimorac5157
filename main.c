#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "add_command.h"
#include "list_command.h"

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage:\n");
        printf(" - vaultmgr - Show this help message\n");
        printf(" - vaultmgr add <text> - Add a new vault log\n");
        printf(" - vaultmgr list - Show a summary of all vault logs\n");
        printf(" - vaultmgr read <id> - Read the full contents of the chosen vault log\n");
        printf(" - vaultmgr delete <id> - Delete the chosen vault log\n");
        return 1;
    }
    // TODO: implementirati robusnije upravljanje greskama
    if (strcmp(argv[1], "list") == 0 && argc == 2) {
        list_vault_logs();
    }
    else if (strcmp(argv[1], "add") == 0) {
        if (argc == 3) {
            add_vault_log(argv[2]);
            return 0;
        }
        else {
            printf("You need to provide text content!");
            return 1;
        }
    }

    printf("Unknown command: %s\n", argv[1]);
    return 1;

}

