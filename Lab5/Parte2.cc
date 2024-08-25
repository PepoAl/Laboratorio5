#include <stdio.h>
#include <omp.h>

#define N 1000000

int main() {
    long long sum = 0;  // Variable que almacena la suma 
    double start_time, end_time; // variables para medir el tiempo 
//medir el inicio del tiempo
    start_time = omp_get_wtime();
// Paralelizar el bucle for con la clausula reduction para sumar en paralelo 
    #pragma omp parallel for reduction(+:sum)
    for (int i = 1; i <= N; i++) {
        sum += i;
    }

    end_time = omp_get_wtime();

    // imprime el resultado y tiempo de educación 
    printf("La suma de los primeros %d numeros naturales es: %lld\n", N, sum);
    printf("Tiempo de ejecucion: %f segundos\n", end_time - start_time);

    return 0;
}
