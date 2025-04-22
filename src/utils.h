#ifndef UTILS_H
#define UTILS_H

#include "header.h"

void read_data(FILE *fp, int* data, int total);
/*Lê a entrada correspondente as casas, ele recebe o arquivo 
que vai ser lido a entrada, o vetor que vai ser armazenado e o número
de entradas que vão ser lidas*/

int create_vector(node* squares, int total, int *data);
/*Cria um vetor de nodes de squares e retorna a quantidade de ids, ele recebe o vetor 
onde vai ser armazenado, a quantidade de items e o vetor de data, onde estão os dados que
foram lidos anteriormente para armazenar como nó em squares*/

void init_graph(node_list* g, int total, node *squares);
/*Inicia o grafo, armazenando os squares que não são do adversário no grafo, que é 
uma lista da estrutura node*/

int is_border(int x, int y, int n, int m);
/*Checa se o elemento está na borda ou não, e retorna*/

void construct_graph(int n, int m, node* squares, node_list* g);
/*Constroi um grafo com base nos vizinhos e os nós antes lidos*/

#endif