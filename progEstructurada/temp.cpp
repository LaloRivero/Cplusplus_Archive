#include <stdio.h>
#include <stdlib.h>

int main(){
    float F, C;
    printf("Hola vamos a convertir de grados Farenheit a grados Celcius\n");
    printf("Ingresa un valor de Temperatura en grados Farenheit: ");
    scanf("%f", &F);

    C = (F-32)*5/9;

    printf("La temperatura en grados Celcius es: %.2f \n",C);

    return 0;
}