#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
        return 1; // error
    }

    return 0; // ok
}

int commands_handler(char **args) {
  if (args[0] != NULL) {

    if (strcmp(args[0], "quit") == 0) {
      if (check_args("quit", 1, args));
      else return 1;
    }
    else if (strcmp(args[0], "cd") == 0) {
      if (check_args("cd", 2, args));
      else cd(args[1]);
    }
    else if (strcmp(args[0], "pwd") == 0) {
      if (check_args("pwd", 1, args));
      else pwd();
    }
    else if (strcmp(args[0], "clr") == 0) {
      if (check_args("clr", 1, args));
      else clr();
    }
    else if (strcmp(args[0], "dir") == 0) {
      if (check_args("dir", 2, args));
      else dir(args[1]);
    }
    else if (strcmp(args[0], "environ") == 0) {
      if (check_args("environ", 1, args));
      else environ();
    }
    else if (strcmp(args[0], "echo") == 0) {
      if (args[1] != NULL) {
        echo(slice_from(args, 1));
      }
    }
    else if (strcmp(args[0], "help") == 0) {
      if (check_args("help", 1, args));
      else help();
    }
    else if (strcmp(args[0], "pause") == 0) {
      if (check_args("pause", 1, args));
      else pause();
    }
    else {
      printf("simpleshell: %s: command not found\n", args[0]);
    }
  }
  return 0;
}

char **helper(char * input) {
  input[strcspn(input, "\n")] = '\0';

  return split(input, ' ');
}


void handle_input(char * filename) {
  FILE *file = NULL;

  if (filename != NULL) {
    file = fopen(filename, "r");

    if (!file) {
      printf("simpleshell: %s: cannot open file.\n", filename);
      return;
    }
  }
  char input[1024];

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

  while (1) {
    printf("> ");
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

