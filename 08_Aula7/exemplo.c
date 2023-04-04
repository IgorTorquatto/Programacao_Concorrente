#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

int main (void){

    int x = 5;

    #pragma omp parallel private(x) num_threads(3)
<<<<<<< HEAD

=======
>>>>>>> 8a0ce5eadb09ed5a314241f6f8ff1b70fb8bde3f
    {
        printf("%d \n" ,x);
    }

<<<<<<< HEAD
    printf("%d \n",x);
=======

>>>>>>> 8a0ce5eadb09ed5a314241f6f8ff1b70fb8bde3f
    return 0;
}