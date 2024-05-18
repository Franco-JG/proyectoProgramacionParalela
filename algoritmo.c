#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>
#include <stdint.h>

#define N 1000000000 //* 1,000,000,000 MAX

bool *arr;
int pivote = 2;
int i, j;
uint64_t tiempo;
struct timespec ini, fin;



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
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &ini);
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
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &fin);
    tiempo = 1e9*(fin.tv_sec - ini.tv_sec) + (fin.tv_nsec - ini.tv_nsec);
    printf("Tiempo calculo secuencial: %.3f ms\n", tiempo/1000000.0);
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
