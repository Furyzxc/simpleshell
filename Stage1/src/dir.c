#include <stdio.h>
#include <time.h>
#include <string.h>
#include "utilities/dirs.h"
#include "utilities/env.h"
#include "utilities/structures.h"
#include "utilities/dir.h"

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

void dir(char * path){
  ENV *env = get_env_instance();
  Directory *pwd = NULL;

  if (path) {
    pwd = get_dir_from_pwd(path);
  } else {
    path = env->get_value(env, "PWD");
    pwd = get_dir_from_path(path);
  }

  if (!pwd) {
    printf("dir: cannot access '%s': No such directory\n", path);
    return;
  }

  print(pwd, ".");

  if (pwd->parent) {
    print(pwd->parent, "..");
  }
  for (int i = 0; i < pwd->child_count; i++) {
    print(pwd->children[i], "");
  }
}
