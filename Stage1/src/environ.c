#include <stdio.h>
#include <stdlib.h>
#include "utilities/env.h"
#include "utilities/environ.h"


void environ() {
  ENV *env = get_env_instance();
  if (!env) return;

  char **names = env->get_names(env);
  if (!names) return;
  
  for (int i = 0; names[i] != NULL; i++) {
    char * value = env->get_value(env, names[i]);
    if (value) {
        printf("%s=%s\n", names[i], value);
        free(value);
    }
  }
  
  free(names);
}

