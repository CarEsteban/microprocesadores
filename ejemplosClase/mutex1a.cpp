/*---------------------------------------
UNIVERSIDAD DEL VALLE DE GUATEMALA
CC3056 - Programacion de Microprocesadores
Modificado por: Kimberly Barrera
Fecha: 08/11/2019
Mod:   2024/09/12

mutex1a.cpp
Demuestra el uso correcto y simplificado
de las funciones relacionadas a mutex.
---------------------------------------*/

#include<stdio.h>
#include<string.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>

//Defincion de variables: hilos, contador, variable mutex
pthread_t tid[2];
int counter;
pthread_mutex_t lock;

void* doSomeThing(void *arg)
{
    pthread_mutex_lock(&lock);					//establecer bloqueo antes utilizar recurso

    unsigned long i = 0;
    counter += 1;								//incialización variable utilizada para retardo
    printf("\n Job %d started\n", counter);

    for(i=0; i<(0xFFFFFFFF);i++);
    printf("\n Job %d finished\n", counter);

    pthread_mutex_unlock(&lock);
    return nullptr;
}

int main(void)
{
    int i = 0;
    int err;
    if (pthread_mutex_init(&lock, nullptr) != 0) 				//inicializacion de mutex no completada
    {
        printf("\n mutex init failed\n");
        return 1;
    }
    while(i < 2)							//se crean solo 2 hilos
    {
        err = pthread_create(&(tid[i]), nullptr, &doSomeThing, nullptr); 	//creacion de hilos sin paso de parametros
        if (err != 0)
            printf("\ncan't create thread :[%s]", strerror(err));	//impresion de mensaje si el hilo no se crea correctamente
        i++;
    }

    pthread_join(tid[0], nullptr);
    pthread_join(tid[1], nullptr);
    pthread_mutex_destroy(&lock);					//destruccion de mutex dinamica ya usada

    return 0;
}
