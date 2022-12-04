#ifndef CASH_COMMAND_FUNCS_H
#define CASH_COMMAND_FUNCS_H

#include <dirent.h>

void clear_proc(void);

void pwd_proc(void);

void exit_proc(void);

void command_not_found_proc(void);

void ls_proc(void);

struct tagCMD getCommand(char *command_name);

typedef struct tagCMD {
    char *name;

    void (*proc)(void);
} CMD;

char g_cwd[PATH_MAX];

CMD g_cmds[] = {
        {"clear", clear_proc},
        {"pwd",   pwd_proc},
        {"ls",  ls_proc},
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

void ls_proc(void){
    DIR* dir;
    struct dirent* entry;
    dir = opendir(g_cwd);
    if (!dir) {
        perror("Error opening directory");
    }
    while ((entry = readdir(dir)) != NULL) {
        printf("%s\n", entry->d_name);
    }
    closedir(dir);
}

#endif //CASH_COMMAND_FUNCS_H
