/*
*------------------------------------------
* pthread_hello.cpp
* -----------------------------------------
* UNIVERSIDAD DEL VALLE DE GUATEMALA
* FACULTAD DE INGENIERÍA
* DEPARTAMENTO DE CIENCIA DE LA COMPUTACIÓN

* CC3086 - Programacion de Microprocesadores
*
*------------------------------------------
* Descripción: demostracion de operaciones 
* básicas para creación de hilos posix
*------------------------------------------
*/
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h> // Incluye para usar intptr_t

#define NTHREADS 100

/* -----------------------------------------------------------
** Subrutina usada por el pthread, luego de crearse.
** Se debe declarar con punteros, debido a que los threads
** emplean referencias de memoria.  La información pasa por 
** referencia indirecta
** ---------------------------------------------------------*/
void *say_hello(void *threadNumber) {
    // Declarar la variable local que recibe el parámetro
    intptr_t tID;
	
    // Casting del parámetro tipo void* a la variable local tipo intptr_t
    tID = (intptr_t)threadNumber;
    printf("Hello thread: %ld\n", tID);
	
	// Retorno explícito para evitar la advertencia
    pthread_exit(NULL);
    return NULL; 
}
/* -----------------------------------------------------------
** Subrutina Principal: desde esta se crean los objetos tipo
** pthread(identificadore & atributos)  se crean pthreads, y se 
** unifican resultados. Se destruyen los elementos creados.
** ---------------------------------------------------------*/
int main() {
    int rc;
    intptr_t i; // Usar intptr_t para manejar índices de hilos de manera segura
	
	// Declarar una variable tipo pthread_t
    pthread_t tid ;
	
	// Recomendable: declarar tambien un atributo tipo pthread_attr_t
    pthread_attr_t attr;
	// Al usar atributos, inicializar el objeto
    pthread_attr_init(&attr);
	
	// Modificar el atributo especifico
	// en este caso el atributo setdetachstate = JOINABLE
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

    for (i = 0; i < NTHREADS; i++) {
	/* -----------------------------------------------------------
	** Al crear un hilo, se pasan los  siguientes parametros:	
	** el valor del ID, el valor del atributo , la subrutina a
	** ejecutar por el hilo y el puntero para el parametro de 
	** la subrutina:
	**
	** pthread_create(&id,NULL,subrutine,(void *)parameter
	** ---------------------------------------------------------*/
        rc = pthread_create(&tid, &attr, say_hello, (void *)i);
		// La variable rc recibe errores en formato entero
        if (rc) {
            printf("ERROR; return code from pthread_create() is %d\n", rc);
            exit(-1);
        }
		// Esperar a que cada thread termine en orden
        rc = pthread_join(tid, NULL);
        if (rc) {
            printf("ERROR; return code from pthread_join() is %d\n", rc);
            exit(-1);
        }
    }
    // Liberar espacios de memoria utilizados para atributo
    pthread_attr_destroy(&attr);
    pthread_exit(NULL);
}
