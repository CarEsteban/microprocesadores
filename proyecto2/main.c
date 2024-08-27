#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define PUNTOS_TOTALES 10000  // Define correctamente la constante

int main(int argc, char const *argv[])
{
    int puntos_circulo = 0;
    double x, y, pi_aproximado;

    // Se inicializa para los números random
    srand(time(NULL));

    for (int i = 0; i < PUNTOS_TOTALES; i++)
    {
        x = (double)rand() / RAND_MAX;
        y = (double)rand() / RAND_MAX;

        if (x * x + y * y <= 1)
        {
            puntos_circulo++;
        }
    }

    // Asegúrate de que la división se realiza con al menos un número de punto flotante
    pi_aproximado = 4.0 * puntos_circulo / (double)PUNTOS_TOTALES;
    printf("El valor aproximado de Pi es: %f\n", pi_aproximado);

    return 0;
}
