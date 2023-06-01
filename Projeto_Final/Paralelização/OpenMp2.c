#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

#define N 3000

int main() {
  double (*A)[N] = malloc(sizeof(double[N][N]));
  double (*B)[N] = malloc(sizeof(double[N][N]));
  double (*C)[N] = malloc(sizeof(double[N][N]));
  double tempo;
  signed long i, j, k;

  // Inicialização
  for (i = 0; i < N; i++) {
    for (j = 0; j < N; j++) {
      A[i][j] = i + j;
      B[i][j] = i - j;
    }
  }

  // Multiplicação
  clock_t inicio = clock();

  omp_set_dynamic(0); // Desativa ajuste automático do número de threads
  omp_set_num_threads(omp_get_num_procs()); // Usa o número de processadores disponíveis

  #pragma omp parallel for private(j, k) shared(A, B, C)
  for (i = 0; i < N; i++) {
    for (j = 0; j < N; j++) {
      double sum = 0.0;
      for (k = 0; k < N; k++) {
        sum += A[i][k] * B[k][j];
      }
      C[i][j] = sum;
    }
  }

  clock_t fim = clock();
  tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;

  printf("Tempo: %.2f s\n", tempo);

  free(A);
  free(B);
  free(C);

  return 0;
}
