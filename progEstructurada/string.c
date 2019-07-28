#include <stdio.h>
#include <stdlib.h>

int main(){
    char cadena [256];
    int n = 0;

    printf("Ingresa una frase: ");
    gets (cadena);
    
    n = strlen(cadena);

    for(int i = n ;i >= 0 ; i--){
        printf("%c", cadena[i]);
    }
    printf("\n");

}