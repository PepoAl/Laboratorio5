#include <stdio.h>
#include <omp.h>

int main() {
    int variable1 = 5;  // Esta variable será compartida entre todos los hilos
    int variable2 = 10;  // Esta variable será privada para cada hilo

    // Configuramos el número de hilos (opcional)
    omp_set_num_threads(4);

    // Ciclo paralelo con OpenMP
    #pragma omp parallel for shared(variable1) private(variable2)
    for (int i = 0; i < 10; i++) {
        // Cada hilo tiene su propia copia de variable2 (es privada)
        variable2 = i;
        




        // variable1 es compartida, así que la modificación se comparte entre todos los hilos
        variable1 += i;

        printf("Hilo %d: i = %d, variable1 = %d, variable2 = %d\n", omp_get_thread_num(), i, variable1, variable2);
    }

    printf("Final: variable1 = %d (compartida), variable2 = %d (último valor de hilo, privada)\n", variable1, variable2);

    return 0;
}
