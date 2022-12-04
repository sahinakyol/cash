#ifndef CASH_COMMAND_RUNNER_H
#define CASH_COMMAND_RUNNER_H

#include "command_funcs.h"

void run_command(char **command_and_args);

void run_command(char **command_and_args) {
    getCommand(command_and_args[0]).proc(command_and_args);
}


#endif //CASH_COMMAND_RUNNER_H
