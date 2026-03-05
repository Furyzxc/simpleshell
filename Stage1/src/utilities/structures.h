#ifndef STRUCTURES_H
#define STRUCTURES_H

typedef struct Directory {
    char name[50];
    struct Directory *parent;
    struct Directory *children[10];
    int child_count;
} Directory;

#endif
