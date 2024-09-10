/*

----------------------------------------------------
ejercicio01.cpp
----------------------------------------------------

UNIVERSIDAD DEL VALLE DE GUATEMALA
FACULTAD DE INGENIERIA
DEPARTAMENtO DE CIENCIAS DE LA COMPUTACIÓN

---------------------------------------------------

Descripción: calcular los numeros divisibles entre 
2, 3 y 5 para un rango de numeros definidos por el 
usuario y con la cantidad de hilos definida por el 
usuario.

---------------------------------------------------

*/

#include <pthread.h>
#include <iostream>

using namespace std;

//definir la estructura para los parametros de la funcion
struct ThreadData {
    long threadID;
    int numCalc;
};



void* calc_divisibilidad(void* arg){

    ThreadData* data = (ThreadData*)arg;


    long tID = data->threadID;
    int numCalc = data->numCalc;

    cout << "Hilo " << tID << " procesando hasta el número " << numCalc << endl;

    return nullptr;
}


int main(){

    //variables a usar
    long i;
    int numCalc,numThreads, rc;

    //declaracion de variables para los hilos junto a los atributos
    pthread_t tid;

    pthread_attr_t attr;

    pthread_attr_init(&attr);

    pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_JOINABLE);

    //preguntas al usuario
    cout<<"Ingrese el numero máximo para calcular"<<endl;
    cin>>numCalc;
    cout<<"Ingrese la cantidad de hilos a usar"<<endl;
    cin>>numThreads;

    pthread_t tids[numThreads];
    ThreadData threadData[numThreads];

    //creacion de los hilos
    for(i=0; i<numThreads; i++){
        
        threadData[i].threadID = i;
        threadData[i].numCalc = numCalc;

        rc = pthread_create(&tids[i],&attr,calc_divisibilidad,(void *)&threadData[i]);



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


