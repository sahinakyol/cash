#ifndef CASH_COMMAND_READ_FUNCS_H
#define CASH_COMMAND_READ_FUNCS_H
#define MAX_CMD_LINE        4096

char **get_input(char *input);

char *readline(void);

char **get_input(char *input) {
    char **command = malloc(8 * sizeof(char *));
    char *separator = " ";
    int index = 0;

    char *parsed = strtok(input, separator);
    while (parsed != NULL) {
        size_t len = strlen(parsed);
        if (parsed[len - 1] == '\n') {
            parsed[len - 1] = 0;
        }
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

    return strtok(cmdline, "\0");
}

#endif //CASH_COMMAND_READ_FUNCS_H
