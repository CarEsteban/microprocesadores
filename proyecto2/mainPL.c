#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define puntosTotales 1000000  // Define el número total de puntos a generar

int puntosCirculo = 0;  // Variable global que cuenta los puntos dentro del círculo

// Función para inicializar variables necesarias antes de la ejecución del programa
void iniciarVariables() {
    srand(time(NULL));  // Inicializa el generador de números aleatorios con la hora actual
}

// Función para generar puntos aleatorios y contar cuántos caen dentro del círculo
void generarPuntos() {
    double x, y;  // Coordenadas de los puntos generados

    // Bucle paralelo que genera los puntos y verifica si caen dentro del círculo
   #pragma omp parallel for reduction(+:puntosCirculo) private(x, y)
   for (int i = 0; i < puntosTotales; i++) {
      // Genera coordenadas aleatorias (x, y) en el rango [0, 1)
      x = (double)rand() / RAND_MAX;
      y = (double)rand() / RAND_MAX;

      // Verifica si el punto (x, y) está dentro del círculo de radio 1
      if (x * x + y * y <= 1) {
         puntosCirculo++;  // Incrementa el contador si el punto está dentro del círculo
      }
   }
}

// Función para calcular el valor aproximado de Pi
// Parámetros:
// - puntosCirculo: Número de puntos que cayeron dentro del círculo
// - total_puntos: Número total de puntos generados
// Retorna: El valor aproximado de Pi
double calcularPI(int puntosCirculo, int total_puntos) {
    return 4.0 * puntosCirculo / total_puntos;  // Fórmula para aproximar Pi
}

// Función principal del programa
int main() {
    iniciarVariables();  // Inicializa las variables necesarias

    generarPuntos();  // Genera puntos y cuenta los que caen dentro del círculo

    // Calcula el valor aproximado de Pi basado en los puntos generados
   double pi_aproximado = calcularPI(puntosCirculo, puntosTotales);

   // Muestra el valor aproximado de Pi
   printf("El valor aproximado de Pi es: %f\n", pi_aproximado);

    return 0;  // Indica que el programa finalizó correctamente
}
