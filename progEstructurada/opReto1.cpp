#include <stdlib.h>
#include <stdio.h>

int main(){
    printf("Si me das dos numeros, te dare el menor entre ellos! \n");

    int n, m;
    printf("Ingresa el primer numero: ");
    scanf("%i", &n);
    printf("Ingresa el segundo numero: ");
    scanf("%i", &m);

    if(n > m){
        printf("El numero menor es: %i \n", m);
    }else {
        printf("El numero menor es: %i \n", n);
    }
}