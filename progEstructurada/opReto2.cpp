#include <stdlib.h>
#include <stdio.h>

int main(){
    int calif;
    printf("Para saber si aprobo o no ingresa tu calificacion: ");
    scanf("%i", &calif);

    if(calif >= 90){
        printf("Excelente trabajo aprobaste! :D\n");
    }else if(calif < 90 && calif >= 60){
        printf("Felicidades aprobaste! \n");
    }else{
        printf("Lo siento reprobaste!\n");
    }
}