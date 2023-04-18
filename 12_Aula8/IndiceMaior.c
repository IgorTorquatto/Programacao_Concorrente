#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>

#define MAX 500
#define TAMANHO 500000000  

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
    int *vetor = NULL;
    vetor = gerar_vetor_inteiro(TAMANHO);
    
    int indice;
    double inicio, fim;
    double speedup;
    double tempo_sequencial,tempo_paralelo;

    //Sequencial:
    int maior;
    int i;
    inicio = omp_get_wtime();
    maior= vetor[0];
	
    for(i = 0; i < TAMANHO ; i++ ){
       
        if (vetor[i] > maior){
            maior = vetor[i];
            indice = i ;
        }
        
    }

    fim = omp_get_wtime();
    tempo_sequencial = fim - inicio;

    printf("Sequencial: \n");
    printf("Maior valor: %d \n",maior);
    printf("Índice do maior valor: %d \n",indice);
    printf("Tempo de execução: %.4f \n",tempo_sequencial);

    //Paralelo:
    inicio = 0;
    fim = 0;
    maior = vetor[0];
    indice = 0;

    inicio = omp_get_wtime();

    #pragma omp parallel num_threads(4)
    {
        #pragma omp for 
        for(i = 0; i < TAMANHO ; i++ ){
    
            if (vetor[i] > maior){
                maior = vetor[i];
                indice = i ;
        	}
    }
    }

    fim = omp_get_wtime();
    tempo_paralelo = fim - inicio;

    printf("Paralelo: \n");
    printf("Maior valor: %d \n",maior);
    printf("Índice do maior valor: %d \n",indice);
    printf("Tempo de execução: %.4f \n",tempo_paralelo);
    
    speedup = tempo_sequencial / tempo_paralelo;
    printf("\nSpeedup: %f \n",speedup);
    printf("Eficiência: %f \n", speedup/ 4.0);

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
