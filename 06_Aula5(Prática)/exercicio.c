#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 705032704

float *gerar_vetor(int n);

void mostrar_vetor(float *v,int tamanho);

int main() {
    /*
    INICIO
    */
    time_t t;
    srand(time(NULL));
    float *vetor = NULL;
    vetor = gerar_vetor(MAX);

    //Busca sequencial
    //Começando a resolução:


    float n = 0.3578;
    int i;
    double inicio = omp_get_wtime();

    for (i=0; i< MAX;i++){
        if (vetor[i]==n){
            printf("Achou! \n");
        }

    }
    double fim = omp_get_wtime();
    double t_sequencial= fim - inicio;

    //Tempo:
    printf("Tempo Sequencial: %f",t_sequencial);

    //Busca paralela

    inicio = omp_get_wtime();
	#pragma omp parallel num_threads(3)
	{
		#pragma omp for
			for (i=0;i<MAX;i++) {
                if (vetor[i]==n) {
                    printf("Thread[%d] ACHOU: %ld\n", omp_get_thread_num(),vetor[i]);
                }
			}
	}
	fim = omp_get_wtime();
	double t_paralelo = fim - inicio;

	//Tempo:
	printf("Execucao paralela: %f\n",t_paralelo);

	//Speedup:
	double speedup = t_sequencial/t_paralelo;
	printf("Speedup: %.4f\n", t_sequencial/t_paralelo);
    /*
    FIM
    */
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
