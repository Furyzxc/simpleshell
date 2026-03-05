#include <stdio.h>
#include "structures.h"
#include "pwd.h"
#include "env.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *split_next(char *str) {
    if (!str || *str == '\0') return NULL;

    char *delim_pos = strchr(str, '/');
    char *token;

    if (delim_pos) {
        size_t len = delim_pos - str;
        token = malloc(len + 1);       // allocate memory for token
        strncpy(token, str, len);
        token[len] = '\0';
        // remove token from original string
        memmove(str, delim_pos + 1, strlen(delim_pos + 1) + 1);
    } else {
        // last token
        token = strdup(str);           // copy the remaining string
        str[0] = '\0';                 // empty the original string
    }

    return token;
}

Directory *cd(char *path, Directory *current_dir) {
  char *token;
  while ((token = split_next(path)) != NULL) {
    if (strcmp(token, "..") == 0) {
      if (current_dir->parent) {
        current_dir = current_dir->parent;
      } else {
        printf("simpleshell: cd: %s: No such file or directory\n", path);
      }
    }
    else if (strcmp(token, ".") == 0) {
      free(token);
      continue;
    }
    else {
      for (int i = 0; i < current_dir->child_count; i++) {
        Directory *subdir = current_dir->children[i];
        if (strcmp(subdir->name, token) == 0) {
          current_dir = subdir;
          break;
        }
      }
    }
    free(token);
  }

  ENV *env = getEnvInstance();
  env->setValue(env, "PWD", pwd(current_dir));
  return current_dir;
}
