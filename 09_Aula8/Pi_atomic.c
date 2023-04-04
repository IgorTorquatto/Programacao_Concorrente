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


   //Paralelo:
   
    x = 0;
    pi = 0;
    soma = 0;
    double inicio = omp_get_wtime();
    step = 1.0/(double) num_steps;
    
    #pragma omp parallel num_threads(3)
    {
        double sum = 0.0;
        double x;

        #pragma omp for 
        for (int i=0;i< num_steps; i++){
            x = (i + 0.5) * step; 
            soma += 4.0 / (1.0 + x*x); 
        }

        #pragma omp atomic

        pi = pi +(step + soma);
    }


    double fim = omp_get_wtime();
    
    double tempo = fim - inicio;

    printf("Valor de Pi : %f\n",pi);
    printf("Tempo de execução: %.4f\n",tempo);
    return 0;
    
}
