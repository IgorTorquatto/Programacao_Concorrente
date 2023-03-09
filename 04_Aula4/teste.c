#include <stdio.h>
#include <locale.h>

int main (void){
    setlocale(LC_ALL,"Portuguese");
    printf("teste com acentuação");
    return 0;
}