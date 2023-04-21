#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <locale.h>

#define MAX 100
#define TAMANHO 500000000 //100000000

double *gerar_vetor(int n);
int *gerar_vetor_inteiro(int n);
void mostrar_vetor_inteiro(int *v,int tamanho);
void mostrar_vetor(double *v,int tamanho);

int main() {
    /*
    INICIO
    */
    
    setlocale(LC_ALL,"Portuguese");
    time_t t;
    srand(time(NULL));
    double *vetor = NULL;
    vetor = gerar_vetor(TAMANHO);
    int i;
    double tempo_sequencial,tempo_paralelo,speedup,inicio,fim;
    
    //Sequencial:
    
    inicio = omp_get_wtime();
    
    int somatorio = 0;
    
    for (i = 0; i < TAMANHO; i++) {
        somatorio += vetor[i];
    }

    double media = somatorio / (double) TAMANHO;

    double variacoes = 0;
    for (i = 0; i < TAMANHO; i++) {
        float v = vetor[i] - media;
        variacoes += v * v;
    }

    double sigma = sqrt(variacoes / TAMANHO);
    
    fim = omp_get_wtime();
    tempo_sequencial = fim - inicio;
    
    printf("Sequencial: \n");
    printf("Desvio Padrão: %.2f\n", sigma);
    printf("Tempo Sequencial: %.4f\n \n",tempo_sequencial);
    
    
    //Paralelo:
    
    inicio = 0;
    fim = 0;
    media = 0;
    somatorio = 0;
    variacoes = 0;
    sigma = 0;
    
    inicio = omp_get_wtime();
    
    #pragma omp parallel num_threads(4)
    {
    	#pragma omp for reduction(+:somatorio)
    	for (i = 0; i < TAMANHO; i++) {
	        somatorio += vetor[i];
	    	}
	    
		media = somatorio / (double) TAMANHO;
		 	
		#pragma omp for reduction(+:variacoes)
		for (i = 0; i < TAMANHO; i++) {
	        float v = vetor[i] - media;
	        variacoes += v * v;
	   		}
		
		sigma = sqrt(variacoes / TAMANHO);
    	
	}
	
	fim = omp_get_wtime();
    tempo_paralelo = fim - inicio;
    
    printf("Paralelo: \n");
    printf("Desvio Padrão: %.2f\n", sigma);
    printf("Tempo Paralelo: %.4f\n \n",tempo_paralelo);
    
    speedup = tempo_sequencial/tempo_paralelo;
    printf("Speedup: %.4f \n",speedup);
    printf("Eficiência: %.4f\n",speedup / 4);
    
    /*
    FIM
    */
    return 0;
}

double *gerar_vetor(int n) {
    double *vetor;
    int i;
    vetor = (double *)malloc(sizeof(double) * n);
    for (i=0;i<n;i++) {
        double num = (rand() / (float)RAND_MAX);
        vetor[i] = num;
    }
    return vetor;
}

int *gerar_vetor_inteiro(int n) {
    int *vetor;
    int i;
    vetor = (int *)malloc(sizeof(int) * n);
    for (i=0;i<n;i++) {
        int num = (rand() % MAX);
        vetor[i] = num;
    }
    return vetor;
}

void mostrar_vetor(double *v,int tamanho) {
    int i;
    for (i=0;i<tamanho;i++) {
        printf("[%.5f]",v[i]);
    }
    printf("\n");
}

void mostrar_vetor_inteiro(int *v,int tamanho) {
    int i;
    for (i=0;i<tamanho;i++) {
        printf("[%d]",v[i]);
    }
    printf("\n");
}
