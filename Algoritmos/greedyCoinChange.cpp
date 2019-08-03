/* Buscaremos el minimo de monedas posible para obtener el cambio total N, 
tomando mondas del set monedas coinSet[]
necesitamos un auxiliar "res" para cada moneda que funione crear una 
funcion recursiva para encontrar el valor y retornar "monedas necesarias para el cambio" */

#include <iostream>
#include <climits>
using namespace std;

int greedyChange(int coinSet[], int n, int C){
    if(C==0){
        return 0;
    }if(C<0){
        return INT_MAX;
    }
    int coins = INT_MAX;

    ///Recorremos todo nuestro set de monedas AKA opciones para dar cambio
    for(int i = 0 ; i < n ; i++){
        int res = greedyChange(coinSet, n, C - coinSet[i]);
       
        if( res != INT_MAX){
            coins = min(coins, res + 1);
        }
    }
    return coins;
}

int main (){
    int coinSet[]={1,5,10,15,20};
    int n = sizeof(coinSet)/sizeof(coinSet[0]);
    cout<<"Ingresa cuando es tu cambio "<<endl;
    int cambio = 0;
    cin>>cambio;

    cout<<"El minimo de monedas para dar cambio es: "
        << greedyChange(coinSet, n, cambio)<<endl;
}
