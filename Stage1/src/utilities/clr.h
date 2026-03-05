#include <stdio.h>

#ifndef CLR_H
#define CLR_H

void clr() {
  printf("\033[2J");
  printf("\033[H");
}

#endif
