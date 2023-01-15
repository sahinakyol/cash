#ifndef CASH_COMMAND_FUNCS_H
#define CASH_COMMAND_FUNCS_H

#include <dirent.h>
#include <sys/stat.h>
#include <sys/errno.h>
#include <sys/fcntl.h>
#include "color_strings.h"
#include "cash_binary_tree.h"

void clear_proc(char **args);

void pwd_proc(char **args);

void exit_proc(char **args);

void command_not_found_proc(char **args);

void ls_proc(char **args);

void cd_proc(char **args);

void mkdir_proc(char **args);

void touch_proc(char **args);

void echo_proc(char **args);

void cp_proc(char **args);

void cash_binary_visualize_proc(char **args);

void mv_proc(char **args);

struct tagCMD getCommand(char *command_name);

typedef struct tagCMD {
    char *name;

    void (*proc)(char **args);
} CMD;

char g_cwd[PATH_MAX];

CMD g_cmds[] = {
        {"clear",   clear_proc},
        {"pwd",     pwd_proc},
        {"ls",      ls_proc},
        {"cd",      cd_proc},
        {"exit",    exit_proc},
        {"mkdir",   mkdir_proc},
        {"touch",   touch_proc},
        {"echo",    echo_proc},
        {"cp",      cp_proc},
        {"bin_vis", cash_binary_visualize_proc},
        {"mv",      mv_proc},
        {NULL,      command_not_found_proc}
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

void mkdir_proc(char **args) {
    char *path = args[1];
    size_t len = strlen(path);
    char *curr_path = malloc(len + 1);
    strcpy(curr_path, path);

    char *p = curr_path;
    while (*p != '\0') {
        if (*p == '/') {
            *p = '\0';
            if (mkdir(curr_path, 0755) != 0 && errno != EEXIST) {
                perror("Error occurred with mkdir");
                return;
            }
            *p = '/';
        }
        p++;
    }
    if (mkdir(curr_path, 0755) != 0 && errno != EEXIST) {
        perror("Error occurred with mkdir");
        return;
    }

    free(curr_path);
}

void touch_proc(char **args) {
    char *file_name = args[1];

    if (!strrchr(file_name, '.')) {
        file_name = strcat(file_name, ".txt");
    }

    FILE *fp = fopen(file_name, "a");
    if (fp == NULL) {
        perror("Error occurred with touch");
        return;
    }

    fclose(fp);
}

void echo_proc(char **args) {
    char *read_input_arg = args[1];
    char *read_param_arg = args[2];

    char *color = colorized(read_param_arg);
    if (0 != color) {
        printf("%s %s %s", color, read_input_arg, colorized("reset"));
    } else {
        fputs(read_input_arg, stdout);
    }
    putchar('\n');
}

void cp_proc(char **args) {
    char *read_input_arg = args[1];
    char *read_param_arg = args[2];

    if (read_input_arg == NULL || read_param_arg == NULL) {
        perror("CP commands missing arguments!!");
        return;
    }

    int input_file_read = open(read_input_arg, O_RDONLY);
    if (input_file_read == -1) {
        perror("CP can't open input file!!");
        return;
    }

    int output_file_write = open(read_param_arg, O_WRONLY | O_CREAT | O_TRUNC, 0664);
    if (output_file_write == -1) {
        perror("CP can't open output file!!");
        return;
    }

    char buffer[1024];
    ssize_t bytes_read;
    while ((bytes_read = read(input_file_read, buffer, sizeof(buffer))) > 0) {
        if (write(output_file_write, buffer, bytes_read) != bytes_read) {
            perror("CP can't write!!");
            return;
        }
    }
    if (bytes_read == -1) {
        perror("CP can't read!!");
        return;
    }
    close(input_file_read);
    close(output_file_write);
}

void cash_binary_visualize_proc(char **args) {
    char *read_input_arg = args[1];

    if (read_input_arg == NULL) {
        perror("CP commands missing arguments!!");
        return;
    }
    CASH_BINARY_TREE *CASH_BINARY_TREE = NULL;
    int count_args = 1;
    while (args[count_args] != NULL) {
        insert_cash_binary_tree(&CASH_BINARY_TREE, args[count_args]);
        ++count_args;
    }
    traverse_cash_binary_tree(CASH_BINARY_TREE);
    free(CASH_BINARY_TREE);
}

void mv_proc(char **args) {
    FILE *src;
    FILE *dst;
    int BUFSIZE = 4096;
    char *source_file = args[1];
    char *destination_file = args[2];
    char buf[4096];
    size_t nread;

    if ((src = fopen(source_file, "rb")) == NULL) {
        perror("MV can not read source file");
        return;
    }

    if ((dst = fopen(destination_file, "wb")) == NULL) {
        perror("MV can not write source file");
        fclose(src);
        return;
    }

    while ((nread = fread(buf, 1, BUFSIZE, src)) > 0) {
        if (fwrite(buf, 1, nread, dst) != nread) {
            perror("Error writing to destination file");
            fclose(src);
            fclose(dst);
            return;
        }
    }

    if (ferror(src)) {
        fclose(src);
        fclose(dst);
        return;
    }

    fclose(src);
    fclose(dst);

    if (remove(source_file) != 0) {
        perror("Error removing source file");
        return;
    }
}

#endif //CASH_COMMAND_FUNCS_H
