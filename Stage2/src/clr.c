#include <stdio.h>
#include "utilities/clr.h"

void clr() {
  // moves the screen to bottom
  printf("\033[2J");
  printf("\033[H");
}

/* Name: Serhii Ananiev
   Student ID: 39561
   I acknowledge the DCU Academic Integrity Policy */
