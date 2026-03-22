#include <stdio.h>
#include <stdlib.h>
#include "utilities/help.h"

void help() {
  int result = system("more manual/readme.txt");

  if (result == -1) {
    perror("help command failed");
  }
}
/* Name: Serhii Ananiev
   Student ID: 39561
   I acknowledge the DCU Academic Integrity Policy */
