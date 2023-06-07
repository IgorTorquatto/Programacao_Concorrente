#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"
#include <time.h>

#define N 3000

int main(int argc, char** argv) {
  int rank, size;
  double (*A)[N] = malloc(sizeof(double[N][N]));
  double (*B)[N] = malloc(sizeof(double[N][N]));
  double (*C)[N] = malloc(sizeof(double[N][N]));
  double tempo;
  signed long i, j, k;

  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);

  // Dividindo o trabalho entre os processos
  signed long chunk_size = N / size;
  signed long chunk_start = rank * chunk_size;
  signed long chunk_end = (rank == size - 1) ? N : chunk_start + chunk_size;

  // Inicialização
  for (i = chunk_start; i < chunk_end; i++) {
    for (j = 0; j < N; j++) {
      A[i][j] = i + j;
      B[i][j] = i - j;
    }
  }

  // Sincronização antes da multiplicação
  MPI_Barrier(MPI_COMM_WORLD);

  // Multiplicação
  clock_t inicio = clock();

  for (i = chunk_start; i < chunk_end; i++) {
    for (j = 0; j < N; j++) {
      double sum = 0.0;
      for (k = 0; k < N; k++) {
        sum += A[i][k] * B[k][j];
      }
      C[i][j] = sum;
    }
  }

  // Sincronização após a multiplicação
  MPI_Barrier(MPI_COMM_WORLD);

  clock_t fim = clock();
  tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;

  // Redução dos tempos para o processo 0
  double total_tempo;
  MPI_Reduce(&tempo, &total_tempo, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

  if (rank == 0) {
    printf("Tempo total: %.2f s\n", total_tempo);
  }

  MPI_Finalize();

  free(A);
  free(B);
  free(C);

  return 0;
}