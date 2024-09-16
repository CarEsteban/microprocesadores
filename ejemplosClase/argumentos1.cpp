/*---------------------------------------
UNIVERSIDAD DEL VALLE DE GUATEMALA
CC3056 - Programacion de Microprocesadores
Modificado por: Kimberly Barrera
Fecha: 08/11/2019
Mod:   2020/08/23

argumentos1.cpp
Comparte a subrutina argumentos en es-
tructura con elementos de múltpiple 
tipo, hacia el thread creado
---------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

#define num_th 100

struct parameters { 
	int id;
	float val1;
	float val2;
};

void *calculate(void *arg ) {
	parameters *ps;
	ps = (parameters *)arg;
	float res;
	
	
	res = ps -> val1*ps -> val2;
	printf("Thread %d ", ps->id); 
	printf(" resultado %f \n", res); 
	//usleep(1000);
	/*
	 * De forma implicita, el thread llama a exit() al terminar
	 * su ejecucion.
	 */
	pthread_exit(NULL);
	return NULL;
}

int main() {
	pthread_t thread;
	int i;
	parameters p;
	
	
	for(i=1; i<num_th; i++){
		p.id = i;
		p.val1 = i;
		p.val2 = i-1;
		pthread_create(&thread, NULL, calculate, ( void *)&p);
		pthread_join(thread, NULL);
	}
	
	
	printf ("\n --- Fin --- \n");
}