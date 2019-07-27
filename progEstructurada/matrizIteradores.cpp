#include <stdio.h>
#include <stdlib.h>

int main (){
    float matriz[5][6]{
        {6,8,9,10,8,0},
        {9,8,7,8,9, 0},
        {6,6,6,6,6, 0},
        {9,8,8,9,7, 0},
        {8,7,6,7,8, 0}};

    for(int i = 0 ; i < 5 ; i++){
        for(int j = 0 ; j < 5 ; j++){
           matriz[i][5]+= matriz[i][j]; 
        }
        matriz[i][5] /= 5;
    }

    for (int i = 0 ; i < 5; i++){
        printf("El promedio numero %i es igual a: %f \n", i+1, matriz[i][5]);
    }
}