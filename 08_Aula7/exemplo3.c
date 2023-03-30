#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

int main (void){

    int x = 5;

    #pragma omp parallel num_threads(4)

    {
        x++ ;
        printf("%d \n" ,x);
    }

    printf("%d \n",x);
    return 0;
}