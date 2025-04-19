#include "header.h"
#include "utils.h"
#include "dfs.h"

int main(int argc, char *argv[]){
    FILE *fp = stdin;

    if (argc == 3 && strcmp(argv[1], "-i") == 0) {
        fp = fopen(argv[2], "r");
        if (fp == NULL) {
            perror("Erro ao abrir o arquivo");
            return 1;
        }
    }

    int n, m;

    while(1){
        fscanf(fp, "%d %d", &n, &m);
        if(n == 0 && m == 0) break;

        int total = (m * n + 1) / 2;
        int *data = malloc(total * sizeof(int));

        read_data(fp, data, total);

        node* squares = malloc(total*sizeof(node));
        int id_len = create_vector(squares, total, data);

        node_list *graph = malloc(id_len*sizeof(node_list));
        init_graph(graph, total, squares);

        construct_graph(n, m, squares, graph);

        int depth = get_depth(graph, id_len);
        printf("%d\n", depth);

        free(data);
        free(squares);
        free(graph);
    }

    fclose(fp);
    
    return 0;
}