#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>

/*
Escreva um programa em C, com OpenMP, que dado um número maior do que 1.000.000.000 (um bilhão), calcular a soma de todos os seus divisores. 
*/

#define TAMANHO 100000000  

int main() {
  	
  	setlocale(LC_ALL,"Portuguese");
  	
    //Sequencial:
    long int soma = 0;
    double tempo_paralelo,tempo_sequencial,fim,inicio,speedup,eficiencia;
    int i;

    inicio = omp_get_wtime();

    for(i = 1 ; i <= TAMANHO ; i ++){
        if (TAMANHO % i == 0){
            soma += i;
        }
    }

    fim = omp_get_wtime();
    tempo_sequencial = fim - inicio;

    printf("Sequencial: \n");
    printf("Soma : %ld \n ", soma);
    printf("Tempo de execução sequencial: %f \n",tempo_sequencial);

    //Paralelo:
    inicio = 0.0;
    fim = 0.0;
    soma = 0;
    i=0;

    inicio = omp_get_wtime();

    #pragma omp parallel num_threads(3)
    {
        #pragma omp for reduction (+:soma)
        for(i = 1 ; i <= TAMANHO ; i ++){
        if (TAMANHO % i == 0){
            soma += i;
        }
    }
    }
    
    fim = omp_get_wtime();

    tempo_paralelo = fim - inicio;

    printf("Paralelo: \n");
    printf("Soma : %ld \n ", soma);
    printf("Tempo de execução paralelo: %f \n",tempo_paralelo);

     return 0;
}
