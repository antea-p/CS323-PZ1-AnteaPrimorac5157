#ifndef ADD_COMMAND_H
#define ADD_COMMAND_H

typedef struct {
    int id;
    char *content;
} VaultLog_t;

int add_vault_log(const char *string);

#endif //ADD_COMMAND_H
