#include <stdio.h>
#include <stdlib.h>

int main(){
    int value = 11;

    printf("Operadores de Asignacion\n\n");  
    printf("El valor de nuestra variable es %i \n", value);
    value +=1;
    printf("El valor de nuestra variable es %i \n", value);
    value -=2;
    printf("El valor de nuestra variable es %i \n", value);
    value *=5;
    printf("El valor de nuestra variable es %i \n", value);
    value /=4;
    printf("El valor de nuestra variable es %i \n", value);
    value %= 6;
    printf("El valor de nuestra variable es %i \n", value);

}