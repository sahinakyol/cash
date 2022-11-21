#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <unistd.h>
#include "command_line_func.h"


typedef struct tagCMD {
    char *name;

    void (*proc)(void);
} CMD;


CMD g_cmds[] = {
        {"dir",   dir_proc},
        {"clear", clear_proc},
        {"pwd",   pwd_proc},
        {"cd",    cd_proc},
        {NULL, NULL}
};

int main(void) {
    char cmdline[MAX_CMD_LINE];
    char *str;
    int i;

    if (getcwd(g_cwd, PATH_MAX) == NULL)
        exit_sys("fatal error (getcwd)");

    while (1) {
        printf("CASH:%s>", g_cwd);

        if (fgets(cmdline, MAX_CMD_LINE, stdin) == NULL)
            continue;

        if ((str = strchr(cmdline, '\n')) != NULL)
            *str = '\0';


        parse_cmd_line(cmdline);

        if (g_nparams == 0)
            continue;
        if (!strcmp(g_params[0], "exit"))
            break;
        for (i = 0; g_cmds[i].name != NULL; ++i){
            if (!strcmp(g_params[0], g_cmds[i].name)) {
                g_cmds[i].proc();
                break;
            }
        }
        if (g_cmds[i].name == NULL)
            printf("bad command: %s\n", g_params[0]);
    }
    return 0;
}

