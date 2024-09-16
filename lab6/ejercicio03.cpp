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
};

void *calc_funcion(void *arg){
    hilo_data *data = (hilo_data *)arg;

    int n = data-> n;

    double result = 1.0 / (n * (n+1));

    return nullptr;
}


int main(){


    //variables a usar
    long i;
    int numMax,numThreads=numMax, rc;

    //declaracion de variables para los hilos junto a los atributos
    
    pthread_attr_t attr;

    pthread_attr_init(&attr);

    pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_JOINABLE);

    //preguntas al usuario
    cout<<"Ingrese el numero máximo para usars en la serie geometrica"<<endl;
    cin>>numMax;

    pthread_t tids[numThreads];



    //creacion de los hilos
    for(i=0; i<numThreads; i++){
        
        hilo_data *data = new hilo_data;

        data->n=i+1;

        rc = pthread_create(&tids[i],&attr,calc_funcion,(void *)&data);



        if (rc) {
            cout << "Error: No se pudo crear el hilo " << i << endl;
            exit(-1);
        }

    }
    
    for(i=0; i<numThreads; i++){
        pthread_join(tids[i], nullptr);
    }

    return 0;

}


