#include <stdlib.h>
#include <stdio.h>


int arr[100001];

int main(){
   int n = 0;
   printf("Ingresa el tamaño del arreglo: ");
   scanf("%i", &n);

   printf("Ingresa los valores: \n");

   for(int i = 1 ; i <= n ; i++){
        printf("Valor[%i]:", i);
        scanf("%i", &arr[i]);

        if(arr[i]>arr[0]){
            arr[0] = arr[i];
        }
   } 

   printf("El numero mayor es: %i \n",arr[0]);

}