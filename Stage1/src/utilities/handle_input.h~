#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cd.h"
#include "env.h"
#include "pwd.h"
#include "clr.h"
#include "split.h"
#include "environ.h"
#include "slice.h"
#include "echo.h"
#include "pause.h"
#include "help.h"
#include "dir.h"

void free_split(char **args) {
  if (args == NULL) return;   // nothing to free

  for (int i = 0; args[i] != NULL; i++) {
    free(args[i]);          // free each string
  }
  free(args);
}

int commands_handler(char **args) {
  if (args[0] != NULL) {
    if (strcmp(args[0], "quit") == 0) {
      return 1;
    }
    else if (strcmp(args[0], "cd") == 0) {
      if (args[1] != NULL) {
        cd(args[1]);
      }
    }
    else if (strcmp(args[0], "pwd") == 0) {
      pwd();
    }
    else if (strcmp(args[0], "clr") == 0) {
      clr();
    }
    else if (strcmp(args[0], "dir") == 0) {
      dir();
    }
    else if (strcmp(args[0], "environ") == 0) {
      environ();
    }
    else if (strcmp(args[0], "echo") == 0) {
      echo(slice_from(args, 1));
    }
    else if (strcmp(args[0], "help") == 0) {
      help();
    }
    else if (strcmp(args[0], "pause") == 0) {
      pause();
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

#ifndef HANDLE_INPUT_H
#define HANDLE_INPUT_H


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
        free_split(args);
        if (stop) break;
      } else {
        free_split(args);
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
      free_split(args);
      if (stop) break;
    } else {
      free_split(args);
    }
  }

}

#endif
