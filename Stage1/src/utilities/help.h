#include <stdio.h>

#ifndef HELP_H
#define HELP_H
void help() {
  printf("cd <dir>     change the current directory\n");
  printf("clr          clear the screen\n");
  printf("dir <dir>    list the contents of directory <dir>\n");
  printf("environ      list all environment variables\n");
  printf("echo <text>  display <text> on the screen\n");
  printf("help         display this help manual\n");
  printf("pause        pause operation of the shell\n");
  printf("quit         quit the shell\n");
}
#endif
