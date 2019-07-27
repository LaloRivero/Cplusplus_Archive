#include <stdlib.h>
#include <stdio.h>

int matriz [3][4]= {{10,20,30,40},
                    {11,21,31,41},
                    {12,22,32,42}};
int sum [3];

int main(){
    for(int i = 0; i < 3 ; i++){
        for(int j = 0; j<4 ; j++){
            sum[i] += matriz[i][j];
        }
    }

    printf("Primer fila: %i\n", sum[0]);
    printf("Segunda fila: %i\n", sum[1]);
    printf("Tercer fila: %i\n", sum[2]);
}