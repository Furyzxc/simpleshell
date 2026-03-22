#ifndef HELPERS_H
#define HELPERS_H


/**
 * Splits the input string `str` by delimiter `delim`.
 * Returns an array of strings terminated with NULL.
 * Caller must free both the array and each string.
 */
char **split(const char *str, char delim);

/**
 * Slice an array of strings from start index to the end (shallow copy)
 * The returned array is NULL-terminated.
 */
char **slice_from(char **arr, int start);

void free_args(char **args);

#endif

/* Name: Serhii Ananiev
   Student ID: 39561
   I acknowledge the DCU Academic Integrity Policy */
