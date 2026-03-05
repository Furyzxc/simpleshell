#include <stdio.h>
#include "utilities/dirs.h"
#include "utilities/structures.h"
#include "utilities/pwd.h"
#include "utilities/cd.h"
#include "utilities/env.h"
#include "utilities/clr.h"

int main(int argc, char * argv[]){
  Directory *home_dir = mkdir("Home", NULL);

  Directory *Downloads = mkdir("Downloads", home_dir);
  Directory *photos = mkdir("photos", Downloads);

  Directory *CSC1021 = mkdir("CSC1021", home_dir);
  Directory *week1 = mkdir("week1", CSC1021);
  Directory *week2 = mkdir("week2", CSC1021);
  Directory *week3 = mkdir("week3", CSC1021);
  Directory *week4 = mkdir("week4", CSC1021);
  Directory *week5 = mkdir("week5", CSC1021);

  ENV *env = getEnvInstance();
  env->setValue(env, "HOME", home_dir->name);
  env->setValue(env, "PWD", home_dir->name);

  char path[] = "Downloads/../Downloads/./photos";
  cd(path, home_dir);
  printf("%s\n", env->getValue(env, "PWD"));
  //print_all_subdirectories(home_dir, "");

  free(env);
  return 0;
}
