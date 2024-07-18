#include <stdio.h>

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
    printf("Unknown command: %s\n", argv[1]);
    return 1;
}

