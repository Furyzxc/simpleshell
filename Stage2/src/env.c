#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utilities/env.h"


void set_value(ENV *e, const char *name, const char *value) {
    // sets value for env
    if (!e || !name || !value) return;

    int found = 0; // checks if found then update value
    for (int i = 0; i < e->count; i++) {
        if (strcmp(e->envs[i].name, name) == 0) {
            strncpy(e->envs[i].value, value, MAX_VALUE - 1);
            e->envs[i].value[MAX_VALUE - 1] = '\0';
            found = 1;
            break;
        }
    }

    if (!found && e->count < MAX_VARS) { // if not found create new one
        strncpy(e->envs[e->count].name, name, MAX_NAME - 1);
        e->envs[e->count].name[MAX_NAME - 1] = '\0';

        strncpy(e->envs[e->count].value, value, MAX_VALUE - 1);
        e->envs[e->count].value[MAX_VALUE - 1] = '\0';

        e->count++;
    }
}

char *get_value(ENV *e, const char *name) {
    // gets value for env for name
    if (!e || !name) return NULL; // if no name or env given return null

    for (int i = 0; i < e->count; i++) { // checks for each name and if its same then return value
        if (e->envs[i].name[0] != '\0' && strcmp(e->envs[i].name, name) == 0) {
            char *copy = malloc(strlen(e->envs[i].value) + 1);
            if (!copy) return NULL;
            strcpy(copy, e->envs[i].value);
            return copy; 
        }
    }
    return NULL; 
}


char **get_names(ENV *e) {
    if (!e || e->count == 0) return NULL;

    char **names = malloc((e->count + 1) * sizeof(char *));
    if (!names) return NULL;

    for (int i = 0; i < e->count; i++) {
        const char *current_name = e->envs[i].name[0] ? e->envs[i].name : "";
        names[i] = malloc(strlen(current_name) + 1);
        if (!names[i]) {
     
            for (int j = 0; j < i; j++) free(names[j]);
            free(names);
            return NULL;
        }
        strcpy(names[i], current_name);
    }

    names[e->count] = NULL; 
    return names;
}

ENV *get_env_instance() {
    static ENV *instance = NULL;

    if (!instance) {
        instance = malloc(sizeof(ENV));
        if (!instance) return NULL;

        instance->count = 0;
        instance->set_value = set_value;
        instance->get_value = get_value;
        instance->get_names = get_names;

        for (int i = 0; i < MAX_VARS; i++) {
            instance->envs[i].name[0] = '\0';
            instance->envs[i].value[0] = '\0';
        }
    }

    return instance;
}