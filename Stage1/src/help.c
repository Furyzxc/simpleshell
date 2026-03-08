#include <stdio.h>
#include "utilities/help.h"

void help() {  // prints manual
  printf("cd <dir>     change the current directory\n");
  printf("pwd          present working directory\n")
  printf("clr          clear the screen\n");
  printf("dir <dir>    list the contents of directory <dir>\n");
  printf("environ      list all environment variables\n");
  printf("echo <text>  display <text> on the screen\n");
  printf("help         display this help manual\n");
  printf("pause        pause operation of the shell\n");
  printf("quit         quit the shell\n");
}

