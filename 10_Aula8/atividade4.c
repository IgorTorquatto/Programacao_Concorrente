#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//al : Cicero Igor

/*
Escreva um programa serial e paralelo em C, com OpenMP, que dado um vetor de inteiros e um valor x, encontrar quantas vezes x ocorre no vetor. Calcular as métricas de desempenho. 
*/

#define MAX 100
#define TAMANHO 100000000    //1000

double *gerar_vetor(int n);
int *gerar_vetor_inteiro(int n);
void mostrar_vetor_inteiro(int *v,int tamanho);
void mostrar_vetor(double *v,int tamanho);

int main() {
    /*
    INICIO
    */
    time_t t;
    srand(time(NULL));
    int *vetor = NULL;
    vetor = gerar_vetor_inteiro(TAMANHO);


    //Sequencial:
    int entrada;
    int num_vezes = 0;
    double tempo_sequencial,inicio,fim;

    inicio= omp_get_wtime();
    printf("Digite um número inteiro: \n");
    scanf("%d",&entrada);

    for(int i = 0; i < TAMANHO; i++){
        if(entrada == vetor[i]){
            //printf("Valor encontrado no vetor. \n");
            num_vezes++;
        }
    }

    fim = omp_get_wtime();
    tempo_sequencial = fim - inicio;

    printf("O valor %d foi encontrado %d vezes no vetor \n",entrada,num_vezes);
    printf("Tempo de execução sequencial: %.4f \n",tempo_sequencial);

    //Paralelo:

    printf("Paralelo: \n");
    double tempo_paralelo;
    num_vezes = 0;
    inicio = 0.0;
    fim = 0.0;
    num_vezes = 0;

    inicio = omp_get_wtime();

    #pragma omp parallel num_threads(4)
    {
        #pragma omp for
        for(int i = 0 ; i < TAMANHO ; i++){
            //printf("Valor encontrado no vetor. \n");
            num_vezes++;
        }
    }

    fim = omp_get_wtime();
    tempo_paralelo = fim - inicio;
    double speedup = tempo_sequencial / tempo_paralelo;
    double eficiencia = speedup / 4.0;

    printf("O valor %d foi encontrado %d vezes no vetor \n",entrada,num_vezes);
    printf("Tempo de execução paralelo: %.4f \n",tempo_paralelo);

    printf("Speedup: %.4f \n",speedup);
    printf("Eficiência: %.4f \n",eficiencia);

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