#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>
#include <stdint.h>

#define N 1000000000

bool *arr;
int pivote = 2;
int i, j;
uint64_t tiempo;
struct timespec ini, fin;
char *cadena;
double sqrtN;


int main()
{   
    arr = (bool *)malloc(N+1 * sizeof(bool));
    if (arr == NULL)
    {
        puts("No se pudo asignar la memoria.\n");
        return EXIT_FAILURE;
    }
    arr[0] = arr[1] = false;

    sqrtN = (int)sqrt(N);
    for (i = 2; i <= N; i++)
        arr[i] = true;
    clock_gettime(CLOCK_MONOTONIC, &ini); //* 
    while (pivote <= sqrtN) 
    {
        j = pivote*pivote;
        while (j <= N)
        {
            arr[j] = false;
            j += pivote;
        }
        pivote++;
        while (arr[pivote] != true)
        {
            pivote++;
        }
    }
    clock_gettime(CLOCK_MONOTONIC, &fin);
    tiempo = 1e9*(fin.tv_sec - ini.tv_sec) + (fin.tv_nsec - ini.tv_nsec);
    printf("Tiempo cálculo secuencial: %.3f ms\n", tiempo/1000000.0);
    i = j = 0; 
    while (i <= N)
    {
        if(arr[i] == true){
            j = i;
            // printf("%d\n ",j);
        }
        i++;
    }
    printf("Último num primo: %d\n",j);
    free(arr);
    return EXIT_SUCCESS;
}
