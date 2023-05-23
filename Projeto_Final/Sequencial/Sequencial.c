#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 1000

int main() {
  
  double (*A)[N] = (double (*)[N])malloc(sizeof(double[N][N]));
  double (*B)[N] = (double (*)[N])malloc(sizeof(double[N][N]));
  double (*C)[N] = (double (*)[N])malloc(sizeof(double[N][N]));
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
