#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define N 100

bool *arr;
int pivote = 2;
int i, j;


int main()
{   
    //* Reservamos memoria para un arraglo de N elementosde tipo bool
    arr = (bool *)malloc(N+1 * sizeof(bool));
    if (arr == NULL)
    {
        puts("No se pudo asignar la memoria.\n");
        return 1;
    }
    //* Inicializamos elementos
    arr[0] = false;
    arr[1] = false;
    for (i = 2; i <= N; i++)
        arr[i] = true;

    while (pow(pivote,2) <= N) 
    {
        j = pow(pivote,2);
        while (j <= N)
        {
            arr[j] = false;
            j = j + pivote;
        }
        pivote++;
        while (pivote <= N && arr[pivote] != true)
        {
            pivote++;
        }
    }
    i = 0;
    while (i <= N)
    {
        if(arr[i] == true){
            printf("%d, ",i);
        }
        i++;
    }
    //? Liberamos memoria
    free(arr);
    
    return 0;
}
