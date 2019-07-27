#include <stdlib.h>
#include <stdio.h>

int main(){
    int arr[6];
    int mult = 1;
    printf("Multiplicar todos los elementos de un arreglo:\n\n");
    printf("Ingresa los valores: \n");
    for(int i = 0 ; i < 5 ; i++){
        printf("Valor[%i]: ", i+1);
        scanf("%i", &arr[i]);
        mult *= arr[i];
    }
    printf("El resultado es: %i\n", mult);
}