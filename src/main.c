#include "header.h"
#include "utils.h"
#include "dfs.h"

int main(int argc, char *argv[]){
    FILE *fp = stdin;

    // Começa a medir o tempo real
    struct timeval start_time, end_time;
    gettimeofday(&start_time, NULL);

    if (argc == 3 && strcmp(argv[1], "-i") == 0) {
        fp = fopen(argv[2], "r");
        if (fp == NULL) {
            perror("Erro ao abrir o arquivo");
            return 1;
        }
    }

    int n, m;

    // Começa a medir o tempo de usuário
    struct rusage usage_start, usage_end;
    getrusage(RUSAGE_SELF, &usage_start);

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

    // Termina medição
    gettimeofday(&end_time, NULL);
    getrusage(RUSAGE_SELF, &usage_end);

    // Calculando o tempo real (tempo total de execução)
    long seconds = end_time.tv_sec - start_time.tv_sec;
    long microseconds = end_time.tv_usec - start_time.tv_usec;
    if (microseconds < 0) {
        seconds--;
        microseconds += 1000000;
    }

    // Calculando tempo de usuário e sistema
    long user_time_sec = usage_end.ru_utime.tv_sec - usage_start.ru_utime.tv_sec;
    long user_time_usec = usage_end.ru_utime.tv_usec - usage_start.ru_utime.tv_usec;

    long sys_time_sec = usage_end.ru_stime.tv_sec - usage_start.ru_stime.tv_sec;
    long sys_time_usec = usage_end.ru_stime.tv_usec - usage_start.ru_stime.tv_usec;

    if (user_time_usec < 0) {
        user_time_sec--;
        user_time_usec += 1000000;
    }

    if (sys_time_usec < 0) {
        sys_time_sec--;
        sys_time_usec += 1000000;
    }

    printf("Tempo Real: %ld.%06ld segundos\n", seconds, microseconds);
    printf("Tempo de Usuário: %ld.%06ld segundos\n", user_time_sec, user_time_usec);
    printf("Tempo de Sistema: %ld.%06ld segundos\n", sys_time_sec, sys_time_usec);


    fclose(fp);
    
    return 0;
}