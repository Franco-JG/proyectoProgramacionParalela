#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <stdint.h>
#include <time.h>
#include <pthread.h>

#define N 1000000000
#define NUM_THREADS 4

bool *arr;
int sqrtN;
uint64_t tiempo;
struct timespec ini, fin;

typedef struct {
    int thread_id;
    int start;
    int end;
} thread_data_t;

void *marcarMultiplos(void *arg) {
    thread_data_t *data = (thread_data_t *)arg;
    int start = data->start;
    int end = data->end;
    
    for (int i = 2; i <= sqrtN; i++) {
        if (arr[i]) {
            int j = fmax(i * i, (start + i - 1) / i * i);
            for (; j <= end; j += i) {
                arr[j] = false;
            }
        }
    }
    pthread_exit(NULL);
}

int main() {
    arr = (bool *)malloc((N + 1) * sizeof(bool));
    if (arr == NULL) {
        puts("No se pudo asignar la memoria.\n");
        return EXIT_FAILURE;
    }
    
    for (int i = 0; i <= N; i++) {
        arr[i] = true;
    }
    arr[0] = arr[1] = false;
    
    sqrtN = (int)sqrt(N);
    
    pthread_t threads[NUM_THREADS];
    thread_data_t thread_data[NUM_THREADS];
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &ini); 
    int segmento = (N - 2 + 1) / NUM_THREADS;
    for (int t = 0; t < NUM_THREADS; t++) {
        thread_data[t].thread_id = t;
        thread_data[t].start = t * segmento + 2;
        thread_data[t].end = (t + 1) * segmento + 1;
        if (t == NUM_THREADS - 1) {
            thread_data[t].end = N;
        }
        pthread_create(&threads[t], NULL, marcarMultiplos, &thread_data[t]);
    }
    
    for (int t = 0; t < NUM_THREADS; t++) {
        pthread_join(threads[t], NULL);
    }
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &fin);
    tiempo = 1e9*(fin.tv_sec - ini.tv_sec) + (fin.tv_nsec - ini.tv_nsec);
    printf("Tiempo cálculo paralelo: %.3f ms\n", tiempo/1000000.0);
    /* printf("Numeros primos menores o iguales a %d:\n", N);
    for (int i = 2; i <= N; i++) {
        if (arr[i]) {
            printf("%d ", i);
        }
    } */
    int i = 0, j = 0; 
    while (i <= N)
    {
        if(arr[i] == true){
            j = i;
        }
        i++;
    }
    printf("Último num primo: %d\n",j);
    
    free(arr);
    return EXIT_SUCCESS;
}