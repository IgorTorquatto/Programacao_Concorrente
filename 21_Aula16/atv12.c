#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define MAX 100

float *gerar_vetor(int n);

int main() {
    // Iniciando MPI
    MPI_Init(NULL, NULL);
    int nprocs;
    MPI_Comm_size(MPI_COMM_WORLD, &nprocs);
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Status status;

    time_t t;
    srand(time(NULL) * rank);

    int n = MAX; // Tamanho do vetor
    float *vetor;

    /*
    INICIO
    */
    if (rank == 0) {
        vetor = gerar_vetor(n);

        // Enviar o vetor para todos os processos
        for (int dest = 1; dest < nprocs; dest++) {
            MPI_Send(vetor, n, MPI_FLOAT, dest, 0, MPI_COMM_WORLD);
        }
    } else {
        // Receber o vetor no processo atual
        vetor = (float *)malloc(sizeof(float) * n);
        MPI_Recv(vetor, n, MPI_FLOAT, 0, 0, MPI_COMM_WORLD, &status);
    }

    // Calcular a média do vetor localmente em cada processo
    float soma_local = 0.0;
    for (int i = 0; i < n; i++) {
        soma_local += vetor[i];
    }
    float media_local = soma_local / n;

    // Calcular a soma das médias de todos os processos
    float soma_medias = 0.0;
    MPI_Reduce(&media_local, &soma_medias, 1, MPI_FLOAT, MPI_SUM, 0, MPI_COMM_WORLD);

    // Calcular o desvio padrão global
    float desvio_local = 0.0;
    for (int i = 0; i < n; i++) {
        desvio_local += pow(vetor[i] - media_local, 2);
    }
    float desvio_padrao_local = sqrt(desvio_local / n);
    float desvio_padrao_global;

    // Calcular o desvio padrão global somando os desvios locais em todos os processos
    MPI_Reduce(&desvio_padrao_local, &desvio_padrao_global, 1, MPI_FLOAT, MPI_SUM, 0, MPI_COMM_WORLD);

    // Processo 0 imprime o resultado
    if (rank == 0) {
        desvio_padrao_global = sqrt(desvio_padrao_global / n);
        printf("Desvio Padrão: %.6f\n", desvio_padrao_global);
    }

    /*
    FIM
    */

    free(vetor);
    MPI_Finalize();
    return 0;
}

float *gerar_vetor(int n) {
    float *vetor;
    int i;
    vetor = (float *)malloc(sizeof(float) * n);
    for (i = 0; i < n; i++) {
        float num = (rand() / (float)RAND_MAX);
        vetor[i] = num;
    }
    return vetor;
}
