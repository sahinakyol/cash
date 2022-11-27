#ifndef CASH_COMMAND_FUNCS_H
#define CASH_COMMAND_FUNCS_H

void clear_proc(void);

void pwd_proc(void);

void exit_proc(void);

void command_not_found_proc(void);

struct tagCMD getCommand(char *command_name);

typedef struct tagCMD {
    char *name;

    void (*proc)(void);
} CMD;

char g_cwd[PATH_MAX];

CMD g_cmds[] = {
        {"clear", clear_proc},
        {"pwd",   pwd_proc},
        {"exit",  exit_proc},
        {NULL,    command_not_found_proc}
};

struct tagCMD getCommand(char *command_name) {
    int i = 0;
    while (g_cmds[i].name != NULL) {
        if (strcmp(command_name, g_cmds[i].name) == 0) {
            return g_cmds[i];
        }
        ++i;
    }
    return g_cmds[i];
}

void clear_proc(void) {
    system("clear");
}

void pwd_proc(void) {
    printf("%s\n", g_cwd);
}

void exit_proc(void) {
    exit(EXIT_SUCCESS);
}

void command_not_found_proc(void) {
    printf("Command Not Found!\n");
}

#endif //CASH_COMMAND_FUNCS_H
