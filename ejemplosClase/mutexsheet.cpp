#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#define NUM_ASIENTOS 10

int asientos[NUM_ASIENTOS];
pthread_mutex_t candado;

void *reservar_asientos(void *id_hilo)
{
     int cliente_id = *((int *)id_hilo);
     int asiento_reservado = 0;

     pthread_mutex_lock(&candado); // Bloqueo

     // Intenta reservar un asiento, protegiendo la sección crítica
     // Bloquear el mutex
     for (int i = 0; i < NUM_ASIENTOS && !asiento_reservado; i++)
     {
          if (asientos[i] == 0)
          {
               // Si el asiento está disponible, entonces:
               printf("Cliente %d esta reservando el asiento %d\n", cliente_id, i + 1);
               asientos[i] = 1;
               // Reserva el asiento
               usleep(100);
               // Simulación de retraso en la operación de reserva - acceso al servidor
               printf("Cliente %d ha reservado el asiento %d\n", cliente_id, i + 1);
               asiento_reservado = 1; // Indicar que se ha reservado un asiento
          }
     }
     pthread_mutex_unlock(&candado); // Unlock
     return nullptr;
}

int main()
{
    int cantidadClientes = 80;

     pthread_t ids[cantidadClientes];
     int num_cliente[cantidadClientes];

     pthread_mutex_init(&candado, nullptr);

     for (int i = 0; i < NUM_ASIENTOS; i++)
     {
          asientos[i] = 0;
     }
     for (int i = 0; i < cantidadClientes; i++)
     {
          num_cliente[i] = i + 24100;
          pthread_create(&ids[i], nullptr, reservar_asientos, &num_cliente[i]);
     }

     for (int i = 0; i < cantidadClientes; i++)
     {
          pthread_join(ids[i], nullptr);
     }

     printf("\nEstado Final de los asientos: \n");

     for (int i = 0; i < NUM_ASIENTOS; i++)
     {
          printf("Asiento %d: %s\n", i + 1, asientos[i] ? "Reservado" : "Disponible");
     }
     pthread_mutex_destroy(&candado);
     return 0;      
}