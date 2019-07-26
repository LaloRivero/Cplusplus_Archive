#include <stdlib.h>
#include <stdio.h>

int main(){
    printf("Te encuentras en una mision secreta en la cual tienes que desactivar una bomba, \n");
    printf("tienes tres cables de diferentes colores, Amarillo (A), Rosa(R), Morado(M).\n");
    printf("Decide que cable cortar para desactivar la bomba.\n\n");

    char opcion;
    printf("Rapido toma una decision!\n");
    scanf("%c",&opcion);

    switch (opcion)
    {
    case 'A':
        printf("Haz cortado el cable Amarillo, salvaste el día!\n");
        break;

    case 'R':
        printf("Haz cortado el cable Rosa, salvaste el día!\n");
        break;

    case 'M':
        printf("Haz cortado el cable Morado, salvaste el día!\n");
        break;

    default:
        printf("Lo siento ha explotado la BOMBA!\n");
        break;
    }
}