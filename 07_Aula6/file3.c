#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 500

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

    //Sequencial:

   
    //prenchendo vetor
    for(int i= 0; i < vetor[MAX] ; i++){
        int aux = rand() %1000000;
        vetor[i] = aux;
    }

    float soma;
    soma= 0;

    for (int i=0; i < vetor[MAX];i++){
        soma+= vetor[i];
    }
    printf("soma: %f",soma);
    float media = soma / MAX;

    printf("MÉDIA sequencial: %4.f \n",media);
    
    //Paralelo:
   

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
