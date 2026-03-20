#include <time.h>
#ifndef STRUCTURES_H
#define STRUCTURES_H

typedef struct Directory {
    char name[50];
    char permissions[10];
    int hard_links;
    char owner[50];
    char group[50];
    int size;
    time_t last_modified;
    struct Directory *parent;
    struct Directory *children[10];
    int child_count;
} Directory;

#endif
