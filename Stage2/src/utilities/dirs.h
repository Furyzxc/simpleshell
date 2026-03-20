#include "structures.h"

#ifndef DIRS_H
#define DIRS_H


Directory * mkdir(char *name, Directory *parent);

Directory *get_home_dir();

Directory *get_dir_from_path(char * path);

void print_all_subdirectories(char * path);

char *get_path(Directory *dir);

Directory * get_dir_from_pwd(char * path);

#endif