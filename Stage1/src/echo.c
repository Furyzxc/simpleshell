#include <stdio.h>
#include <string.h>
#include "utilities/echo.h"

void echo(char ** s) {
  int i = 0;
  while (s[i+1] != NULL) {
    printf("%s ", s[i]);
    i++;
  }
  printf("%s\n", s[i]);
}
