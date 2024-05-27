#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <stdint.h>
#include <time.h>
#include <mpi.h>

#define N 100000000

bool *arr;
int sqrtN;
uint64_t tiempo;
int my_rank, num_procs;

void marcarMultiplos(int start, int end) {
    for (int i = 2; i <= sqrtN; i++) {
        if (arr[i]) {
            int j = (start % i == 0) ? start : (start / i + 1) * i;
            if (j < i * i) j = i * i;
            for (; j <= end; j += i) {
                arr[j] = false;
            }
        }
    }
}

int main(int argc, char *argv[]) {
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &num_procs);

    arr = (bool *)malloc((N + 1) * sizeof(bool));
    if (arr == NULL) {
        puts("No se pudo asignar la memoria.\n");
        MPI_Finalize();
        return EXIT_FAILURE;
    }

    for (int i = 0; i <= N; i++) {
        arr[i] = true;
    }
    arr[0] = arr[1] = false;

    sqrtN = sqrt(N);

    int segmento = (N + 1 - 2) / num_procs;
    int start = my_rank * segmento + 2;
    int end = (my_rank == num_procs - 1) ? N : (my_rank + 1) * segmento + 1;

    MPI_Barrier(MPI_COMM_WORLD);
    tiempo = MPI_Wtime();

    marcarMultiplos(start, end);

    MPI_Barrier(MPI_COMM_WORLD);
    tiempo = MPI_Wtime() - tiempo;

    // Reducir los resultados en el proceso 0
    bool *global_arr = NULL;
    if (my_rank == 0) {
        global_arr = (bool *)malloc((N + 1) * sizeof(bool));
    }

    MPI_Reduce(arr, global_arr, N + 1, MPI_C_BOOL, MPI_LAND, 0, MPI_COMM_WORLD);

    if (my_rank == 0) {
        printf("Tiempo cálculo paralelo: %.3f s\n", (double)tiempo);

        int last_prime = 0;
        for (int i = N; i >= 0; i--) {
            if (global_arr[i]) {
                last_prime = i;
                break;
            }
        }
        printf("Último num primo: %d\n", last_prime);

        free(global_arr);
    }
    free(arr);
    MPI_Finalize();
    return EXIT_SUCCESS;
}
