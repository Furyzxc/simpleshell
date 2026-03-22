#include <stdio.h>
#include <string.h>
#include "utilities/pause.h"

void pause_shell() {
  // pauses shell till enter is pressed
  int character = getchar();

  while (character != '\n') {
    character = getchar();
  }
}

/* Name: Serhii Ananiev
   Student ID: 39561
   I acknowledge the DCU Academic Integrity Policy */
