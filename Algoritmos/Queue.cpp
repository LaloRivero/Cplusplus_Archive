/* Para crear una Queue debemos seguir los siguientes pasos:

1 Crear un pointer para saber que hay en front y rear
2 Colocar estos valores en -1 al inicializar
3 Incrementar en 1 el valor de “rear” cuando agregamos un elemento
4 Retornar el valor de front al quitar un elemento e incrementar en 1 el valor de front a usar dequeue.
5 Antes de agregar un elemento revisar si hay espacios
6 Antes de remover un elemento revisamos que existan elementos
7 Asegurarnos de que al remover todos los elementos resetear nuestro front y rear a -1 y agregar el valor de 0 a 
Front al hacer nuestro primer enqueue
 */

#include <stdio.h>
#include <stdlib.h>
#define SIZE 5

int values [SIZE];
int copyValues [SIZE];
int front = -1, rear = -1, cfront = 0;

void enQueue(int value){
    if( rear == SIZE -1 ){
        printf("Nuestro Queue esta lleno\n");
    }else{
        if(front == -1){
            front = 0;
        }
        rear++;
        values[rear] = value;
        printf("Se inserto el valor %d correctamente \n", value);
    }
}

void deQueue(){
    if(front == -1){
        printf("Nuestro Queue esta vacio\n");
    }else{
        printf("Se elimino el valor %d\n", values[cfront]);
        for (int i = 0; i < SIZE; i++)
        {
            if(values[i + 1] != 0){
            copyValues[i] = values[i + 1];
            }else{
                copyValues[i]= -1;
            }
            
        }
        for (int i = 0; i < SIZE; i++){
            if (copyValues[i] != -1){
                values[i] = copyValues[i];
            }
            else{
                values[i] = 0;
            }
        }
        rear--;
        front++;
        if(copyValues[0] == -1){
            front = rear = -1;
        } 
    }
} 

int main(){

    deQueue();
    enQueue(10);
    enQueue(5);
    enQueue(7);
    enQueue(3);
    enQueue(8);
    deQueue();
    deQueue();
    enQueue(2);
    enQueue(4);
    enQueue(6);
    deQueue();
    deQueue();
    deQueue();
    deQueue();
    deQueue();
    deQueue();

    return 0 ;
}