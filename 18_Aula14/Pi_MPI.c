#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <mpi.h>

#define PI 3.14159265358979323846

double f(double x) {
    return 4.0 / (1.0 + x * x);
}

int main(int argc, char** argv) {
    int rank, size;
    double a = 0.0, b = 1.0, h, x, sum = 0.0, local_sum = 0.0;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    h = (b - a) / (double) size;
    for (int i = rank; i < size; i += size) {
        x = a + i * h + h / 2.0;
        local_sum += f(x) * h;
    }

    MPI_Reduce(&local_sum, &sum, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        printf("O valor de pi é aproximadamente %.16f\n", sum);
        printf("O valor exato de pi é %.16f\n", PI);
    }

    MPI_Finalize();
    return 0;
}
