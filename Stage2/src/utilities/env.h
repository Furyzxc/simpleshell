#ifndef ENV_H
#define ENV_H

#include <stddef.h>

#define MAX_VARS 100
#define MAX_NAME 256
#define MAX_VALUE 256

typedef struct Variable {
  char name[MAX_NAME];
  char value[MAX_VALUE];
} Variable;

typedef struct ENV ENV;

typedef struct ENV {
  Variable envs[MAX_VARS];
  int count;

  void (*set_value)(ENV*, const char*, const char*);
  char* (*get_value)(ENV*, const char*);
  char **(*get_names)(ENV*);
} ENV;

ENV* get_env_instance();


// Usage:
//    ENV *env = getEnvInstance();
//    env->setValue(env, "PWD", "/home");
//    char *pwd = env->getValue(env, "PWD");
#endif

/* Name: Serhii Ananiev
   Student ID: 39561
   I acknowledge the DCU Academic Integrity Policy */
