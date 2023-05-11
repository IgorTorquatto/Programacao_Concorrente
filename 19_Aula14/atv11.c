#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

#define N 1000

int main(int argc, char** argv) {
    int rank, size;
    int* vetor = NULL;
    int soma, soma_dobro;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (size != 3) {
        if (rank == 0) {
            printf("Este programa requer exatamente 3 processos.\n");
        }
        MPI_Finalize();
        return 1;
    }

    if (rank == 0) {
        // Gera o vetor aleatório
        vetor = (int*) malloc(N * sizeof(int));
        for (int i = 0; i < N; i++) {
            vetor[i] = rand() % 100;
        }

        // Envia o vetor para os processos 1 e 2
        MPI_Bcast(vetor, N, MPI_INT, 0, MPI_COMM_WORLD);

        // Recebe os resultados dos processos 1 e 2
        MPI_Recv(&soma, 1, MPI_INT, 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        MPI_Recv(&soma_dobro, 1, MPI_INT, 2, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        // Mostra os resultados
        printf("Soma dos elementos do vetor: %d\n", soma);
        printf("Soma do dobro de cada elemento do vetor: %d\n", soma_dobro);

        free(vetor);
    } else if (rank == 1) {
        // Recebe o vetor do processo 0
        vetor = (int*) malloc(N * sizeof(int));
        MPI_Bcast(vetor, N, MPI_INT, 0, MPI_COMM_WORLD);

        // Calcula a soma dos elementos
        soma = 0;
        for (int i = 0; i < N; i++) {
            soma += vetor[i];
        }

        // Envia o resultado para o processo 0
        MPI_Send(&soma, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);

        free(vetor);
    } else if (rank == 2) {
        // Recebe o vetor do processo 0
        vetor = (int*) malloc(N * sizeof(int));
        MPI_Bcast(vetor, N, MPI_INT, 0, MPI_COMM_WORLD);

        // Calcula a soma do dobro de cada elemento
        soma_dobro = 0;
        for (int i = 0; i < N; i++) {
            soma_dobro += 2 * vetor[i];
        }

        // Envia o resultado para o processo 0
        MPI_Send(&soma_dobro, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);

        free(vetor);
    }

    MPI_Finalize();
    return 0;
}
