#include "utils.h"

void read_data(FILE* fp, int* data, int total){
    for (int i = 0; i < total; i++) {
        if(fscanf(fp, "%d", &data[i]) != 1){
            printf("Erro ao ler o arquivo");
            exit(1);
        }
    }
}

int create_vector(node* squares, int total, int *data){
    int id = 0;
    
    for(int i = 0; i < total; i++){
        if(data[i] != 2){
            squares[i] = (node){data[i], id, 0, -1};
            id++;
        }else{
            squares[i] = (node){data[i], -1, 0, -1};
        }
    }

    return id;
}

void init_graph(node_list* g, int total, node *squares){
    for(int i = 0; i < total; i++){
        if(squares[i].type == 2) continue;

        int id_ = squares[i].id;
        g[id_].root = squares[i];
        g[id_].size = 0;
    }
}

int is_border(int x, int y, int n, int m){
    if(x > 0 && x < m - 1 && y > 0 && y < n-1){
        return 0;
    }
    return 1;
}

void construct_graph(int n, int m, node* squares, node_list* g){
    int x, y;
    int par = !(m%2);
    for(int i = 0; i < n*m; i+=2){
        y = i/m;
        x = i%m + (y%2*par);

        if(!is_border(x, y, n, m)){
            // Se é uma peça adversária
            if(squares[i/2].type == 2){
                node *neighbors = get_neighbors(squares, i/2 + (!(m%2)*y%2), m, n);

                for(int j = 0; j < 4; j+=2){
                    node n1 = neighbors[j];
                    node n2 = neighbors[j+1];

                    if(n1.type != 2 && n2.type != 2){
                        node_list* gn1 = &g[n1.id];
                        node_list* gn2 = &g[n2.id];
                        gn1->e[gn1->size] = n2;
                        gn2->e[gn2->size] = n1;
                        gn1->e[gn1->size].pos = gn2->size;
                        gn2->e[gn2->size].pos = gn1->size;
                        gn1->size++;
                        gn2->size++;
                    }
                }
                free(neighbors);
            }
        }
    }
}