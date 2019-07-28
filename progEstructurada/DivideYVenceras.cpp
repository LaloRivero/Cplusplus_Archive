#include <stdio.h>
#include <stdlib.h>

int pow(int num, int exp){
    int res=1;

    for(int i = 0 ; i < exp ; i++){
        res *=num;
    }

    printf("El resultado es: %i\n", res);
}

int main(){
    printf("Potencia de un numero\n");

    int num;
    int exp;

    printf("Base: ");
    scanf("%i", &num);

    printf("Exponente: ");
    scanf("%i", &exp);

    pow(num,exp);
}