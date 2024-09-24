/*---------------------------------------
* UNIVERSIDAD DEL VALLE DE GUATEMALA
* Sistemas Operativos
* Autor: Esteban Cárcamo, Nicolás Concuá
* Fecha: 2024/09/24
*
* ---------------------------------------
* Variables de condición p/acceder a 
* region crítica 
* variables de condición.
*----------------------------------------
*/

#include <iostream>
#include <pthread.h>
#include <string>
#include <unistd.h> // Para la función sleep()

using namespace std;

// Estructura del producto
struct Producto {
    string nombre;
    double precioUnitario;
    double costoFijo;
    int vendidoMes1;
    int vendidoMes2;
};

// Estructura para almacenar los resultados de cada mes
struct Resultados {
    double ventasJulio;
    double utilidadJulio;
    double ventasAgosto;
    double utilidadAgosto;
};

// Estructura para pasar múltiples parámetros al hilo
struct Args {
    int hiloID;
    Producto *producto;
};

// Función para calcular y devolver resultados de Julio y Agosto
void *calc_products(void *args) {
    Args *data = (Args *)args;
    int hiloID = data->hiloID;
    Producto *producto = data->producto;

    // Almacenar los resultados en un array
    double *resultados = new double[4];

    // Imprimir inicio de cálculo
    cout << "calculo hilo " << hiloID << " iniciado" << endl;
    sleep(1); // Simulación de tiempo de cálculo

    // Cálculo de ventas y utilidad para Julio
    resultados[0] = producto->vendidoMes1 * producto->precioUnitario;  // Ventas Julio
    resultados[1] = resultados[0] - (producto->vendidoMes1 * producto->costoFijo); // Utilidad Julio

    // Cálculo de ventas y utilidad para Agosto
    resultados[2] = producto->vendidoMes2 * producto->precioUnitario;  // Ventas Agosto
    resultados[3] = resultados[2] - (producto->vendidoMes2 * producto->costoFijo); // Utilidad Agosto

    // Imprimir fin de cálculo
    cout << "calculo hilo " << hiloID << " terminado" << endl;

    pthread_exit((void*)resultados); // Devolver resultados como puntero void*
}

int main() {
    Producto productos[8] = {
        {"Porción pastel de chocolate", 60.00, 20.00, 300, 250},
        {"White mocha", 32.00, 19.20, 400, 380},
        {"Café americano 8onz", 22.00, 13.20, 1590, 800},
        {"Latte 8onz", 24.00, 17.20, 200, 250},
        {"Toffee coffee", 28.00, 20.10, 390, 600},
        {"Cappuccino 8onz", 24.00, 17.20, 1455, 1200},
        {"S'mores Latte", 32.00, 23.00, 800, 1540},
        {"Café tostado molido", 60.00, 20.00, 60, 15}
    };

    int cantidadProductos = 8;
    pthread_t ids[cantidadProductos];
    pthread_attr_t attr;

    // Inicializar atributos de hilos
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

    Args args[cantidadProductos];
    void *resultadoHilo;
    double totalVentasJulio = 0.0;
    double totalUtilidadJulio = 0.0;
    double totalVentasAgosto = 0.0;
    double totalUtilidadAgosto = 0.0;

    // Crear hilos para cálculo de Julio y Agosto
    for (int i = 0; i < cantidadProductos; i++) {
        args[i].hiloID = i;
        args[i].producto = &productos[i];
        pthread_create(&ids[i], &attr, calc_products, (void *)&args[i]);
    }

    // Esperar a que todos los hilos terminen y acumular resultados
    for (int i = 0; i < cantidadProductos; i++) {
        pthread_join(ids[i], &resultadoHilo);

        double *resultados = (double *)resultadoHilo; // Convertir a puntero de double

        totalVentasJulio += resultados[0];
        totalUtilidadJulio += resultados[1];
        totalVentasAgosto += resultados[2];
        totalUtilidadAgosto += resultados[3];

        // Liberar memoria asignada en el hilo
        delete[] resultados;
    }

    // Imprimir reporte de Julio
    cout << "------------------------------------------" << endl;
    cout << "REPORTE DEL MES DE JULIO" << endl;
    cout << "--- Monto Ventas por Producto ---" << endl;
    for (int i = 0; i < cantidadProductos; i++) {
        cout << "- " << productos[i].nombre << ": Q" << productos[i].vendidoMes1 * productos[i].precioUnitario << endl;
    }
    cout << "--- Utilidad por Producto ---" << endl;
    for (int i = 0; i < cantidadProductos; i++) {
        double utilidad = (productos[i].vendidoMes1 * productos[i].precioUnitario) - (productos[i].vendidoMes1 * productos[i].costoFijo);
        cout << productos[i].nombre << ": Q" << utilidad << endl;
    }
    cout << "--- Monto Total Ventas del Mes: Q" << totalVentasJulio << endl;
    cout << "--- Utilidad del mes: Q" << totalUtilidadJulio << endl;

    // Imprimir reporte de Agosto
    cout << "------------------------------------------" << endl;
    cout << "REPORTE DEL MES DE AGOSTO" << endl;
    cout << "--- Monto Ventas por Producto ---" << endl;
    for (int i = 0; i < cantidadProductos; i++) {
        cout << "- " << productos[i].nombre << ": Q" << productos[i].vendidoMes2 * productos[i].precioUnitario << endl;
    }
    cout << "--- Utilidad por Producto ---" << endl;
    for (int i = 0; i < cantidadProductos; i++) {
        double utilidad = (productos[i].vendidoMes2 * productos[i].precioUnitario) - (productos[i].vendidoMes2 * productos[i].costoFijo);
        cout << productos[i].nombre << ": Q" << utilidad << endl;
    }
    cout << "--- Monto Total Ventas del Mes: Q" << totalVentasAgosto << endl;
    cout << "--- Utilidad del mes: Q" << totalUtilidadAgosto << endl;

    // Liberar recursos de atributos
    pthread_attr_destroy(&attr); 

    return 0;
}
