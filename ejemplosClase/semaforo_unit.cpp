/*
*----------------------------------------
* semaforo_unit.cpp
* ---------------------------------------
* UNIVERSIDAD DEL VALLE DE GUATEMALA
* CC3086 - Programacion de Microprocesadores
* Ver.: 1.1
* Fecha: 2022/09/03
* Mod:   2023/09/29
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

#define REP_LOOP 1000000

int counter = 0; 


void * routineA(void *arg)
{
    for(int i = 0; i < REP_LOOP;  i++) 
    {
        counter += 1;
    }
    return NULL;
}

void * routineB(void *arg)
{
    for(int i = 0; i < REP_LOOP; i++) 
    {
        counter -= 1;
    }
    return NULL;
}

int main()
{
	pthread_t t1,t2;
	
	// Crea los threads
	pthread_create(&t1, NULL, routineA, NULL);
	pthread_create(&t2, NULL, routineB, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    printf("El valor del contador es: %d\n", counter);
	
	return 0;
}