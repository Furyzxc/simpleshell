#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>

#include "utilities/cd.h"
#include "utilities/env.h"
#include "utilities/pwd.h"
#include "utilities/clr.h"
#include "utilities/helpers.h"
#include "utilities/environ.h"
#include "utilities/echo.h"
#include "utilities/pause.h"
#include "utilities/help.h"
#include "utilities/dir.h"

int check_args(const char *name, int max_args, char **args) {
    if (!args) return 0;

    int count = 0;
    while (args[count] != NULL) count++;

    if (count > max_args) {
        printf("simpleshell: %s: too many arguments\n", name);
        return 1;
    }

    return 0;
}

int commands_handler(char **args) {
    if (args[0] == NULL) return 0;

    // background
    int background = 0;
    int i = 0;
    while (args[i] != NULL) i++;

    if (i > 0 && strcmp(args[i - 1], "&") == 0) {
        background = 1;
        args[i - 1] = NULL;
    }

    // io redirection
    char *input_file = NULL;
    char *output_file = NULL;
    int append = 0;

    for (int j = 0; args[j] != NULL; j++) {

        if ((strcmp(args[j], "<") == 0) ||
            (strcmp(args[j], ">") == 0) ||
            (strcmp(args[j], ">>") == 0)) {

            if (args[j + 1] == NULL) {
                printf("simpleshell: syntax error near unexpected token\n");
                return 0;
            }
        }

        if (strcmp(args[j], "<") == 0) {
            input_file = args[j + 1];
            args[j] = NULL;
            args[j + 1] = NULL;
        }
        else if (strcmp(args[j], ">") == 0) {
            output_file = args[j + 1];
            append = 0;
            args[j] = NULL;
            args[j + 1] = NULL;
        }
        else if (strcmp(args[j], ">>") == 0) {
            output_file = args[j + 1];
            append = 1;
            args[j] = NULL;
            args[j + 1] = NULL;
        }
    }

    // save stdout for internal commands
    int saved_stdout = dup(STDOUT_FILENO);

    if (output_file) {
        int fd;
        if (append)
            fd = open(output_file, O_WRONLY | O_CREAT | O_APPEND, 0644);
        else
            fd = open(output_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);

        if (fd < 0) {
            perror("output file");
            return 0;
        }

        dup2(fd, STDOUT_FILENO);
        close(fd);
    }

    // internal commands
    if (strcmp(args[0], "quit") == 0) {
        return 1;
    }
    else if (strcmp(args[0], "cd") == 0) {
        if (!check_args("cd", 2, args))
            cd(args[1]);
    }
    else if (strcmp(args[0], "pwd") == 0) {
        if (!check_args("pwd", 1, args))
            pwd();
    }
    else if (strcmp(args[0], "clr") == 0) {
        if (!check_args("clr", 1, args))
            clr();
    }
    else if (strcmp(args[0], "dir") == 0) {
        if (!check_args("dir", 2, args))
            dir(args[1]);
    }
    else if (strcmp(args[0], "environ") == 0) {
        if (!check_args("environ", 1, args))
            environ();
    }
    else if (strcmp(args[0], "echo") == 0) {
        if (args[1] != NULL)
            echo(slice_from(args, 1));
    }
    else if (strcmp(args[0], "help") == 0) {
        if (!check_args("help", 1, args))
            help();
    }
    else if (strcmp(args[0], "pause") == 0) {
        if (!check_args("pause", 1, args))
            pause_shell();
    }

    // external commands
    else {
        pid_t pid = fork();

        if (pid == 0) {
            // child

            // input redirection
            if (input_file) {
                int fd = open(input_file, O_RDONLY);
                if (fd < 0) {
                    perror("input file");
                    exit(1);
                }
                dup2(fd, STDIN_FILENO);
                close(fd);
            }

            // output redirection
            if (output_file) {
                int fd;
                if (append)
                    fd = open(output_file, O_WRONLY | O_CREAT | O_APPEND, 0644);
                else
                    fd = open(output_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);

                if (fd < 0) {
                    perror("output file");
                    exit(1);
                }

                dup2(fd, STDOUT_FILENO);
                close(fd);
            }

            // required environment variable
            setenv("parent", "simpleshell", 1);

            execvp(args[0], args);
            perror(args[0]);
            exit(1);
        }

        else if (pid > 0) {
            if (!background) {
                waitpid(pid, NULL, 0);
            } else {
                printf("[process running in background: %d]\n", pid);
            }
        }

        else {
            perror("fork failed");
        }
    }

    //restore stdout
    dup2(saved_stdout, STDOUT_FILENO);
    close(saved_stdout);

    return 0;
}

char **helper(char *input) {
    input[strcspn(input, "\n")] = '\0';
    return split(input, ' ');
}

void handle_input(char *filename) {
    FILE *file = NULL;

    if (filename != NULL) {
        file = fopen(filename, "r");

        if (!file) {
            printf("simpleshell: %s: cannot open file.\n", filename);
            return;
        }
    }

    char input[1024];

    // batch mode
    if (file != NULL) {
        while (fgets(input, sizeof(input), file) != NULL) {
            char **args = helper(input);

            if (args[0] != NULL) {
                int stop = commands_handler(args);
                free_args(args);
                if (stop) break;
            } else {
                free_args(args);
            }
        }
        fclose(file);
        return;
    }

    // interactive mode
    ENV *env = get_env_instance();

    while (1) {
        printf("%s> ", env->get_value(env, "PWD"));

        if (fgets(input, sizeof(input), stdin) == NULL) break;

        char **args = helper(input);

        if (args[0] != NULL) {
            int stop = commands_handler(args);
            free_args(args);
            if (stop) break;
        } else {
            free_args(args);
        }
    }
}

/* Name: Serhii Ananiev
   Student ID: 39561
   I acknowledge the DCU Academic Integrity Policy */
