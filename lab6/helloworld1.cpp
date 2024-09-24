#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define NUM_THREADS 100

void *PrintHello(void *paramID) {
    int *id = (int *)paramID;  // Conversión explícita de void* a int*
    printf("hello world thread no. #%d\n" ,  *id);
   pthread_exit(NULL);
   return NULL;
}

int main(int argc, char *argv[]) {
   pthread_t threadsID[NUM_THREADS];
   pthread_attr_t attr;


   //Inicializador
   pthread_attr_init(&attr);

   // Modificar los atributos del thread
   pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);


   int rc, t, param[NUM_THREADS];

   for (t = 0; t < NUM_THREADS; t++) {
      param[t] = t;
      rc = pthread_create(&threadsID[t], &attr, PrintHello, (void *)&param[t]);

      if (rc) {
         printf("ERROR: código retornado desde pthread_create() es %d\n", rc);
         exit(-1);
      }
   }

   //Join de hilos
   for (t = 0; t < NUM_THREADS; t++) {
      pthread_join(threadsID[t], NULL);
      //printf("Haciendo join para numero de hilos %d\n", *threadsID[t]);

   }

   pthread_attr_destroy(&attr);
   pthread_exit(NULL);
}
