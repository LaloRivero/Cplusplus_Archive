#include <stdio.h>
#include <math.h>

/* Función de insertion Sort*/
void insertionSort(int arr[], int n)
{
    int temp, inc, i, j;
    
    for(inc=1 ; inc < n ; inc = inc*3+1);
        while(inc > 0){
            for (i = inc; i < n; i++)
            {
                j = i;
                temp = arr[i]; 
                while (j >= inc && arr[j-inc] > temp){
                    arr[j] = arr[j - inc];
                    j = j - inc;
                }
                arr[j] = temp;
            }
            inc /= 2;
        }
    
}

// función auxiliar para imprimir un arrary de tamaño n
void printArray(int arr[], int n)
{
    int i;
    for (i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

/* Driver program to test insertion sort */
int main()
{
    int arr[] = {13, 14, 94, 33, 82, 25, 59, 94, 65, 23, 45, 27, 73, 25, 39, 10};
    int n = sizeof(arr) / sizeof(arr[0]);

    insertionSort(arr, n);
    printArray(arr, n);

    return 0;
}