#ifndef SPLIT_H
#define SPLIT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Splits the input string `str` by delimiter `delim`.
 * Returns an array of strings terminated with NULL.
 * Caller must free both the array and each string.
 */
char **split(const char *str, char delim) {
    if (!str) return NULL;

    // 1. Count tokens
    int count = 0;
    const char *tmp = str;
    while (*tmp) {
        // skip consecutive delimiters
        while (*tmp == delim) tmp++;
        if (*tmp == '\0') break;

        count++;
        // move to next delimiter
        while (*tmp && *tmp != delim) tmp++;
    }

    // 2. Allocate array (plus 1 for NULL terminator)
    char **tokens = malloc((count + 1) * sizeof(char *));
    if (!tokens) return NULL;

    // 3. Extract tokens
    int idx = 0;
    tmp = str;
    while (*tmp) {
        while (*tmp == delim) tmp++; // skip delimiters
        if (*tmp == '\0') break;

        const char *start = tmp;
        while (*tmp && *tmp != delim) tmp++;
        size_t len = tmp - start;

        tokens[idx] = malloc(len + 1);
        if (!tokens[idx]) {
            // free everything if allocation fails
            for (int j = 0; j < idx; j++) free(tokens[j]);
            free(tokens);
            return NULL;
        }
        strncpy(tokens[idx], start, len);
        tokens[idx][len] = '\0';
        idx++;
    }

    tokens[idx] = NULL; // null-terminate array
    return tokens;
}

#endif
