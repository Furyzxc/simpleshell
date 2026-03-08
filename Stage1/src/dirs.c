#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "utilities/structures.h"
#include "utilities/helpers.h"
#include "utilities/env.h"
#include "utilities/dirs.h"

#define MAX_CHILDREN 10


Directory * mkdir(char *name, Directory *parent) {
  // creates directory
  ENV *env = get_env_instance();
  Directory *dir = malloc(sizeof(Directory));
  // setting values for dir
  strcpy(dir->name, name);
  strcpy(dir->permissions, "drwxr-xr-x");
  // getting owner name from env
  char * owner = env->get_value(env, "USER");

  if (!owner) { 
    strcpy(dir->owner, "guest");
    strcpy(dir->group, "guest");
  } else {
    strcpy(dir->owner, owner);
    strcpy(dir->group, owner);
  }
  dir->hard_links = 0; // initiate 0 hard links. it should be changed later to calculate hard links
  dir->size = 4096; // initiate size 4096 per dir. it should be changed later to calculate subcontents
  dir-> child_count = 0; // no children
  dir->last_modified = time(NULL);
  dir->parent = parent;
  if (parent) {
    parent->children[parent->child_count++] = dir;
  }
  return dir;
}

Directory *get_home_dir() {
  // singleton for home dir
  static Directory *home_dir = NULL;

  if (home_dir == NULL) {
    home_dir = mkdir("home", NULL);
  }

  return home_dir;
}


Directory *get_dir_from_path(char * path) {
  // return dir from full path such as home/Donwloads/photos
  Directory *home_dir = get_home_dir();
  char pwd_path[1024];
  strcpy(pwd_path, path);
  char *paths[20];
  paths[0] = strtok(pwd_path, "/");

  int i = 1;
  while ((paths[i] = strtok(NULL, "/")) != NULL) {
    i++;
  }

  Directory *curr_dir = home_dir;
  for(int j = 0; j < i; j++) {
    for (int c = 0; c < curr_dir->child_count; c++) {
      if (strcmp(curr_dir->children[c]->name, paths[j]) == 0) {
        curr_dir = curr_dir->children[c];
      }
    }
  }
  return curr_dir;
}

void print_all_subdirectoriess(Directory *dir, char *path) {
  //helper function, prints recursively all subdirectories in format home/CSC1021/week1
  char *new_path = malloc(strlen(path) + strlen(dir->name) + 2);

  strcpy(new_path, path); 
  strcat(new_path, "/");
  strcat(new_path, dir->name);
  if (dir->child_count) {
    for (int i = 0; i < dir->child_count; i++) {
      print_all_subdirectoriess(dir->children[i], new_path);
    }
  }
  else {
    printf("%s\n", new_path);
  }

  free(new_path);
}


void print_all_subdirectories(char * path) {
  // prints all subdirectories in format home/CSC1021/week1
  Directory *dir = get_dir_from_path(path);
  print_all_subdirectoriess(dir, "");
}

char *get_path(Directory *dir) {
  // returns full path of given dir
    Directory *stack[100]; 
    int count = 0;

    Directory *tmp = dir;
    while (tmp != NULL) {
        stack[count++] = tmp;
        // move to parent
        tmp = tmp->parent;
    }

    size_t total_len = 0;
    for (int i = count - 1; i >= 0; i--) {
        total_len += strlen(stack[i]->name) + 1; 
    }

    char *path = malloc(total_len + 1);
    if (!path) return NULL;

    path[0] = '\0';

    for (int i = count - 1; i >= 0; i--) {
        strcat(path, "/");
        strcat(path, stack[i]->name);
    }

    return path;
}

Directory * get_dir_from_pwd(char * path) {
  // checks env, returns respective dir from it
  ENV *env = get_env_instance();
  // getting dir from env
  Directory * curr_dir = get_dir_from_path(env->get_value(env, "PWD"));
  // if path given
  if (path) {
    // split on particles by /
    char **new_dir_paths = split(path, '/');
    for (int i = 0; new_dir_paths[i] != NULL; i++) {
      if (strcmp(new_dir_paths[i], "..") == 0) {
        // go back to parent if there is one
        if (curr_dir->parent) {
          curr_dir = curr_dir->parent;
        }
      }
      // if its same dir do nothing
      else if (strcmp(new_dir_paths[i], ".") == 0) {}

      else {
        int found = 0; // not found
        for (int j = 0; j < curr_dir->child_count; j++) {
          Directory *subdir = curr_dir->children[j];
          if (strcmp(subdir->name, new_dir_paths[i]) == 0) { // if its same name as child dir
            curr_dir = subdir;
            found = 1; // found
            break;
          }
        }
        if (!found) {
          return NULL;
        }
      }
    }


    return curr_dir;
  }
  return NULL;
}