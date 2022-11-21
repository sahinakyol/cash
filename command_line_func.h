#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <limits.h>
#include <unistd.h>

void parse_cmd_line(char *cmdline);
void dir_proc(void);
void clear_proc(void);
void pwd_proc(void);
void cd_proc(void);
void exit_sys(const char *msg);

#define MAX_CMD_LINE        4096
#define MAX_CMD_PARAMS      128

char *g_params[MAX_CMD_PARAMS];
int g_nparams;

char g_cwd[PATH_MAX];

void parse_cmd_line(char *cmdline)
{
    char *str;

    g_nparams = 0;
    for (str = strtok(cmdline, " \t"); str != NULL; str = strtok(NULL, " \t"))
        g_params[g_nparams++] = str;
}

void dir_proc(void)
{
    printf("dir command executing..\n");
}

void clear_proc(void)
{
    system("clear");
}

void pwd_proc(void)
{
    printf("%s\n", g_cwd);
}

void cd_proc(void)
{
    char *dir;

    if (g_nparams > 2) {
        printf("too many arguments!\n");
        return;
    }
    if (g_nparams == 1) {
        if ((dir = getenv("HOME")) == NULL)
            exit_sys("fatal error (getenv");
    }
    else
        dir = g_params[1];

    if (chdir(dir) == -1) {
        printf("%s\n", strerror(errno));
        return;
    }

    if (getcwd(g_cwd, PATH_MAX) == NULL)
        exit_sys("fatal error (getcwd)");
}

void exit_sys(const char *msg)
{
    perror(msg);

    exit(EXIT_FAILURE);
}