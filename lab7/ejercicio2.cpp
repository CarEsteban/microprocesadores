#include <iostream>
#include <pthread.h>
#include <string>
#include <unistd.h> // Para la función sleep()

using namespace std;

int bodega = 0;
int silo = 0;
const int n = 400; // Número de bolsas objetivo
bool produccionCompleta = false; // Bandera para detener la producción

// Estructura para pasar argumentos a los hilos
struct HiloArgumentos {
    int id; // Identificador del hilo
    string tipo; // Tipo de hilo: "tostadora" o "empacadora"
};

pthread_mutex_t lock;
pthread_cond_t cond_var; // Condición para la empacadora
pthread_cond_t cond_tost; // Condición para las tostadoras

void* producir(void* args) {
    HiloArgumentos* datos = (HiloArgumentos*)args;

    while (true) {
        if (datos->tipo == "tostadora") {
            sleep(1); // Simulación de tiempo de producción de 1 lb de café
            pthread_mutex_lock(&lock);

            // Verificar si la producción ha terminado
            if (produccionCompleta) {
                pthread_mutex_unlock(&lock);
                break;
            }

            // Esperar si el silo tiene 5 o más libras
            while (silo >= 5 && !produccionCompleta) {
                pthread_cond_wait(&cond_tost, &lock);
            }

            // Verificar nuevamente la condición antes de producir
            if (produccionCompleta) {
                pthread_mutex_unlock(&lock);
                break;
            }

            silo += 1;
            cout << "Tostadora " << datos->id << " produjo: 1 lb de café tostado" << endl;
            cout << "Lbs de café en silo: " << silo << endl;
            pthread_cond_signal(&cond_var); // Notifica a la empacadora que hay café disponible
            pthread_mutex_unlock(&lock);
        } 
        else if (datos->tipo == "empacadora") {
            pthread_mutex_lock(&lock);

            // Verificar si la producción ha terminado
            if (produccionCompleta) {
                pthread_mutex_unlock(&lock);
                break;
            }

            // Esperar hasta que haya al menos 5 libras en el silo para empaquetar
            while (silo < 5 && !produccionCompleta) {
                pthread_cond_wait(&cond_var, &lock); // Espera a que haya café en el silo
            }

            // Empacar hasta que el silo esté vacío o se alcance el objetivo
            while (silo > 0 && bodega < n) {
                silo -= 1;
                bodega += 1;
                cout << "Empacadora produjo: 1 bolsa de 1 lb de café" << endl;
                cout << "Lbs de café en silo: " << silo << endl;
                cout << "Lbs de café en bodega: " << bodega << endl;

                sleep(1); // Simula tiempo de empaquetado de 1 libra
            }

            // Si se alcanzó el objetivo, detener producción
            if (bodega >= n) {
                produccionCompleta = true;
                pthread_cond_broadcast(&cond_tost); // Notificar a todas las tostadoras para que terminen
                pthread_cond_broadcast(&cond_var); // Notificar a la empacadora
            }

            pthread_mutex_unlock(&lock);
        }
    }

    return nullptr;
}

int main() {
    pthread_t hilos[3]; // Arreglo de hilos
    HiloArgumentos argumentos[3]; // Arreglo de argumentos para los hilos

    pthread_mutex_init(&lock, nullptr);
    pthread_cond_init(&cond_var, nullptr);
    pthread_cond_init(&cond_tost, nullptr);

    // Crear hilos utilizando un ciclo for
    for (int i = 0; i < 3; i++) {
        argumentos[i].id = i + 1; // Asigna un ID único para cada hilo
        if (i < 2) {
            argumentos[i].tipo = "tostadora"; // Los dos primeros hilos son tostadoras
        } else {
            argumentos[i].tipo = "empacadora"; // El tercer hilo es la empacadora
        }

        pthread_create(&hilos[i], nullptr, producir, &argumentos[i]);
    }

    // Esperar a que todos los hilos terminen
    for (int i = 0; i < 3; i++) {
        pthread_join(hilos[i], nullptr);
    }

    pthread_mutex_destroy(&lock);
    pthread_cond_destroy(&cond_var);
    pthread_cond_destroy(&cond_tost);
    return 0;
}
