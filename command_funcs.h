#ifndef CASH_COMMAND_FUNCS_H
#define CASH_COMMAND_FUNCS_H

#include <dirent.h>

void clear_proc(char **args);

void pwd_proc(char **args);

void exit_proc(char **args);

void command_not_found_proc(char **args);

void ls_proc(char **args);

void cd_proc(char **args);

struct tagCMD getCommand(char *command_name);

typedef struct tagCMD {
    char *name;

    void (*proc)(char **args);
} CMD;

char g_cwd[PATH_MAX];

CMD g_cmds[] = {
        {"clear", clear_proc},
        {"pwd",   pwd_proc},
        {"ls",    ls_proc},
        {"cd",    cd_proc},
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

void clear_proc(char **args) {
    system("clear");
}

void pwd_proc(char **args) {
    printf("%s\n", g_cwd);
}

void exit_proc(char **args) {
    exit(EXIT_SUCCESS);
}

void command_not_found_proc(char **args) {
    printf("Command Not Found!\n");
}

void ls_proc(char **args) {
    DIR *dir;
    struct dirent *entry;
    dir = opendir(g_cwd);
    if (!dir) {
        perror("Error opening directory");
    }
    while ((entry = readdir(dir)) != NULL) {
        printf("-> %s\n", entry->d_name);
    }
    closedir(dir);
}

void cd_proc(char **args) {
    if (args[1] != 0) {
        strcpy(g_cwd, args[1]);
    } else {
        strcpy(g_cwd, getenv("HOME"));
    }
    if (chdir(g_cwd) != 0) {
        perror("Error changing directory");
    }
}

#endif //CASH_COMMAND_FUNCS_H
