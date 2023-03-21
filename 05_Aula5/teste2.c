#include <stdio.h>
#include <omp.h>

int main () {
	int i;
	#pragma omp parallel num_threads(3)
	{
	    //Cria 4 Thread e cada uma executa esse mesmo código:
		#pragma omp for
		//Divide as iterações nas threads
			for (i=0; i<=20; i++) {
				printf("Thread %d executa iteracao %d do for\n",omp_get_thread_num(),i);
			}
	}

	return 0;
}
