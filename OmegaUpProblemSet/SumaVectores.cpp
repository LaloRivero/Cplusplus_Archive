#include <iostream>
using namespace std ;

int vector1[101];
int vector2[101];

int main (){

    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n; 
    cin >> n ;

    for(int i = 0 ; i<n ; i++){
        cin>>vector1[i];
    }

    for(int i = 0 ; i<n ; i++){
        cin>>vector2[i];
    }

    for(int i = 0; i < n ; i++){
        cout<<vector1[i] + vector2[i] <<" ";
    }
}