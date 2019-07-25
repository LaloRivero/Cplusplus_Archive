#include <stdlib.h>
#include <stdio.h>

int main(){
    int var; 
    printf("Ingresa un valor entero: ");
    scanf("%i", &var);
    
    var %= var;
    var++;

    printf("El resultado de las operaciones es: %i",var);
}