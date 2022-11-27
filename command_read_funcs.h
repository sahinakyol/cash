#ifndef CASH_COMMAND_READ_FUNCS_H
#define CASH_COMMAND_READ_FUNCS_H
#define MAX_CMD_LINE        4096

char **get_input(char *input);

char *readline(void);

char **get_input(char *input) {
    char **command = malloc(8 * sizeof(char *));
    char *separator = " ";
    char *parsed;
    int index = 0;

    parsed = strtok(input, separator);
    while (parsed != NULL) {
        command[index] = parsed;
        index++;
        parsed = strtok(NULL, separator);
    }
    command[index] = NULL;

    return command;
}

char *readline(void) {
    char cmdline[MAX_CMD_LINE];
    fgets(cmdline, MAX_CMD_LINE, stdin);

    return strtok(cmdline, " \n");
}

#endif //CASH_COMMAND_READ_FUNCS_H
