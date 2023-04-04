#include <stdio.h>
#include <omp.h>
#include <stdlib.h>
#include <time.h>

#define num_steps 100000000

int main() {

    //Declaração:
    double step;
    double pi, comeco, final;
    int t = omp_get_num_threads();
    
    pi = 0;
    comeco = omp_get_wtime();
    step = 1.0/(double) num_steps;

    #pragma omp parallel num_threads(4)
    {
        //Cada Thread possui suas variáveis locais
        double x,sum;
        sum= 0.0;
        int i, id, nthrds;

        id = omp_get_thread_num();
        nthrds = omp_get_num_threads();

        for (i=id,sum=0.0;i< num_steps; i=i+nthrds){
            x = (i + 0.5) * step;
            sum = sum + 4.0 / (1.0 + x*x);
        }

        //Usando o omp critical:
        #pragma omp critical
            pi+=sum*step;
        //Apenas uma thread de cada vez acessa o pi para acumular a soma

    }

    //Capturando tempo:
    final = omp_get_wtime();
    double tempo = final - comeco;

    printf("Valor de Pi : %f\n",pi);
    printf("Tempo de execução: %.4f\n",tempo);
    return 0;
}