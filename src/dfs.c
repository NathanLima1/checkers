#include "header.h"
#include "dfs.h"

int direction_x[4] = {-2, -2, 2, 2};
int direction_y[4] = {-2, 2, -2, 2};

void reset_visited(node_list *graph, int len_graph, int n) {
    for (int i = 0; i < len_graph; i++) {
        for (int j = 0; j < graph[i].size; j++) {
            graph[i].e[j].visited = 0;

            if (j != n && graph[i].e[j].type == 1) {
                graph[i].e[j].visited = 1;
            }
        }
    }
}

int isValid(int x, int y, int n, int m){
    return x >= 0 && x < n && y >= 0 && y < m;
}

int all_captures(int x, int y, int **board, int current_cap, int n, int m){
    int found = 0;
    int max_res = current_cap;
    for(int i = 0; i < 4; i++){
        int final_x = x + direction_x[i];
        int final_y = y + direction_y[i];
        int enemy_x = x + direction_x[i]/2;
        int enemy_y = y + direction_y[i]/2;

        if(isValid(final_x, final_y, n, m) && isValid(enemy_x, enemy_y, n, m) && 
           board[enemy_x][enemy_y] == 2 && board[final_x][final_y] == 0){
            
            board[x][y] = 0;
            board[enemy_x][enemy_y] = 0;
            board[final_x][final_y] = 1;

            found = 1;
            int res = all_captures(final_x, final_y, board, current_cap + 1, n, m);
            if(res > max_res) max_res = res;

            board[x][y] = 1;
            board[enemy_x][enemy_y] = 2;
            board[final_x][final_y] = 0;
        }
    }

    if(!found) return current_cap;
    return max_res;
}

int backtracking_dfs(node_list *g, int current) {
    node_list *curr = &g[current];
    int max_depth = 0;

    for (int i = 0; i < curr->size; i++) {
        int neighbor_id = curr->e[i].id;
        node_list *neighbor = &g[neighbor_id];

        // Se o atual não foi visitado e o tipo do vizinho é uma casa vazia
        if (curr->e[i].visited == 0) {
            curr->e[i].visited = 1;

            int neighbor_current_id = curr->e[i].pos;
            neighbor->e[neighbor_current_id].visited = 1;

            // Chamada recursiva para descobrir a profundidade
            int new_depth = backtracking_dfs(g, neighbor_id) + 1;
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
            int n = graph[i].root.id;
            reset_visited(graph, len_graph, n); // Reseta os visitados e marca as casas aliadas como visitadas logo em seguida
            int depth = backtracking_dfs(graph, n);
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