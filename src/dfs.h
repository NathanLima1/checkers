#ifndef DFS_H
#define DFS_H

#include "header.h"
#include "dfs.h"

int get_max_captures(int x, int y, int** board, int n, int m);

int bactracking_dfs(node_list *g, int current, int start_id, int depth);
/*Realiza uma busca em profundidade com bactracking 
tendo como base no grafo passado, 
o nó atual, o id atual e a profundidade*/

void reset_visited(node_list *graph, int len_graph);
/*Reseta o estado de visitado dos edges do grafo, com baso no grafo e seu tamanho*/

int get_depth(node_list* graph, int len_graph);
/*Retorna a profundidade máxima possível, nesse caso o número máximo 
de capturas que é possível realizar*/

node* get_neighbors(node* squares, int pos, int m, int n);
/*Retorna um vetor com os vizinhos da peça que foi passada como parâmetro, 
nesse caso pos*/

#endif