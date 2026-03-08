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
  if (path == NULL) {
    curr_dir = get_dir_from_path(env->get_value(env, "HOME"));
  }
  else {
    curr_dir = get_dir_from_pwd(path);
  }


  if (curr_dir) {
    char * fullpath = get_path(curr_dir);
    env->set_value(env, "PWD", fullpath);
    free(fullpath);
  } else {
    printf("simpleshell: cd: %s: No such directory\n", path);
  }
}
