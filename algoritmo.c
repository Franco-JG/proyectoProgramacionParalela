#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define N 100 //* 1,000,000,000 MAX

bool *arr;
int pivote = 2;
int i, j;


int main()
{   
    arr = (bool *)malloc(N+1 * sizeof(bool));
    if (arr == NULL)
    {
        puts("No se pudo asignar la memoria.\n");
        return 1;
    }
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
    i = 0, j = 0; 
    while (i <= N)
    {
        if(arr[i] == true){
            j = i;
        }
        i++;
    }
    printf("Ultimo num primo: %d\n",j);
    free(arr);
    return 0;
}
