/*---------------------------------------
UNIVERSIDAD DEL VALLE DE GUATEMALA
CC3056 - Programacion de Microprocesadores
Modificado por: Kimberly Barrera
Fecha: 08/11/2019
Mod:   2024/09/12

Demuestra el uso de recursividad en bloqueo
de un mutex.
---------------------------------------*/

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

pthread_mutex_t mutex;  	// Declaración del mutex
pthread_mutexattr_t attr;   // Declaración de los atributos del mutex

// Estructura para pasar el número de hilo y el nivel
typedef struct {
    int id_hilo;
    int nivel;
} datos_hilo;

// Función recursiva que ejecutan los pthreads al crearse
// intenta bloquear el mutex varias veces
void* funcion_recursiva(void* arg) {
    datos_hilo* datos = (datos_hilo*)arg;
    int nivel = datos->nivel;
    int id_hilo = datos->id_hilo;

    // Bloqueo del mutex
    pthread_mutex_lock(&mutex);
    printf("Hilo %d bloqueando el mutex en nivel %d\n", id_hilo, nivel);

    // Simulación trabajo
    usleep(100000);  // 100 ms

    // Llamada recursiva
    if (nivel > 0) {
        datos_hilo nuevos_datos = { id_hilo, nivel - 1 };
        funcion_recursiva(&nuevos_datos);
    }

    // Desbloqueo del mutex
    printf("Hilo %d desbloqueando el mutex en nivel %d\n", id_hilo, nivel);
    pthread_mutex_unlock(&mutex);

    return nullptr;
}

int main() {
    
	pthread_t hilo1, hilo2;
	
	// Inicialización de los atributos del mutex
    pthread_mutexattr_init(&attr);
    pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE);  // mutex recursivo

    // Inicialización del mutex con los atributos configurados
    pthread_mutex_init(&mutex, &attr);

    // Asignar el nivel de recursión y el número de hilo para cada hilo
    datos_hilo datos1 = { 1, 1 };  // Hilo 1 con nivel 1
    datos_hilo datos2 = { 2, 2 };  // Hilo 2 con nivel 2

    // Crear los hilos
    pthread_create(&hilo1, nullptr, funcion_recursiva, &datos1);
    pthread_create(&hilo2, nullptr, funcion_recursiva, &datos2);

    // Esperar a que los hilos terminen
    pthread_join(hilo1, nullptr);
    pthread_join(hilo2, nullptr);

    // Destruir el mutex y los atributos
    pthread_mutex_destroy(&mutex);
    pthread_mutexattr_destroy(&attr);

    return 0;
}
