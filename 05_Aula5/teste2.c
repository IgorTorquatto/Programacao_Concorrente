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
		//Quando definimos um número de threads e passamos as tarefas , logo em seguida, cada thread será responsável pela execução de uma dessas tarefas (Que nese caso são as iterações do for).
		//Importante destacar que o objetivo é realizar várias tarefas ao mesmo tempo e não necessariamente simultaneamente
	}

	return 0;
}
