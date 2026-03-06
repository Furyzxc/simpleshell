#include <stdlib.h>
#include <stdio.h>
#include "env.h"
#ifndef PWD_H
#define PWD_H

void pwd() {
    ENV *env = getEnvInstance();
    printf("%s\n", env->getValue(env, "PWD"));
}

#endif
