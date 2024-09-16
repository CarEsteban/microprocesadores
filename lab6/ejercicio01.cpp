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
#include <stdlib.h>
#include <stdio.h>

using namespace std;

//definir la estructura para los parametros de la funcion
struct ThreadData {
    long threadID;
    int inicio;
    int fin;
};



void* calc_divisibilidad(void* arg){

    ThreadData* data = (ThreadData*)arg;


    int tID = data->threadID;
    int inicio = data->inicio;
    int fin = data->fin;

    printf("Hilo %d procesando números de %d a %d\n", tID, inicio, fin);

    //divisible o no entre 2, 3 y 5
    for (int i = inicio; i <= fin; i++) {
        // Verifica si es divisible por 2, 3 y 5
        if (i % 2 == 0 && i % 3 == 0 && i % 5 == 0) {
            printf("Hilo %d: %d es divisible por 2, 3 y 5\n", tID, i);
        }
        // Verifica si es divisible por 2 y 3
        else if (i % 2 == 0 && i % 3 == 0) {
            printf("Hilo %d: %d es divisible por 2 y 3\n", tID, i);
        }
        // Verifica si es divisible por 2 y 5
        else if (i % 2 == 0 && i % 5 == 0) {
            printf("Hilo %d: %d es divisible por 2 y 5\n", tID, i);
        }
        // Verifica si es divisible por 3 y 5
        else if (i % 3 == 0 && i % 5 == 0) {
            printf("Hilo %d: %d es divisible por 3 y 5\n", tID, i);
        }
        // Verifica si es divisible por 2
        else if (i % 2 == 0) {
            printf("Hilo %d: %d es divisible por 2\n", tID, i);
        }
        // Verifica si es divisible por 3
        else if (i % 3 == 0) {
            printf("Hilo %d: %d es divisible por 3\n", tID, i);
        }
        // Verifica si es divisible por 5
        else if (i % 5 == 0) {
            printf("Hilo %d: %d es divisible por 5\n", tID, i);
        }
    }




    return nullptr;
}


int main(){

    //variables a usar
    long i;
    int numCalc,numThreads, rc;

    //declaracion de variables para los hilos junto a los atributos
    
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


    //calculo para dividir la cantidad de numeros en los hilos
    int rangoPorHilo = numCalc / numThreads;
    int resto = numCalc % numThreads;

    int inicio = 0;
    //creacion de los hilos
    for(i=0; i<numThreads; i++){
        
        threadData[i].threadID = i;
        threadData[i].inicio = inicio;
        threadData[i].fin = inicio+ rangoPorHilo - 1;

        //para los sobrantes
        if(resto>0){
            threadData[i].fin+=1;
            resto--;
        }

        inicio = threadData[i].fin + 1 ;

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


