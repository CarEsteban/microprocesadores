#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define puntosTotales 10000  // Define correctamente la constante

int main(int argc, char const *argv[])
{
    int puntosCirculo = 0;
    double x, y, piAprox;

    // Se inicializa para los números random
    srand(time(NULL));

    for (int i = 0; i < puntosTotales; i++)
    {
        x = (double)rand() / RAND_MAX;
        y = (double)rand() / RAND_MAX;

        if (x * x + y * y <= 1)
        {
            puntosCirculo++;
        }
    }

    // Asegúrate de que la división se realiza con al menos un número de punto flotante
    piAprox = 4.0 * puntosCirculo / (double)puntosTotales;
    printf("El valor aproximado de Pi es: %f\n", piAprox);

    return 0;
}
