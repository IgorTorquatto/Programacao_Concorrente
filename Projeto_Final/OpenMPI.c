#include <stdio.h>
#include <mpi.h>

#define N 1000

void multiply_matrices(double *A, double *B, double *C, int local_n, int n) {
  for (int i = 0; i < local_n; i++) {
    for (int j = 0; j < n; j++) {
      double sum = 0.0;
      for (int k = 0; k < n; k++) {
        sum += A[i*n+k] * B[k*n+j];
      }
      C[i*n+j] = sum;
    }
  }
}

int main(int argc, char *argv[]) {
  int rank, size, local_n;
  double *A, *B, *C, *local_A, *local_C;

  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);

  // set local_n as the number of rows of matrix A to be processed by each process
  local_n = N / size;

  // allocate memory for A, B, and C matrices
  if (rank == 0) {
    A = (double*)malloc(N*N*sizeof(double));
    B = (double*)malloc(N*N*sizeof(double));
    C = (double*)malloc(N*N*sizeof(double));
    // initialize A and B matrices
    for (int i = 0; i < N; i++) {
      for (int j = 0; j < N; j++) {
        A[i*N+j] = i + j;
        B[i*N+j] = i - j;
      }
    }
  }

  // allocate memory for local_A and local_C matrices
  local_A = (double*)malloc(local_n*N*sizeof(double));
  local_C = (double*)malloc(local_n*N*sizeof(double));

  // scatter matrix A to all processes
  MPI_Scatter(A, local_n*N, MPI_DOUBLE, local_A, local_n*N, MPI_DOUBLE, 0, MPI_COMM_WORLD);
  // broadcast matrix B to all processes
  MPI_Bcast(B, N*N, MPI_DOUBLE, 0, MPI_COMM_WORLD);

  // perform matrix multiplication on local_A and B and store result in local_C
  multiply_matrices(local_A, B, local_C, local_n, N);

  // gather local_C matrices from all processes to matrix C on process 0
  MPI_Gather(local_C, local_n*N, MPI_DOUBLE, C, local_n*N, MPI_DOUBLE, 0, MPI_COMM_WORLD);

  // print result matrix C on process 0
  if (rank == 0) {
    for (int i = 0; i < N; i++) {
      for (int j = 0; j < N; j++) {
        printf("%f ", C[i*N+j]);
      }
      printf("\n");
    }
    free(A);
    free(B);
    free(C);
  }

  free(local_A);
  free(local_C);

  MPI_Finalize();

  return 0;
}
