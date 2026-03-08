#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utilities/helpers.h"


char **split(const char *str, char delim) {
  // splits str by delim and returns array of strings
    if (!str) return NULL;

    int count = 0;
    const char *tmp = str;
    while (*tmp) {
        while (*tmp == delim) tmp++;
        if (*tmp == '\0') break;

        count++;

        while (*tmp && *tmp != delim) tmp++;
    }

    char **tokens = malloc((count + 1) * sizeof(char *));
    if (!tokens) return NULL;


    int idx = 0;
    tmp = str;
    while (*tmp) {
        while (*tmp == delim) tmp++; 
        if (*tmp == '\0') break;

        const char *start = tmp;
        while (*tmp && *tmp != delim) tmp++;
        size_t len = tmp - start;

        tokens[idx] = malloc(len + 1);
        if (!tokens[idx]) {
            for (int j = 0; j < idx; j++) free(tokens[j]);
            free(tokens);
            return NULL;
        }
        strncpy(tokens[idx], start, len);
        tokens[idx][len] = '\0';
        idx++;
    }

    tokens[idx] = NULL;
    return tokens;
}

void free_split(char **args) {
  if (args == NULL) return;

  for (int i = 0; args[i] != NULL; i++) {
    free(args[i]);        
  }
  free(args);
}


char **slice_from(char **arr, int start) {
  // slices an array from start index to the end
    if (!arr) return NULL;

    int count = 0;
    while (arr[start + count] != NULL) count++;

    char **slice = malloc((count + 1) * sizeof(char *));
    if (!slice) return NULL;

    for (int i = 0; i < count; i++)
        slice[i] = arr[start + i]; 

    slice[count] = NULL;
    return slice;
}

void free_args(char **args) {
  // frees args from array
  if (args == NULL) return;  

  for (int i = 0; args[i] != NULL; i++) {
    free(args[i]);
  }
  free(args);
}


