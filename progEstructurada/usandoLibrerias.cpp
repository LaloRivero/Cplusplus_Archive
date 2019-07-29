#include <stdio.h>
#include <stdlib.h>
#include "operaciones.h"

int main (){
    printf("Usando nuevas librerias");

    float fValue = 10;
    float sValue = 15;
    float res; 
    int op;

    printf("Soy una calculadora! \n");
    printf("Que operacion deseas realizar? \n");
    printf("1. Suma \n");
    printf("2. Resta \n");
    printf("3. Multiplicacion \n");
    printf("4. Division \n");
    printf("Elige una opcion \n");

    scanf("%i", &op);

    switch (op)
    {
    case 1:
        res = addition(fValue, sValue);
        break;

    case 2:
        res = substraction(fValue, sValue);
        break;

    case 3:
        res = multiplication(fValue, sValue);
        break;

    case 4:
        res = division(fValue, sValue);
        break;

    default:
        printf("Opcion invalida\n");
        break;
    }

    printf("El resultado de la operacion es : %f\n", res);
}