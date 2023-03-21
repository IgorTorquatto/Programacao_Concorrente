#include <stdio.h>
#include <stdlib.h>
#include <omp.h>


int main (){

    int nprocs = omp_get_num_procs();

    #pragma omp parallel num_threads(nprocs)

    {
        printf("Hello \n");
    }

    return 0;
}
