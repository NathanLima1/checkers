#include "header.h"
#include "utils.h"

int main(){
    int n, m;

    scanf("%d %d", &n, &m);

    int total = m * n / 2;
    int *data = malloc(total * sizeof(int));

    read_data(&data, total);

    node* squares = malloc(total*sizeof(node));
    int id_len = create_vector(&squares, total, &data);

    node_list *graph = malloc(id_len*sizeof(node_list));
    init_graph(&graph, total, &squares);

    construct_graph(n, m, &squares, &graph);
}