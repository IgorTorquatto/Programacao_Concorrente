#include <mpi.h>
#include <stdio.h>

int main(int argc, char** argv) {
   //Iniciando MPI
   MPI_Init(NULL, NULL);
   int nprocs;  // é preenchido pela linha de comando no mpiexec -n 
   MPI_Comm_size(MPI_COMM_WORLD, &nprocs);
   int rank;
   MPI_Comm_rank(MPI_COMM_WORLD, &rank);
   //Comando(s) a serem realizados por cada processo
   printf("Hello world do processador rank #%d/%d\n",meu_rank, ncpus);
   // Finalizando MPI
   MPI_Finalize();
   return 0;
}

//Cada processo é colocado para ser executado por um processador;
// Trabalhar com threads -> MP
// Trabalhar com processos -> MPI