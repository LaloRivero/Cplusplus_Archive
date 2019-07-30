#include <stdio.h>

int main()
{
    int n;
    long long int fact = 1;

    printf("Ingresa un numero para calcular el factorial: \n");
    scanf("%d", &n);

    for(int i = 1; i <= n ; i++ ){
        fact *= i;
    }
            
    printf("%lld\n", fact);
}