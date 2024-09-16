/*

----------------------------------------------------
ejercicio03.cpp
----------------------------------------------------

UNIVERSIDAD DEL VALLE DE GUATEMALA
FACULTAD DE INGENIERIA
DEPARTAMENtO DE CIENCIAS DE LA COMPUTACIÓN

---------------------------------------------------

Descripción: 

---------------------------------------------------

*/

#include <pthread.h>
#include <iostream>

using namespace std;

struct hilo_data {
    int n;
    int threadID;

};

void *calc_funcion(void *arg){
    hilo_data *data = (hilo_data *)arg;

    int n = data-> n;
    int tID =  data->threadID;

    double *resultado = new double;
    *resultado = 1.0 / (n * (n+1));

    printf("Hilo %d obtuvo el resultado: %f\n", tID, *resultado);

    pthread_exit((void *)resultado);  
    
}


int main(){


    //variables a usar
    long i;
    int numMax,numThreads, rc;
    double sumaTotal = 0.0;

    //declaracion de variables para los hilos junto a los atributos
    
    pthread_attr_t attr;

    pthread_attr_init(&attr);

    pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_JOINABLE);

    //preguntas al usuario
    cout<<"Ingrese el numero máximo para usar en la serie geometrica"<<endl;
    cin>>numMax;

    numThreads = numMax;  

    pthread_t tids[numThreads];
    hilo_data hilo_data[numThreads];


    //creacion de los hilos
    for(i=0; i<numThreads; i++){
        
        hilo_data[i].threadID = i;
        hilo_data[i].n = i + 1;

        rc = pthread_create(&tids[i],&attr,calc_funcion,(void *)&hilo_data[i]);



        if (rc) {
            cout << "Error: No se pudo crear el hilo " << i << endl;
            exit(-1);
        }

    }
    
    for(i=0; i<numThreads; i++){
        void* resultadoParcial;

        pthread_join(tids[i], &resultadoParcial);

        sumaTotal += *(double *)resultadoParcial;

        delete (double *)resultadoParcial;
    }

    printf("La suma total de la serie es: %f\n", sumaTotal);

    return 0;

}


