#ifndef DFS_H
#define DFS_H

#include "header.h"

int DFS(node_list* g, int current, int start_id, int depth);
int get_depth(node_list* graph, int len_graph);
node* get_neighbors(node* squares, int pos, int m, int n);

#endif