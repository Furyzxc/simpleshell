#include <stdio.h>
#include <time.h>
#include "dirs.h"
#include "env.h"
#include "structures.h"
#ifndef DIR_H
#define DIR_H

void print(Directory *d, char *name) {
  char *name_to_print = d->name;
  if (strcmp(name, "..") == 0 || strcmp(name, ".") == 0) {
    name_to_print = name;
  }
  char *time_str = ctime(&(d->last_modified));
  time_str[strcspn(time_str, "\n")] = '\0';
  printf("%s %d %s %s %d %s %s\n",
    d->permissions,
    d->hard_links,
    d->owner,
    d->group,
    d->size,
    time_str,
    name_to_print
    );
}

void dir(){
  ENV *env = getEnvInstance();
  Directory * pwd = getDirFromPath(env->getValue(env, "PWD"));

  print(pwd, ".");

  if (pwd->parent) {
    print(pwd->parent, "..");
  }
  for (int i = 0; i < pwd->child_count; i++) {
    print(pwd->children[i], "");
  }
}

#endif
