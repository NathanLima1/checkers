#include "header.h"
#include "dfs.h"

void reset_visited(node_list *graph, int len_graph) {
    for (int i = 0; i < len_graph; i++) {
        for (int j = 0; j < graph[i].size; j++) {
            graph[i].e[j].visited = 0;
        }
    }
}

int DFS(node_list *g, int current, int start_id, int depth) {
    node_list *curr = &g[current];
    int max_depth = depth;

    if (current == start_id && depth == 0) {
        curr->root.type = 0;
    }

    for (int i = 0; i < curr->size; i++) {
        int neighbor_id = curr->e[i].id;
        node_list *neighbor = &g[neighbor_id];

        // Se o atual não foi visitado e o tipo do vizinho é uma casa vazia
        if (curr->e[i].visited == 0 && neighbor->root.type == 0) {
            curr->e[i].visited = 1;

            int neighbor_current_id = curr->e[i].pos;
            neighbor->e[neighbor_current_id].visited = 1;

            // Chamada recursiva para descobrir a profundidade
            int new_depth = DFS(g, neighbor_id, start_id, depth + 1);
            if (new_depth > max_depth) max_depth = new_depth;

            curr->e[i].visited = 0;
            neighbor->e[neighbor_current_id].visited = 0;
        }
    }

    return max_depth;
}

int get_depth(node_list *graph, int len_graph){
    int max_depth = 0;

    for (int i = 0; i < len_graph; i++) {
        // Se for uma peça do usuário, calcula o número de capturas
        if (graph[i].root.type == 1) {
            // Reseta os visitados antes de começar uma nova dfs
            reset_visited(graph, len_graph);
            int n = graph[i].root.id;
            int depth = DFS(graph, n, n, 0);
            if (depth > max_depth) max_depth = depth;
        }
    }

    return max_depth;
}


node* get_neighbors(node* squares, int pos, int m, int n){
    int x = pos/(n/2);
    int is_even_width = !(m%2);
    // Quando a linha não começa com uma casa
    int shift_pos = !(x%2) && is_even_width;
    int shift_pos_for_sub = (x%2) && is_even_width;
    int half_width = m/2;

    node* neighbors = (node*)malloc(4*sizeof(node));

    neighbors[0] = squares[pos + half_width - shift_pos];
    neighbors[1] = squares[pos - half_width + shift_pos_for_sub];
    neighbors[2] = squares[pos + half_width - shift_pos + 1];
    neighbors[3] = squares[pos - half_width + shift_pos_for_sub - 1];

    return neighbors;

}