#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define N 1000

//Para rodar isso devemos executar o seguinte comando :    ulimit -s unlimited

void multiply_matrices(double A[N][N], double B[N][N], double C[N][N]) {

  double tempo;
  tempo = omp_get_wtime();

  #pragma omp parallel num_threads(4)

  {
    #pragma omp for 
    for (int i = 0; i < N; i++) {
      for (int j = 0; j < N; j++) {
        double sum = 0.0;
        for (int k = 0; k < N; k++) {
          sum += A[i][k] * B[k][j];
        }
        C[i][j] = sum;
      }
    }

  }
  
  printf("Tempo de execução: %f",tempo);
}

int main() {

  //double A[N][N], B[N][N], C[N][N];
  double (*A)[N] = malloc(sizeof(double[N][N]));
  double (*B)[N] = malloc(sizeof(double[N][N]));
  double (*C)[N] = malloc(sizeof(double[N][N]));

  
  if (A == NULL || B == NULL || C == NULL) {
    printf("Memory allocation failed. Exiting...\n");
    return 1;
  }
 
  // inicilizando as matrizes
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      A[i][j] = i + j;
      B[i][j] = i - j;
    }
  }

  // multiplicação das matrizes A e B e salvando o resultado na matriz C

  multiply_matrices(A,B,C);

  /*impressão 
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      printf("%f ", C[i][j]);
    }
    printf("\n");
  }*/
  
  free(A);
  free(B);
  free(C);

  return 0;
}
