#include "header/commands.h"
#include "header/list_command.h"
#include "header/view_command.h"
#include "header/add_command.h"
#include "header/delete_command.h"
#include "header/edit_command.h"
#include <stdio.h>
#include <stdlib.h>

int parse_list_command(int argc, char *argv[]) {
    return list_vault_logs();
}

int parse_view_command(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: vaultmgr view <id>\n");
        return 1;
    }
    return view_vault_log(argv[2]);
}

int parse_add_command(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: vaultmgr add <text>\n");
        return 1;
    }
    return add_vault_log(argv[2]);
}

int parse_edit_command(int argc, char *argv[]) {
    if (argc != 4) {
        fprintf(stderr, "Usage: vaultmgr edit <id> <new_text>\n");
        return 1;
    }
    return edit_vault_log(argv[2], argv[3]);
}

int parse_delete_command(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: vaultmgr delete <id>\n");
        return 1;
    }
    return delete_vault_log(argv[2]);
}