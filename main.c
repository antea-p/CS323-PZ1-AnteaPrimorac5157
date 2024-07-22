#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "add_command.h"
#include "list_command.h"
#include "view_command.h"
#include "delete_command.h"

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
    char *command = argv[1];
    if (strcmp(command, "list") == 0 && argc == 2) {
        return list_vault_logs();

    }
    else if (strcmp(command, "view") == 0) {
        if (argc == 3) {
            return view_vault_log(atoi(argv[2]));
        }
        else {
            printf("You need to provide ID!");
        }
    }
    else if (strcmp(command, "add") == 0) {
        if (argc == 3) {
            return add_vault_log(argv[2]);
        }
        else {
            printf("You need to provide text content!");
            return 1;
        }
    } else if (strcmp(command, "delete") == 0) {
        if (argc == 3) {
            return delete_vault_log(argv[2]);
        } else {
            printf("You need to provide ID!");
        }
    }
    printf("Unknown command: %s\n", argv[1]);
    return 1;

}

