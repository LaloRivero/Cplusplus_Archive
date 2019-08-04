/* Buscaremos el minimo de monedas posible para obtener el cambio total N, 
tomando mondas del set monedas coinSet[]
necesitamos un auxiliar "res" para cada moneda que funione crear una 
funcion recursiva para encontrar el valor y retornar "monedas necesarias para el cambio" */

#include <iostream>
#include <climits>
using namespace std;

int greedyChange(int coinSet[], int n, int Cambio){
    if(Cambio==0){ //Si no tenemos que dar cambio detiene la ejecucion 
        return 0;
    }if(Cambio<0)
    { // Si las operaciones resultan en numeros negativos regresa  INT_MAX -> Maximum value for an object of type int | 32767 (215-1) or greater* | <climits>
        return INT_MAX;
    }
    int coins = INT_MAX;

    ///Recorremos todo nuestro set de monedas AKA opciones para dar cambio
    for(int i = 0 ; i < n ; i++){
        int res = greedyChange(coinSet, n, Cambio - coinSet[i]);
        if( res != INT_MAX){
            coins = min(coins, res + 1);
        }
    }
    return coins;
}

int main (){
    int coinSet[]={1,5,10,15,20}; // son las monedas con las que cuento para dar cambio 
    int n = sizeof(coinSet)/sizeof(coinSet[0]); // Es el tamaño del array
    cout<<"Ingresa cuando es tu cambio "<<endl;
    int cambio = 0;
    cin>>cambio;

    cout<<"El minimo de monedas para dar cambio es: "
        << greedyChange(coinSet, n, cambio)<<endl;
}
