#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <stdint.h>
#include <time.h>
#include <pthread.h>

#define N 1000000000        // Definir el límite máximo para buscar números primos
#define NUM_THREADS 4 // Definir el número de threads a utilizar

bool *arr;   // Arreglo de booleanos para marcar números primos
int sqrtN;   // Raíz cuadrada de N
uint64_t tiempo;
struct timespec ini, fin;
int i, j;

typedef struct {
    int id;
    int start; // Índice de inicio del segmento para el thread
    int end;   // Índice de fin del segmento para el thread
} thread_data_t;

// Función que marca los múltiplos de números primos en un segmento específico
void *marcarMultiplos(void *arg) {
    thread_data_t *data = (thread_data_t *)arg; // Obtener los datos del thread
    int id = data->id; // Indice del thread
    int start = data->start; // Índice de inicio del segmento
    int end = data->end;     // Índice de fin del segmento
    // Iterar sobre todos los números primos hasta sqrtN
    for (int i = 2; i <= sqrtN; i++) {
        if (arr[i]) { // Si el número es primo
            // Encontrar el primer múltiplo de i en el segmento
            int j = (i * i > (start + i - 1) / i * i) ? i * i : (start + i - 1) / i * i;
            // Marcar todos los múltiplos de i en el segmento como no primos
            for (; j <= end; j += i) {
                arr[j] = false;
            }
        }
    }
    pthread_exit(NULL); // Terminar el thread
}

int main() {
    // Asignar memoria para el arreglo de booleanos
    arr = (bool *)malloc((N + 1) * sizeof(bool));
    if (arr == NULL) {
        puts("No se pudo asignar la memoria.\n");
        return EXIT_FAILURE;
    }
    
    // Inicializar todos los elementos del arreglo como verdaderos
    for (int i = 0; i <= N; i++) {
        arr[i] = true;
    }
    arr[0] = arr[1] = false; // 0 y 1 no son primos
    
    sqrtN = sqrt(N); // Calcular la raíz cuadrada de N
    
    pthread_t threads[NUM_THREADS]; // Arreglo para almacenar los IDs de los threads
    thread_data_t thread_data[NUM_THREADS]; // Arreglo para almacenar los datos de los threads
    
    int segmento = (N + 1 - 2) / NUM_THREADS; // Calcular el tamaño de cada segmento
    // printf("segment size: %d\n",segmento);
    clock_gettime(CLOCK_MONOTONIC, &ini);
    // Crear y lanzar los threads
    for (int t = 0; t < NUM_THREADS; t++) {
        thread_data[t].id = t;
        thread_data[t].start = t * segmento + 2; // Calcular el índice de inicio del segmento
        thread_data[t].end = (t + 1) * segmento + 1; // Calcular el índice de fin del segmento
        // printf("ini_i %d fin_i %d",thread_data[t].start, thread_data[t].end);
        if (t == NUM_THREADS - 1) {
            thread_data[t].end = N; // Asegurarse de que el último segmento llegue hasta N
        }
        pthread_create(&threads[t], NULL, marcarMultiplos, &thread_data[t]); // Crear el thread
    }
    
    // Esperar a que todos los threads terminen
    for (int t = 0; t < NUM_THREADS; t++) {
        pthread_join(threads[t], NULL);
        // printf("thread %d success\n",t);
    }
    clock_gettime(CLOCK_MONOTONIC, &fin);
    tiempo = 1e9*(fin.tv_sec - ini.tv_sec) + (fin.tv_nsec - ini.tv_nsec);
    printf("Tiempo cálculo paralelo: %.3f ms\n",tiempo/1000000.0);
    // Imprimir todos los números primos encontrados
    i = j = 0;
    while (i <= N)
    {
        if(arr[i] == true){
            j = i;
        }
        i++;
    }
    printf("Último num primo: %d\n",j);
    
    // Liberar la memoria asignada
    free(arr);
    return EXIT_SUCCESS;
}
