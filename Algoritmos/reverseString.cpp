#include <bits/stdc++.h>
using namespace std;

string str;
int cont;

string reverserString(string str, int cont){
    int size = str.length();
    cont = size;
    if(size == 0){
        return str;
    }else{
        return reverserString();
    }
}

int main (){
    cout<<"Ingresa un mensaje que quieras voltear de manera recursiva"<<endl;
    getline(cin,str);
    cout<<reverserString(str, cont)<<endl;
}