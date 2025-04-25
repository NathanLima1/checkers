#ifndef DFS_H
#define DFS_H

#include "header.h"
#include "dfs.h"

int all_captures(int x, int y, int **board, int current_cap, int n, int m);
/*Testa todas as possibilidades de movimento*/

int backtracking_dfs(node_list *g, int current);
/*Realiza uma busca em profundidade com bactracking 
tendo como base o grafo e o nó atual*/

void reset_visited(node_list *graph, int len_graph, int n);
/*Reseta o estado de visitado dos edges do grafo e marca casas aliadas diferentes de n como visitadas
com base no grafo, seu tamanho e a casa sendo analisada*/

int get_depth(node_list* graph, int len_graph);
/*Retorna a profundidade máxima possível, nesse caso o número máximo 
de capturas que é possível realizar*/

node* get_neighbors(node* squares, int pos, int m, int n, int x);
/*Retorna um vetor com os vizinhos da peça que foi passada como parâmetro, 
nesse caso pos*/

#endif