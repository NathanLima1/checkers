#ifndef HEADER_H
#define HEADER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <stdbool.h>

typedef struct {
    int type;
    int id;
    bool visited;
    int pos;
} node;

typedef struct {
    node e[4];
    int dists[4];
    node root;
    int size;
} node_list;


#endif