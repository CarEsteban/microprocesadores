/*---------------------------------------
UNIVERSIDAD DEL VALLE DE GUATEMALA
CC3056 - Programacion de Microprocesadores
Modificado por: Kimberly Barrera
Mod:   2024/09/12

mutex3.cpp
Demuestra el uso de mutex temporizados
---------------------------------------*/
#include <stdio.h>
#include <pthread.h>
#include <time.h>
#include <unistd.h>
#include <errno.h>

pthread_mutex_t mutex;  // Declaración del mutex

void* intentar_bloquear(void* arg) {
    struct timespec ts;
    int resultado;

    // Obtener el tiempo actual y sumar 2 segundos al tiempo de espera
    clock_gettime(CLOCK_REALTIME, &ts);
    ts.tv_sec += 2000000;  // Esperar hasta 2 segundos

    printf("Hilo secundario intentando bloquear el mutex...\n");

    // Intentar bloquear el mutex con tiempo límite
    resultado = pthread_mutex_timedlock(&mutex, &ts);
    if (resultado == 0) {
        printf("Hilo secundario logro bloquear el mutex\n");
        // Simular alguna operación
        usleep(1000000);
        // Desbloquear el mutex
        pthread_mutex_unlock(&mutex);
        printf("Hilo secundario ha desbloqueado el mutex\n");
    } else if (resultado == ETIMEDOUT) {
        printf("Hilo secundario no pudo bloquear el mutex: tiempo de espera agotado\n");
    } else {
        printf("Error al intentar bloquear el mutex: %d\n", resultado);
    }

    return nullptr;
}

int main() {
    pthread_t hilo1, hilo2;

    // Inicializar el mutex
    pthread_mutex_init(&mutex, nullptr);

    // Bloquear el mutex inicialmente desde el hilo principal
    pthread_mutex_lock(&mutex);
    printf("El hilo principal ha bloqueado el mutex desde main\n");

    // Crear un hilo que intentará bloquear el mutex con tiempo límite
    pthread_create(&hilo1, nullptr, intentar_bloquear, nullptr);
	pthread_create(&hilo2, nullptr, intentar_bloquear, nullptr);
    // Simular alguna operación en el hilo principal
    usleep(3000000);  // Mantener el mutex bloqueado por 3 segundos

    // Desbloquear el mutex
    pthread_mutex_unlock(&mutex);
    printf("El hilo principal ha desbloqueado el mutex desde el main\n");

    // Esperar a que el hilo secundario termine
    pthread_join(hilo1, nullptr);
    pthread_join(hilo2, nullptr);

    // Destruir el mutex
    pthread_mutex_destroy(&mutex);

    return 0;
}
