#include <stdio.h>

#define N 1000

void multiply_matrices(double A[N][N], double B[N][N], double C[N][N]) {
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

int main() {
  double A[N][N], B[N][N], C[N][N];
  // initialize A and B matrices
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      A[i][j] = i + j;
      B[i][j] = i - j;
    }
  }
  // multiply A and B matrices and store result in C
  multiply_matrices(A, B, C);
  // print result matrix C
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      printf("%f ", C[i][j]);
    }
    printf("\n");
  }
  return 0;
}
