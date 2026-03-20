#include <stdio.h>
#include "utilities/clr.h"

void clr() {
  // moves the screen to bottom
  printf("\033[2J");
  printf("\033[H");
}