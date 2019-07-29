#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Creando un User defined data type

struct monster
{
    char name[50];
    int life;
    int attack;
    char type[16];
};

int main (){
    struct monster perrosaurio = {"Perrosaurio", 100, 75, "Fire"};

    printf("Monster name: %s \n", perrosaurio.name );
    printf("Monster life: %i \n", perrosaurio.life);
    printf("Monster attack: %i \n", perrosaurio.attack);
    printf("Monster type: %s \n", perrosaurio.type);
}