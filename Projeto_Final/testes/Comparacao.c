#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <omp.h>

#define N 1000

void multiply_matrices_seq(double *A, double *B, double *C) {
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      double sum = 0.0;
      for (int k = 0; k < N; k++) {
        sum += A[i*N+k] * B[k*N+j];
      }
      C[i*N+j] = sum;
    }
  }
}

void multiply_matrices_par(double *A, double *B, double *C) {
  #pragma omp parallel for
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      double sum = 0.0;
      for (int k = 0; k < N; k++) {
        sum += A[i*N+k] * B[k*N+j];
      }
      C[i*N+j] = sum;
    }
  }
}

void multiply_matrices_mpi(double *A, double *B, double *C, int local_n) {
  int rank, size;
  double *local_A, *local_C;

  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);

  // allocate memory for local_A and local_C matrices
  local_A = (double*)malloc(local_n*N*sizeof(double));
  local_C = (double*)malloc(local_n*N*sizeof(double));

  // scatter matrix A to all processes
  MPI_Scatter(A, local_n*N, MPI_DOUBLE, local_A, local_n*N, MPI_DOUBLE, 0, MPI_COMM_WORLD);
  // broadcast matrix B to all processes
  MPI_Bcast(B, N*N, MPI_DOUBLE, 0, MPI_COMM_WORLD);

  // perform matrix multiplication on local_A and B and store result in local_C
  multiply_matrices_par(local_A, B, local_C);

  // gather local_C matrices from all processes to matrix C on process 0
  MPI_Gather(local_C, local_n*N, MPI_DOUBLE, C, local_n*N, MPI_DOUBLE, 0, MPI_COMM_WORLD);

  free(local_A);
  free(local_C);
}

int main(int argc, char *argv[]) {
  int rank, size, local_n;
  double *A, *B, *C_seq, *C_par, *C_mpi;
  double start, end, seq_time, par_time, mpi_time, seq_speedup, par_speedup, mpi_speedup, seq_efficiency, par_efficiency, mpi_efficiency;

  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);

  // set local_n as the number of rows of matrix A to be processed by each process
  local_n = N / size;

  // allocate memory for A, B, and C matrices
  if (rank == 0) {
    A = (double*)malloc(N*N*sizeof(double));
    B = (double*)malloc(N*N*sizeof(double));
    C_seq = (double*)malloc(N*N*sizeof(double));
    C_par = (double*)malloc(N*N*sizeof(double));
    C_mpi = (double*)malloc(N*N*sizeof(double));
    // initialize A and B matrices
    for (int i = 0; i < N; i++)
