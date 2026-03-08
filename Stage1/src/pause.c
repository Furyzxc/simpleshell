#include <stdio.h>
#include <string.h>
#include "utilities/pause.h"

void pause() {
  int character = getchar();

  while (character != '\n') {
    character = getchar();
  }
}

