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
   pthread_t threadsID;
   pthread_attr_t attr;


   //Inicializador
   pthread_attr_init(&attr);

   // Modificar los atributos del thread
   pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);


   int rc, t, param;

   for (t = 0; t < NUM_THREADS; t++) {
      param = t;
      rc = pthread_create(&threadsID, &attr, PrintHello, (void *)&param);

      if (rc) {
         printf("ERROR: código retornado desde pthread_create() es %d\n", rc);
         exit(-1);
      }

      pthread_join(threadsID, NULL);
   }


   pthread_attr_destroy(&attr);
   pthread_exit(NULL);
}
