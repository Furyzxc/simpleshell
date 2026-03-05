#ifndef PWD_H
#define PWD_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Recursive helper
char* pwdr(Directory *dir) {
    if (dir->parent == NULL) {
        // Base case: root directory
        char *root_path = malloc(strlen(dir->name) + 2); // +1 for '/', +1 for '\0'
        strcpy(root_path, dir->name);
        strcat(root_path, "/");
        return root_path;
    } else {
        // Recursive case: get parent path
        char *parent_path = pwdr(dir->parent);
        size_t len = strlen(parent_path) + strlen(dir->name) + 2;
        char *full_path = malloc(len);
        strcpy(full_path, parent_path);
        strcat(full_path, dir->name);
        strcat(full_path, "/");
        free(parent_path); // free previous allocation
        return full_path;
    }
}

// Public function
char* pwd(Directory *dir) {
    return pwdr(dir);
}

#endif
