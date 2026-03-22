#include <stdio.h>
#include <time.h>
#include <string.h>
#include "utilities/dirs.h"
#include "utilities/env.h"
#include "utilities/structures.h"
#include "utilities/dir.h"

void print(Directory *d, char *name) {
  // function to output directory in ls -al format
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

  if (path) { // if path, get the dir
    pwd = get_dir_from_pwd(path);
  } else { // if no path then get present dir
    path = env->get_value(env, "PWD");
    pwd = get_dir_from_path(path);
  }

  if (!pwd) {// not found
    printf("dir: cannot access '%s': No such directory\n", path);
    return;
  }

  print(pwd, "."); // current dir

  if (pwd->parent) { // parent dir
    print(pwd->parent, "..");
  }
  for (int i = 0; i < pwd->child_count; i++) { // children
    print(pwd->children[i], "");
  }
}

/* Name: Serhii Ananiev
   Student ID: 39561
   I acknowledge the DCU Academic Integrity Policy */
