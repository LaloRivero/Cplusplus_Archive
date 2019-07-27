#include <stdlib.h>
#include <stdio.h>

int main(){
    int n = 9;
    int a= 1, b = 1, c;

    printf("%i ", a);
    
    for(int i = 0; i < n-1 ; i++){
        c = a + b;
        a = b;
        b = c;
        printf("%i ", a);
    }
}