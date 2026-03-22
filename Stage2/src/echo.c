#include <stdio.h>
#include <string.h>
#include "utilities/echo.h"

void echo(char ** s) {
  // splits by whitespace and prints s
  int i = 0;
  while (s[i+1] != NULL) {
    printf("%s ", s[i]);
    i++;
  }
  printf("%s\n", s[i]);
}

/* Name: Serhii Ananiev
   Student ID: 39561
   I acknowledge the DCU Academic Integrity Policy */
