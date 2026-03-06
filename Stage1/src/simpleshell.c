#include <stdio.h>
#include <string.h>
#include "utilities/cd.h"
#include "utilities/env.h"
#include "utilities/structures.h"
#include "utilities/pwd.h"
#include "utilities/init.h"
#include "utilities/clr.h"
#include "utilities/split.h"
#include "utilities/environ.h"
#include "utilities/slice.h"
#include "utilities/echo.h"

int main(){
  initShell();
  print_all_subdirectories("home");
  while (1) {

    char input[1024];

    printf(">");
    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\n")] = '\0';

    char ** args = split(input, ' ');

    if (args[0] != NULL) {
      if (strcmp(args[0], "quit") == 0) {
        break;
      }
      else if (strcmp(args[0], "cd") == 0) {
        cd(args[1]);
      }
      else if (strcmp(args[0], "pwd") == 0) {
        pwd();
      }
      else if (strcmp(args[0], "clr") == 0) {
        clr();
      }
      else if (strcmp(args[0], "environ") == 0) {
        environ();
      }
      else if (strcmp(args[0], "echo") == 0) {
        echo(slice_from(args, 1));
      }
    }
    for (int i = 0; args[i] != NULL; i++)
      free(args[i]);
    free(args);
  }


  return 0;
}
