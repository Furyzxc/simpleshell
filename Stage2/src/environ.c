#include <stdio.h>
#include <stdlib.h>
#include "utilities/env.h"
#include "utilities/environ.h"


void environ() {
  // prints all env values in format name=value
  ENV *env = get_env_instance();
  if (!env) return;// null check

  // getting names
  char **names = env->get_names(env);
  if (!names) return;

  for (int i = 0; names[i] != NULL; i++) {
      // for each name print get it value and print it
    char * value = env->get_value(env, names[i]);
    if (value) {
        printf("%s=%s\n", names[i], value);
        free(value);
    }
  }
  // free memory
  free(names);
}

/* Name: Serhii Ananiev
   Student ID: 39561
   I acknowledge the DCU Academic Integrity Policy */
