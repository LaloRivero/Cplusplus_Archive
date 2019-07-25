#include <iostream>
using namespace std;

int main(){
  int var;
  cout<<"Adivina un numero entre 0 y 10:"<<endl; //Es lo mismo que printf pero en C++
  cin>>var; //es lo mismo que scanf pero en C++

  //El numero que buscamos es el 5
  if(var==5){
    printf("Felicidades Adivinaste");
  }else{
    printf("Lo siento. Perdiste!");
  }
}