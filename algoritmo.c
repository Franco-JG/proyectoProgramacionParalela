#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#define N 100

int main()
{   
    //* Reservamos memoria para un arraglo de N elementosde tipo bool
    bool *arr = (bool *)malloc(N+1 * sizeof(bool));
    if (arr == NULL)
    {
        puts("No se pudo asignar la memoria.\n");
        return 1;
    }
    //* Inicializamos elementos
    arr[0] = false;
    arr[1] = false;
    for (int i = 2; i <= N; i++)
        arr[i] = true;
        
    printf("%d:\t %s\n", N, arr[N] ? "true" : "false");

    //? Liberamos memoria
    free(arr);
    
    return 0;
}
