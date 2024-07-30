#include <iostream>
#include <random>
#include <chrono>
#include <algorithm>

using namespace std;

int main() {
    int numeroArreglo;

    // Obtener una semilla basada en el tiempo
    unsigned seed = chrono::system_clock::now().time_since_epoch().count();

    // Inicializar el generador de números aleatorios con la semilla
    mt19937 gen(seed);

    // Definir la distribución
    uniform_int_distribution<> distrib(0, 50);

    cout << "Ingrese el numero del arreglo, maximo 100" << endl;
    cin >> numeroArreglo;

    if (numeroArreglo < 0 || numeroArreglo > 100) {
        cout << "Numero no valido" << endl;
        return 0;
    }

    int arreglo[numeroArreglo] ;  // Usar asignación dinámica

    // Ingresar valor al arreglo
    for (int i = 0; i < numeroArreglo; i++) {
        int numeroAleatorio = distrib(gen);
        arreglo[i] = numeroAleatorio;
    }

    // Imprimir los valores del arreglo para verificar
    for (int i = 0; i < numeroArreglo; ++i) {
        cout << "arreglo[" << i + 1 << "] = " << arreglo[i] << endl;
    }

    int max = arreglo[0];
    int min = arreglo[0];
    int suma = 0;
    int contador = 0;

    for (int i = 0; i < numeroArreglo; i++) {
        suma += arreglo[i];

        if (max < arreglo[i]) {
            max = arreglo[i];
        }

        if (min > arreglo[i]) {
            min = arreglo[i];
        }
    }

    int prom = suma / numeroArreglo;

    for (int i = 0; i < numeroArreglo; i++) {
        if (arreglo[i]>prom)
        {
            contador++;
        }
    }

    int arregloAscendente[numeroArreglo];
    // Copiar los valores del arreglo original al nuevo arreglo
    for (int i = 0; i < numeroArreglo; i++) {
        arregloAscendente[i] = arreglo[i];
    }

    // Ordenar el nuevo arreglo en orden ascendente
    sort(arregloAscendente, arregloAscendente + numeroArreglo);

    cout << "Max: " << max << endl;
    cout << "Min: " << min << endl;
    cout << "Promedio: " << prom << endl;
    cout << "Contador mayores que el promedio: " << contador << endl;

    // Imprimir los valores del arreglo ordenado para verificar
    cout << "Arreglo ordenado ascendente:" << endl;
    for (int i = 0; i < numeroArreglo; ++i) {
        cout << "arregloAscendente[" << i + 1 << "] = " << arregloAscendente[i] << endl;
    }


    return 0;
}
