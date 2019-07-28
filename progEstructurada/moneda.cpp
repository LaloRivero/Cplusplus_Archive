#include <stdio.h>
#include <stdlib.h>

int conver(float dinero, char divisa){
    float res;

    if(divisa == 'P' || divisa == 'p'){
        res = dinero / 19.05;
        printf("La cantidad en dolares es: %0.2f\n", res);
    }else if(divisa == 'D' || divisa == 'd'){
        res = dinero * 19.05;
        printf("La cantidad en pesos es: %0.2f\n", res);
    }else{
        printf("Lo siento el valor ingresado es incorrecto \n\n");
    }
}

int main(){

    char pesos = 'P', dolares = 'D', divisa;
    float dinero;

    printf("Vamos a convertir divisas \n");
    printf("Para convertir de pesos a dolares escribe: P \n");
    printf("Para convertir de dolares a pesos escribe: D \n\n");
    printf("Ingresa la cantidad que deseas convertir: ");
    scanf("%f", &dinero);
    printf("Ingresa la divisa: ");
    scanf("%s", &divisa);

    conver(dinero, divisa);
}