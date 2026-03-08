#include <stdlib.h>
#include <stdio.h>
#include "utilities/env.h"
#include "utilities/pwd.h"

void pwd() {
    ENV *env = get_env_instance();
    printf("%s\n", env->get_value(env, "PWD"));
}
