#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utilities/structures.h"
#include "utilities/env.h"
#include "utilities/helpers.h"
#include "utilities/dirs.h"
#include "utilities/cd.h"


void cd(char *path) {
  ENV *env = get_env_instance();
  Directory *curr_dir;
  if (path == NULL) { // if no path specified, then go to home directory
    curr_dir = get_dir_from_path(env->get_value(env, "HOME"));
  }
  else { // otherwise go to path
    curr_dir = get_dir_from_pwd(path);
  }


  if (curr_dir) {
    // getting fullpath, eg home/Donwloads/photos
    char * fullpath = get_path(curr_dir); 
    // setting env value
    env->set_value(env, "PWD", fullpath);
    free(fullpath);
  } else { // if not found
    printf("simpleshell: cd: %s: No such directory\n", path);
  }
}

/* Name: Serhii Ananiev
   Student ID: 39561
   I acknowledge the DCU Academic Integrity Policy */
