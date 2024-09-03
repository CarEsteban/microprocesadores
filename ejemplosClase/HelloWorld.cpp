#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define NUM_THREADS 10

/*
Definir la subrutina *void por el pthread
*/

void *PrintHello(void *paramID){
    //convertir de entero puntero a void - puntero a entero
    int *id;    //puntero a enter
    double raizID;
    id = (int *)paramID; //Cast explicito de void * a int*

    raizID = sqrt(*id);

    printf("Hola mundo desde el hilo %d, la raiz es %f\n",*id,raizID);


    pthread_exit(NULL);

    return NULL;

}

int main(int argc, char const *argv[])
{
    //crear los atributos
    pthread_attr_t attr;
  
    // Al usar atributos, inicializarlos
    pthread_attr_init(&attr);  
    
    //configuracion para que sea joinable
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);


    pthread_t threadsID[NUM_THREADS];

    int rc , t , param[NUM_THREADS];

    for (t = 0; t < NUM_THREADS; t++)
    {
        printf("Rutina Main principal: creando el hilo num #%d\n",t);
        /*asignar valor al parametro que pasara a subrutina*/
        param[t]=t;

        rc = pthread_create(&threadsID[t],&attr,PrintHello,(void *)&param[t]);

        //verificar que todos los hilos se hayan creado correctamente
        if (rc)
        {
            printf("ERROR: codigo retornado desde pthread_create() %d",rc);
            exit(-1);
        }
    }
    
    for (t = 0; t < NUM_THREADS; t++) {
        pthread_join(threadsID[t], NULL);
    }
    
    pthread_attr_destroy(&attr);

    pthread_exit(NULL);

    
    return 0;
}
