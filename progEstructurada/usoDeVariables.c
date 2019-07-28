#include <stdlib.h>
#include <stdio.h>

char nombre[256];
int calif; //Base 100

int calCalif(){
    if(calif >= 60){
        printf("El alumn@ %s ha sid@ aprobad@.\n\n", nombre);
    }else if(calif<60){
        printf("El alumn@ %s ha sid@ reprobad@.\n\n", nombre);
    }
}

int main (){
    printf("Variables Globales\n\n");
    printf("Ingresa el nombre del alumno: ");
    gets(nombre);
    printf("Ingresa la calificacion: ");
    scanf("%i", &calif);

    calCalif();
}