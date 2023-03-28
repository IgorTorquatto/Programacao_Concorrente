#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 10000000

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

    double comeco,fim;
    int i;
    float n;
    printf("Digite um número n:");
    scanf("%f",&n);

    //Sequencial;

    comeco = omp_get_wtime();

    for(int i = 0; i < MAX;i++){
        if(vetor[i] == n){
            printf("Valor n achado \n");
        }
    }

    fim = omp_get_wtime();

    double tempo_sequencial = fim - comeco;

    printf("Tempo Sequencial: %f \n",tempo_sequencial);

    //Paralelo:

    comeco = omp_get_wtime();
	#pragma omp parallel num_threads(2)
	{
		#pragma omp for
			for (i=0;i<MAX;i++) {
                if (vetor[i]==n) {
                    printf("Valor n achado\n");
                }
			}
	}
	fim = omp_get_wtime();
	double tempo_paralelo = fim - comeco;
	printf("Execução paralela: %f\n",tempo_paralelo);
	double speedup = tempo_sequencial/tempo_paralelo;
	printf("Speedup: %.4f\n", tempo_sequencial/ tempo_paralelo);
	printf("Eficiência: %.4f\n",speedup/2.0);


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
