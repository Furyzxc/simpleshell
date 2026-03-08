#include <stdio.h>
#include "utilities/clr.h"

void clr() {
  printf("\033[2J");
  printf("\033[H");
}