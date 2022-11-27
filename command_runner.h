//
// Created by sahin on 27.11.2022.
//

#ifndef CASH_COMMAND_RUNNER_H
#define CASH_COMMAND_RUNNER_H

#include <sys/wait.h>
#include "command_funcs.h"

void run_command(char *const *command);
void run_command(char *const *command) {
    pid_t cpid;
    int status;

    cpid = fork();
    if (cpid > 0) {
        getCommand(command[0]).proc();
    } else if (cpid < 0)
        printf("Error forking\n");
    else {
        waitpid(cpid, &status, WUNTRACED);
    }
}


#endif //CASH_COMMAND_RUNNER_H
