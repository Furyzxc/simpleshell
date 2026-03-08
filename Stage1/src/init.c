#include <stdio.h>
#include "utilities/dirs.h"
#include "utilities/structures.h"
#include "utilities/pwd.h"
#include "utilities/env.h"
#include "utilities/init.h"

void init(){
  // actions to initiate the shell
  ENV *env = get_env_instance();
  // setting env values
  env->set_value(env, "HOME", "home");
  env->set_value(env, "PWD", "home");
  env->set_value(env, "SHELL", "bin/simpleshell");
  env->set_value(env, "USER", "serhii");
  env->set_value(env, "LANG", "en_US.UTF-8");

  // making directories
  Directory *home_dir = get_home_dir();

  Directory *Downloads = mkdir("Downloads", home_dir);
  mkdir("photos", Downloads);

  Directory *CSC1021 = mkdir("CSC1021", home_dir);
  mkdir("week1", CSC1021);
  mkdir("week2", CSC1021);
  mkdir("week3", CSC1021);
  mkdir("week4", CSC1021);
  mkdir("week5", CSC1021);

  mkdir("notes", home_dir);
}


