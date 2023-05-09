#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

#define VEC_SIZE 1000

int main(int argc, char** argv) {

  int rank, size;
  int vector[VEC_SIZE];
  int partial_sum = 0, partial_double_sum = 0, total_sum, total_double_sum;

  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);

  if (rank == 0) {
    // Processo 0: gera o vetor aleatório e envia para processos 1 e 2
    srand(0); // Define a semente do gerador de números aleatórios para sempre gerar o mesmo vetor
    for (int i = 0; i < VEC_SIZE; i++) {
      vector[i] = rand() % 10; // Gera um número aleatório entre 0 e 9
    }
    MPI_Bcast(vector, VEC_SIZE, MPI_INT, 0, MPI_COMM_WORLD);
    printf("Vetor aleatório gerado:\n");
    for (int i = 0; i < VEC_SIZE; i++) {
      printf("%d ", vector[i]);
    }
    printf("\n");
  } else {
    // Processos 1 e 2: recebem o vetor enviado pelo processo 0
    MPI_Bcast(vector, VEC_SIZE, MPI_INT, 0, MPI_COMM_WORLD);
  }

  // Cada processo calcula sua soma parcial
  for (int i = rank; i < VEC_SIZE; i += size) {
    partial_sum += vector[i];
    partial_double_sum += vector[i] * 2;
  }

  // Cada processo envia sua soma parcial para o processo 0
  MPI_Reduce(&partial_sum, &total_sum, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
  MPI_Reduce(&partial_double_sum, &total_double_sum, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

  if (rank == 0) {
    // Processo 0: recebe os resultados dos processos 1 e 2 e mostra na tela
    printf("Soma dos elementos do vetor: %d\n", total_sum);
    printf("Soma do dobro dos elementos do vetor: %d\n", total_double_sum);
  }

  MPI_Finalize();

  return 0;
}
