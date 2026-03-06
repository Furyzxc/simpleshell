#include <stdlib.h>

/**
 * Slice an array of strings from start index to the end (shallow copy)
 * The returned array is NULL-terminated.
 */
char **slice_from(char **arr, int start) {
    if (!arr) return NULL;

    // Count remaining elements
    int count = 0;
    while (arr[start + count] != NULL) count++;

    // Allocate new array (+1 for NULL terminator)
    char **slice = malloc((count + 1) * sizeof(char *));
    if (!slice) return NULL;

    for (int i = 0; i < count; i++)
        slice[i] = arr[start + i];  // just copy pointer

    slice[count] = NULL;
    return slice;
}
