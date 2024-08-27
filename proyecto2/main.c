#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <omp.h>

#define puntosTotales 2000000000

int puntosCirculo = 0;

void iniciarVariables() {
    srand(time(NULL));
}

void generarPuntosSecuencial() {
    double x, y;

    for (int i = 0; i < puntosTotales; i++) {
        x = (double)rand() / RAND_MAX;
        y = (double)rand() / RAND_MAX;

        if (x * x + y * y <= 1) {
            puntosCirculo++;
        }
    }
}

double calcularPI(int puntosCirculo, int total_puntos) {
    return 4.0 * puntosCirculo / total_puntos;
}

int main() {
    iniciarVariables();

    double inicio = omp_get_wtime();  // Inicia el cronómetro

    generarPuntosSecuencial();  // Ejecuta la versión secuencial

    double fin = omp_get_wtime();  // Detiene el cronómetro

    double pi_aproximado = calcularPI(puntosCirculo, puntosTotales);
    printf("El valor aproximado de Pi es: %f\n", pi_aproximado);

    printf("Tiempo de ejecucion secuencial: %f segundos\n", fin - inicio);  // Imprime el tiempo de ejecución

    return 0;
}

