#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <unistd.h>
#include "command_read_funcs.h"
#include "command_runner.h"

int main() {
    char **command;
    char *input;
    while (1) {
        if (getcwd(g_cwd, PATH_MAX) == NULL) {
            perror("fatal error (getcwd)");
            exit(EXIT_SUCCESS);
        }
        printf("CASH:>");
        input = readline();
        if (input == 0) {
            continue;
        }
        command = get_input(input);
        run_command(command);
    }
    return 0;
}