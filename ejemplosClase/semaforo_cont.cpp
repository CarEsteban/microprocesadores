/*
*----------------------------------------
* semaf_2.cpp
* ---------------------------------------
* UNIVERSIDAD DEL VALLE DE GUATEMALA
* CC3086 - Programacion de Microprocesadores
* Ver.: 1.1
* Fecha: 2022/09/03
*
* References:
* "Shared-Memory Programming with Pthreads" - Intro to
* Parallel Programming (Pacheco) pp.153 - 181
*
* ---------------------------------------
* Barrier programming pattern with semaphores
*----------------------------------------
*/

#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

//#include <misc/error_checks.h>
sem_t sem;
int sem_v;
// Thread que espera el semaforo
void * waiter(void *arg)
{
	while (1) {
		sem_getvalue(&sem, &sem_v);
        printf(" - X Waiter antes de esperar semaforo: %d\n", sem_v);
        sem_wait(&sem);
		printf(" -/ Waiter despues de esperar semaforo \n");
	}
 return NULL;
}

// Thread que senializa el semaforo
void * signaler(void *arg)
{
    printf ("Signaler antes de senalizar 3 veces \n");
	sem_post(&sem);
    sem_post(&sem);
	sem_post(&sem);
	sleep(10); // deja ejecutar al thread senalizado
	
	while (1) {
		printf ("Signaler antes de liberar %d\n", sem_v);
		sem_post(&sem);
		printf ("Signaler despues de liberar\n");
		sleep(5); // deja ejecutar al thread senalizado
	}
 return NULL;
}

int main()
{
	pthread_t t1,t2;
	int ret;
	sem_init(&sem, 0, 2);  //free - post
	// Crea los threads
	pthread_create(&t1, NULL, waiter, NULL);
	pthread_create(&t2, NULL, signaler, NULL);
	// deja ejecutar un rato y termina
	sleep(30);
	return 0;
}
