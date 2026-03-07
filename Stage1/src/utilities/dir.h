#include <stdio.h>
#include <time.h>
#include "dirs.h"
#include "env.h"
#include "structures.h"
#ifndef DIR_H
#define DIR_H

void dir(){
  ENV *env = getEnvInstance();
  Directory * pwd = getDirFromPath(env->getValue(env, "PWD"));

  for (int i = 0; i < pwd->child_count; i++) {
    char *time_str = ctime(&(pwd->last_modified));
    time_str[strcspn(time_str, "\n")] = '\0';
    printf("%s %d %s %s %d %s %s\n",
      pwd->permissions,
      pwd->hard_links,
      pwd->owner,
      pwd->group,
      pwd->size,
      time_str,
      pwd->children[i]->name
      );
  }
}

#endif
