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
  // checks if there is not more then max_args. for example cd can take max 2 arguments: cd and dir
    if (!args) return 0;

    int count = 0;
    while (args[count] != NULL) count++;

    if (count > max_args) {// too many args
        printf("simpleshell: %s: too many arguments\n", name);
        return 1; // error
    }

    return 0; // ok
}

int commands_handler(char **args) {
  // checks for command given and does appopriate action
  if (args[0] != NULL) {

    if (strcmp(args[0], "quit") == 0) {//quits
      if (check_args("quit", 1, args));
      else return 1;
    }
    else if (strcmp(args[0], "cd") == 0) {// cds to dir
      if (check_args("cd", 2, args));
      else cd(args[1]);
    }
    else if (strcmp(args[0], "pwd") == 0) {// present working dir
      if (check_args("pwd", 1, args));
      else pwd();
    }
    else if (strcmp(args[0], "clr") == 0) { // clears screen
      if (check_args("clr", 1, args));
      else clr();
    }
    else if (strcmp(args[0], "dir") == 0) { // lists contents
      if (check_args("dir", 2, args));
      else dir(args[1]);
    }
    else if (strcmp(args[0], "environ") == 0) { // lists envs
      if (check_args("environ", 1, args));
      else environ();
    }
    else if (strcmp(args[0], "echo") == 0) { //echos text
      if (args[1] != NULL) {
        echo(slice_from(args, 1));
      }
    }
    else if (strcmp(args[0], "help") == 0) { // manual
      if (check_args("help", 1, args));
      else help();
    }
    else if (strcmp(args[0], "pause") == 0) { // pause till enter pressed
      if (check_args("pause", 1, args));
      else pause();
    }
    else { // not found command
      printf("simpleshell: %s: command not found\n", args[0]);
    }
  }
  return 0;
}

char **helper(char * input) { // clears whitespaces
  input[strcspn(input, "\n")] = '\0';

  return split(input, ' ');
}


void handle_input(char * filename) {
  // if filename given then go through it, otherwise expects user input
  FILE *file = NULL;
// if filename present then open it
  if (filename != NULL) {
    file = fopen(filename, "r");

    if (!file) { // couldnt find file, prints error msg
      printf("simpleshell: %s: cannot open file.\n", filename);
      return;
    }
  }
  char input[1024];
  // read from file
  if (file != NULL) {
    while (fgets(input, sizeof(input), file) != NULL) {

      char **args = helper(input);
      if (args[0] != NULL) {
        int stop = commands_handler(args);
        free_args(args);
        if (stop) break; // quit shell
      } else {
        free_args(args);
      }
    }
    fclose(file);
    return; // finish
  }
// otherwise take user input
  while (1) {
    printf("> "); // for interaction
    if (fgets(input, sizeof(input), stdin) == NULL) break;
    char **args = helper(input);
      if (args[0] != NULL) { // if there args then handle command
        int stop = commands_handler(args);
        free_args(args);
        if (stop) break;
    } else { 
      free_args(args);
    }
  }

}

