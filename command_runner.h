#ifndef CASH_COMMAND_RUNNER_H
#define CASH_COMMAND_RUNNER_H

#include <sys/wait.h>
#include "command_funcs.h"

void run_command(char *const *command);

void run_command(char *const *command) {
    pid_t child_pid;
    int status;

    child_pid = fork();
    if (child_pid == 0) {
        getCommand(command[0]).proc();
    } else if (child_pid < 0) {
        printf("Error forking\n");
    } else {
        waitpid(child_pid, &status, WUNTRACED);
    }
}


#endif //CASH_COMMAND_RUNNER_H
