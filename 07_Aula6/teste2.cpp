#include <stdio.h>
#include <omp.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>

#define num_steps 100000000

int main() {

	setlocale(LC_ALL,"Portuguese");
    double step;
    double x, pi, soma;
    soma = 0.0;

   	//Sequencial:
   	
    double inicio = omp_get_wtime();
    step = 1.0/(double) num_steps;
    
    for (int i =0;i< num_steps; i++){
        x = (i + 0.5) * step; 
        soma += 4.0 / (1.0 + x*x); 
    }
    
    pi = step * soma;
    
    double fim = omp_get_wtime();
    double tempo_sequencial = fim-inicio;
    
    printf("Valor do pi (Sequencial) %f\n",pi);
    printf("Execucao sequencial(s): %f\n",tempo_sequencial);
   
   //Paralelo:
   
    x = 0;
    pi = 0;
    soma = 0;
    inicio = omp_get_wtime();
    step = 1.0/(double) num_steps;
    
    #pragma omp parallel private(x) num_threads(4)
    {
        #pragma omp for reduction (+:soma)
        for (int i=0;i< num_steps; i++){
            x = (i + 0.5) * step; 
            soma += 4.0 / (1.0 + x*x); 
        }
    }
    pi = step * soma;
    fim = omp_get_wtime();
    
    double tempo_paralelo = fim-inicio;
    double speedup = tempo_sequencial/tempo_paralelo;
    
    printf("Valor do pi (Paralelo) %f\n",pi);
    printf("Tempo execução paralelo: %f\n",tempo_paralelo);
    printf("speedup: %.4f\n", speedup);
	printf("Eficiência: %.4f\n",speedup/4.0);
    return 0;
    
}
