#include <stdio.h>
#include <stdio.h>
#include "dirs.h"
#include "structures.h"
#include "pwd.h"
#include "env.h"

#ifndef INIT_H
#define INIT_H

void initShell(){
  Directory *home_dir = getHomeDirectory("Home", NULL);

  Directory *Downloads = mkdir("Downloads", home_dir);
  mkdir("photos", Downloads);

  Directory *CSC1021 = mkdir("CSC1021", home_dir);
  mkdir("week1", CSC1021);
  mkdir("week2", CSC1021);
  mkdir("week3", CSC1021);
  mkdir("week4", CSC1021);
  mkdir("week5", CSC1021);

  mkdir("notes", home_dir);

  ENV *env = getEnvInstance();
  env->setValue(env, "HOME", home_dir->name);
  env->setValue(env, "PWD", home_dir->name);
}

#endif
