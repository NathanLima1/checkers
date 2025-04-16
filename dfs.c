#include "header.h"
#include "dfs.h"

int DFS(node_list *g, int current, int start_id, int depth) {
    node_list *curr = &g[current];
    int max_depth = depth;

    if (current == start_id && depth == 0) curr->root.type = 0;

    for (int i = 0; i < curr->size; i++) {
        int neighbor_id = curr->e[i].id;
        node_list *neighbor = &g[neighbor_id];
        
        if (curr->e[i].visited == 0 && neighbor->root.type == 0) {
            curr->e[i].visited = 1;
            
            int neighbor_current_id = curr->e[i].pos;
            neighbor->e[neighbor_current_id].visited = 1;

            int new_depth = DFS(g, neighbor_id, start_id, depth + 1);
            if (new_depth > max_depth)
                max_depth = new_depth;

            curr->e[i].visited = 0;
            neighbor->e[neighbor_current_id].visited = 0;
        }
    }
    
    return max_depth;
}

int get_depth(node_list* graph, int len_graph){
    int max_depth = 0;

    for(int i = 0; i < len_graph; i++){
        if(graph[i].root.type == 1){
            printf("%d / %d\n", i, len_graph);

            int n = graph[i].root.id;
            node_list* graph_copy = (node_list*)malloc(sizeof(node_list)*len_graph);
            memcpy(graph_copy, graph, sizeof(node_list)*len_graph);

            int depth = DFS(graph_copy, n, n, 0);
            free(graph_copy);

            if(depth > max_depth) max_depth = depth;

        }
    }
}

node* get_neighbors(node* squares, int pos, int m, int n){
    int x = pos/(n/2);
    int is_even_width = !(m%2);
    // When the row doesn't start with a square
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