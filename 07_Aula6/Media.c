#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>

#define MAX 500000000

float *gerar_vetor(int n);

void mostrar_vetor(float *v,int tamanho);

int main() {
    
    setlocale(LC_ALL,"Portuguese");
    time_t t;
    srand(time(NULL));
    float *vetor = NULL;
    vetor = gerar_vetor(MAX);

	double inicio,fim;
	float tempo_sequencial;
	float tempo_paralelo;
	float soma;
	float media;
	soma = 0;
	
	//Sequencial:
	inicio = omp_get_wtime();
	
	for(int i = 0 ; i < MAX; i++){
		soma+= vetor[i];
	}
	
	media = soma / MAX;
	
	fim = omp_get_wtime();
	tempo_sequencial = fim - inicio ;
	
	printf("Média dos valores (Sequencial): %f \n",media);
	printf("Tempo de execução Sequencial: %.4f \n",tempo_sequencial);
	
	inicio = 0;
	fim = 0;
	soma = 0.0;
	media = 0.0;
	
	//Paralelo:
	
	inicio = omp_get_wtime();
	#pragma omp parallel num_threads(3)
	{
		#pragma omp for
		
			for(int i = 0 ; i < MAX; i++){
				soma+= vetor[i];
			}
	
	}
	
	media = soma / MAX ;
	
	fim = omp_get_wtime();
	tempo_paralelo = fim - inicio;
	
	printf("Média dos valores(Paralelo): %f \n",media);
	printf("Tempo de execução Paralelo: %.4f \n",tempo_paralelo);
	
	//Speedup:
	float speedup = tempo_sequencial / tempo_paralelo;
	printf("Speedup: %f \n",speedup);
	
	//Eficiência:
	float eficiencia = speedup / 3.0;
	printf("Eficiência: %f \n",eficiencia);
	
    return 0;
}

float *gerar_vetor(int n) {
    float *vetor;
    int i;
    vetor = (float *)malloc(sizeof(float) * n);
    for (i=0;i<n;i++) {
        float num = (rand() / (float)RAND_MAX);
        vetor[i] = num;
    }
    return vetor;
}

void mostrar_vetor(float *v,int tamanho) {
    int i;
    for (i=0;i<tamanho;i++) {
        printf("[%.5f]",v[i]);
    }
    printf("\n");
}