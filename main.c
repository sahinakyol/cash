#include <unistd.h>
#include <sys/wait.h>
#include "command_funcs.h"
#include "command_read_funcs.h"

int main() {
    char **command;
    char *input;

    while (1) {
        if (getcwd(g_cwd, PATH_MAX) == NULL) {
            perror("fatal error (getcwd)");
            exit(EXIT_SUCCESS);
        }
        printf("CASH:%s>", g_cwd);
        input = readline();
        if (input == 0) {
            continue;
        }
        command = get_input(input);
        getCommand(command[0]).proc();
    }
    return 0;
}