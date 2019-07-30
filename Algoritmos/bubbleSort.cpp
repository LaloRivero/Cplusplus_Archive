/* Ordenamiento de MAYOR A MENOR

1. Comenzamos a hacer la comparación de elemtos adyacentes.
2. Repetimos hasta tener una pasada completa sin ningun swap. */

#include <stdio.h>

void cambiarPos(int *n1, int *n2){
    int temp = *n1;
    *n1 = *n2;
    *n2 = temp;
}

void bubbleSort(int vectorEntrada[], int n){
    int i, j;
    for( i = 0 ; i < n-1 ; i++){
        for( j = 0 ; j < n - i - 1 ; j++){

            //Solo es cuestion de cambiar el simbolo de mayor que a menor que
            if(vectorEntrada[j] < vectorEntrada[j + 1]){
                cambiarPos(&vectorEntrada[j], &vectorEntrada[j+1]);
            }
        }
    }
}

int print(int vectorEntrada[], int n){
    for(int i = 0 ; i < n ; i++){
        printf("%d ", vectorEntrada[i]);
    }
    printf("\nFin del ordenamiento");
}

int main (){
    int vectorEntrada[] = {100, 1992, 0, 5, -1, 60, 70, 15, 14, 10};
    int n = sizeof(vectorEntrada)/sizeof(vectorEntrada[0]);

    bubbleSort(vectorEntrada, n);
    print(vectorEntrada, n);
    printf("\n");

    return 0;
}