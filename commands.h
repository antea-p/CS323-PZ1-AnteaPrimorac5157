#ifndef COMMANDS_H
#define COMMANDS_H

typedef struct {
    const char *name;
    int (*function)(int argc, char *argv[]);
    const char *description;
} Command_t;

int parse_list_command(int argc, char *argv[]);
int parse_view_command(int argc, char *argv[]);
int parse_add_command(int argc, char *argv[]);
int parse_edit_command(int argc, char *argv[]);
int parse_delete_command(int argc, char *argv[]);

#endif //COMMANDS_H
