#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

int main (void){

    int x = 5;

    #pragma omp parallel private(x) num_threads(3)
    {
        printf("%d \n" ,x);
    }


    return 0;
}