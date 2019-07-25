#include <stdio.h>
#include <stdlib.h>

int main(){
    float radio, area, altura, volumen;

    //Se leen los valores de las variables

    printf("Vamos a calcular el volumen de un cilindro! \n\n");
    printf("Ingresa el radio de la base: \n");
    scanf("%f", radio);
    printf("Ingresa la altura del cilindro: \n");
    scanf("%f", altura);

    //Realizamos las operaciones
    
    area = 3.1416 * radio * radio;
    volumen = area * altura;

    //Mostramos el resultado
    printf("\nEl area de la base es: %f \n", area);
    printf("El volumen del cilindro es: %f ", volumen);
    
    return 0;
}