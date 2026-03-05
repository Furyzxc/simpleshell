#include <stdio.h>

#ifndef ENV_H
#define ENV_H

typedef struct Variable {
  char name[256];
  char value[256];
} Variable;

typedef struct ENV ENV;

typedef struct ENV {
  Variable envs[100];
  int count;

  void (*setValue)(struct ENV*, const char*, const char*);
  const char* (*getValue)(struct ENV*, const char*);
} ENV;


const char * getValue(struct ENV *e, const char * name) {
  for (int i = 0; i < e->count; i++) {
    if (strcmp(e->envs[i].name, name) == 0) {
      return e->envs[i].value;
    }
  }
}

void setValue(ENV *e, const char*name, const char*value) {
  int found = 0;
  for (int i = 0; i < e->count; i++) {
    if(strcmp(e->envs[i].name, name) == 0) {
      strcpy(e->envs[i].value, value);
      found = 1;
    }
  }
  if (!found) {
    strcpy(e->envs[e->count].name, name);
    strcpy(e->envs[e->count++].value, value);
  }
}

ENV* getEnvInstance() {
  static ENV *instance = NULL;
  if (instance == NULL) {
    instance = malloc(sizeof(ENV));
    instance->count = 0;
    instance->setValue = setValue;
    instance->getValue = getValue;
  }
  return instance;
}

#endif
