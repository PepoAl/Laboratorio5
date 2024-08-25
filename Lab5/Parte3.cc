#include <stdio.h>
#include <omp.h>

// Función para calcular el factorial de un número
long long factorial(int n) {
    long long result = 1;
    for (int i = 2; i <= n; i++) {
        result *= i;
    }
    return result;
}

// Función para generar la serie de Fibonacci hasta el n-ésimo término
void fibonacci(int n) {
    long long a = 0, b = 1, c;
    printf("Serie Fibonacci hasta %d términos: ", n);
    for (int i = 0; i < n; i++) {
        printf("%lld ", a);
        c = a + b;
        a = b;
        b = c;
    }
    printf("\n");
}

// Función para encontrar el máximo en un arreglo
int find_max(int arr[], int size) {
    int max = arr[0];
    for (int i = 1; i < size; i++) {
        if (arr[i] > max) {
            max = arr[i];
        }
    }
    return max;
}

int main() {
    // Ejemplo de uso para cada función
    int n = 5; 
    int arr[] = {1, 3, 5, 2, 4}; 
    int size = sizeof(arr) / sizeof(arr[0]);

    // Iniciar la paralelización con OpenMP
    #pragma omp parallel sections
    {
        #pragma omp section
        {
            long long fact = factorial(n);
            printf("Factorial de %d es %lld\n", n, fact);
        }

        #pragma omp section
        {
            fibonacci(n);
        }

        #pragma omp section
        {
            int max = find_max(arr, size);
            printf("El máximo en el arreglo es %d\n", max);
        }
    }

    return 0;
}
