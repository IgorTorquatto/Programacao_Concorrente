#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define N 1000

int main() {

  double A[N][N], B[N][N], C[N][N];
  double tempo,inicio,fim;

  // Inicializando

  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      A[i][j] = i + j;
      B[i][j] = i - j;
    }
  }

  // Multiplicação

  inicio = omp_get_wtime();

  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      double sum = 0.0;
      for (int k = 0; k < N; k++) {
        sum += A[i][k] * B[k][j];
      }
      C[i][j] = sum;
    }
  }

  fim = omp_get_wtime();
  tempo = fim - inicio;

  printf("Tempo: (%.2f) s ",tempo);
  

  /*
  Imprimir o resultado da matriz C
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      printf("%f ", C[i][j]);
    }
    printf("\n");
  }*/

  return 0;
}
