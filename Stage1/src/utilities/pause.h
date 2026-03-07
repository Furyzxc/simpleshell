#include <stdio.h>
#include <string.h>
#ifndef PAUSE_H
#define PAUSE_H
void pause() {
  int character = getchar();

  while (character != '\n') {
    character = getchar();
  }
}

#endif
