#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define NUM_THREADS 10

/*
Definir la subrutina *void por el pthread
*/

void *PrintHello(void *paramID){
    //convertir de entero puntero a void - puntero a entero
    int *id;    //puntero a enter
    id = (int *)paramID; //Cast explicito de void * a int*

    printf("Hola mundo desde el hilo %d\n",*id);

    pthread_exit(NULL);

    return NULL;

}

int main(int argc, char const *argv[])
{
    pthread_t threadsID[NUM_THREADS];

    int rc , t , param[NUM_THREADS];

    for (t = 0; t < NUM_THREADS; t++)
    {
        printf("Rutina Main principal: creando el hilo num #%d\n",t);
        /*asignar valor al parametro que pasara a subrutina*/
        param[t]=t;

        rc = pthread_create(&threadsID[t],NULL,PrintHello,(void *)&param[t]);

        //verificar que todos los hilos se hayan creado correctamente
        if (rc)
        {
            printf("ERROR: codigo retornado desde pthread_create() %d",rc);
            exit(-1);
        }
    }
    

    pthread_exit(NULL);

    
    return 0;
}
