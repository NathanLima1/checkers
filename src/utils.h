#ifndef UTILS_H
#define UTILS_H

#include "header.h"

void read_data(int* data, int total);
int create_vector(node* squares, int total, int *data);
void init_graph(node_list* g, int total, node *squares);
int is_border(int x, int y, int n, int m);
void construct_graph(int n, int m, node* squares, node_list* g);

#endif