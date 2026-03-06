#include <stdio.h>
#include "env.h"

#ifndef ENVIRON
#define ENVIRON

void environ() {
  ENV *env = getEnvInstance();

  char **names = env->getNames(env);

  for (int i = 0; names[i] != NULL; i++) {
    const char * value = env->getValue(env, names[i]);

    printf("%s=%s\n", names[i], value);
  }
}

#endif
