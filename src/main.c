#include "header.h"
#include "utils.h"
#include "dfs.h"
#include <unistd.h>
#include "getopt.h"


int main(int argc, char *argv[]){
    FILE *fp = stdin;
    FILE *fp_out = stdin;

    // Começa a medir o tempo real
    struct timeval start_time, end_time;
    gettimeofday(&start_time, NULL);

    int option = 1;

    char *input_file = "entrada.txt";
    char *output_file = "saida.txt";
    int opt;

    while ((opt = getopt(argc, argv, "i:o:f:")) > 0 ) {
        switch (opt) {
            case 'i':
                input_file = optarg;
                break;
            case 'o':
                output_file = optarg;
                break;
            case 'f':
                option = atoi(optarg);
                if(option == 2){
                    printf("Otimizado escolhido.\n");
                }else{
                    printf("Força bruta selecionada.\n");
                }
                break;
            default:
                printf("Entrada inválida, use -i:-o:-f\n");
                return 0;
        }
    }

    fp = fopen(input_file, "r");
    if (fp == NULL) {
        perror("Erro ao abrir o arquivo");
        return 1;
    }

    fp_out = fopen(output_file, "w");

    int n, m;

    // Começa a medir o tempo de usuário
    struct rusage usage_start, usage_end;
    getrusage(RUSAGE_SELF, &usage_start);

    // Optimized
    if(option == 2){
        while(1){
            if(fscanf(fp, "%d %d", &n, &m) != 2){
                printf("Erro ao ler o arquivo\n");
                exit(1);
            }
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
            fprintf(fp_out, "%d\n", depth);

            free(data);
            free(squares);
            free(graph);
        }
    }else{
        while(1){
            if(fscanf(fp, "%d %d", &n, &m) != 2){
                printf("Erro ao ler o arquivo\n");
                exit(1);
            }
            if(n == 0 && m == 0) break;

            int total = (m * n + 1) / 2;
            int *data = malloc(total * sizeof(int));

            read_data(fp, data, total);

            int** board = (int**)malloc(n*sizeof(int*));
            for(int i = 0; i < n; i++){
                board[i] = (int*)malloc(m*sizeof(int));
            }
            // preenchendo com 3 para não conter lixo de memoria
            for(int i = 0; i < n; i++){
                for(int j = 0; j < m; j++){
                    board[i][j] = 3;
                }
            }

            int index = 0;
            for(int i = 0; i < n; i++){
                for(int j = (i%2); j < m; j+= 2){
                    board[i][j] = data[index++];
                }
            }

            int max_res = 0;
            for(int i = 0; i < n; i++){
                for(int j = 0; j < m; j++){
                    if(board[i][j] == 1){
                        int res = all_captures(i, j, board, 0, n, m);
                        if(res > max_res){
                            max_res = res;
                        }
                    }
                }
            }

            printf("%d\n", max_res);
            fprintf(fp_out, "%d\n", max_res);


            for(int i = 0; i<n;i++){
                free(board[i]);
            }
            free(board);
        }
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
    fclose(fp_out);
    
    return 0;
}