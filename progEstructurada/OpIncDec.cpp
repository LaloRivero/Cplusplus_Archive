#include <stdio.h>
#include <stdlib.h>

int main(){
    int value, res;
    printf("Operadores de Incremento y Decremento\n");
     value = 25;
     res = value++;
    printf("Resultado %i \n", res);
     value = 25;
     res = ++value;
    printf("Resultado %i \n", res);
     value = 25;
     res = value--;
    printf("Resultado %i \n", res);
     value = 25;
     res = --value;
    printf("Resultado %i \n", res);
    return 0;
}
