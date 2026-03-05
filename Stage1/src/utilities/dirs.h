#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structures.h"

#define MAX_CHILDREN 10

#ifndef DIRS_H
#define DIRS_H

Directory * mkdir(char *name, Directory *parent) {
  Directory *dir = malloc(sizeof(Directory));
  strcpy(dir->name, name);
  dir-> child_count = 0;

  dir->parent = parent;
  if (parent) {
    parent->children[parent->child_count++] = dir;
  }
  return dir;
}


void print_all_subdirectories(Directory * dir, const char *paths) {
  char *new_path = malloc(strlen(paths) + strlen(dir->name) + 2);
  strcpy(new_path, paths);
  strcat(new_path, "/");
  strcat(new_path, dir->name);
  if (dir->child_count) {
    for (int i = 0; i < dir->child_count; i++) {
      print_all_subdirectories(dir->children[i], new_path);
    }
  }
  else {
    printf("%s\n", new_path);
  }

  free(new_path);
}
#endif
