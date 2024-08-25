#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define N 131072
#define THRESHOLD 1024 // Umbral para el tamaño mínimo del subproblema

long count_key_recursive(long *a, long start, long end, long key) {
    long count = 0;

    if (end - start <= THRESHOLD) {  // Si el tamaño del subproblema es pequeño, realizar secuencialmente
        for (long i = start; i < end; i++) {
            if (a[i] == key) count++;
        }
    } else {
        long mid = (start + end) / 2;
        long count1 = 0, count2 = 0;

        #pragma omp task shared(count1) // Crear tarea para la primera mitad
        count1 = count_key_recursive(a, start, mid, key);

        #pragma omp task shared(count2) // Crear tarea para la segunda mitad
        count2 = count_key_recursive(a, mid, end, key);

        #pragma omp taskwait // Esperar a que ambas tareas terminen

        count = count1 + count2; // Combinar resultados
    }

    return count;
}

int main() {
    long a[N], key = 42, nkey = 0;
    
    // Inicialización del arreglo con valores aleatorios
    for (long i = 0; i < N; i++) a[i] = rand() % N;
    a[N % 43] = key; 
    a[N % 73] = key; 
    a[N % 3] = key;
    
    // Configurar el número de hilos deseados
    omp_set_num_threads(4); // Puedes ajustar el número de hilos

    // Conteo paralelo
    #pragma omp parallel
    {
        #pragma omp single // Solo un hilo debe iniciar la primera tarea
        {
            nkey = count_key_recursive(a, 0, N, key);
        }
    }

    printf("Numero de veces que 'key' aparece en paralelo: %ld\n", nkey);

    return 0;
}
