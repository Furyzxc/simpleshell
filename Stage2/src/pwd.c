#include <stdlib.h>
#include <stdio.h>
#include "utilities/env.h"
#include "utilities/pwd.h"

void pwd() {
    // checks env value for PWD and prints it
    ENV *env = get_env_instance();
    printf("%s\n", env->get_value(env, "PWD"));
}

/* Name: Serhii Ananiev
   Student ID: 39561
   I acknowledge the DCU Academic Integrity Policy */
