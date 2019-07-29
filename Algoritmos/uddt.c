#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//User defined data type

struct client
{
    char Name[50];
    char Id[10];
    float Credit;
    char Address[100]; 
};


int main (){
    struct client client_1 = {0};

    strcpy(client_1.Name, "Camilo Valencia");
    strcpy(client_1.Id, "0000000001");
    client_1.Credit = 1000000;
    strcpy(client_1.Address, "Calle 1 , Carrera 1 Ciudad Bolivar");

    printf("The client Name is: %s \n", client_1.Name);
    printf("The client Id is: %s \n", client_1.Id);
    printf("The client Credit is: %f \n", client_1.Credit);
    printf("The client Address is: %s \n", client_1.Address);
}