#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main (void){

    #pragma omp parallel num_threads(4)
	{
	    //O mesmo código vai para diferentes cores para serem executados
	    //Em C essa parte do código é realmente paralelo
	    //4 threads executam as mesmas instruções!

		printf("Ola mundo!\n");
	}



    return 0;
}
