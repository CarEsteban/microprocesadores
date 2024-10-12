#include <pthread.h>
#include <semaphore.h>
#include <iostream>
#include <mutex>
#include <vector>

sem_t semaforo; //semaforo para controlar el acceso al cajero
double saldo = 100000.00; //saldo inicial 


struct  ClienteDatos
{
    int id;
    double monto;
};


using namespace std;


void* operacionCliente(void* arg){
    ClienteDatos* data = (ClienteDatos*)arg; //casteo

    sem_wait(&semaforo); //intentar acceder al cajero, bloquearlo si ya se está usando

    int idCliente = data->id;
    double montoCliente = data->monto;

    cout <<"Cliente: " <<idCliente<<" quiere retirar Q"<<montoCliente<<endl;
    
    //verificaciones
    if (saldo>=montoCliente)
    {
        saldo-=montoCliente;
        cout<<"Cliente: "<<idCliente<<" retiró exitosamente Q"<<montoCliente<<", Saldo restante: Q"<<saldo<<endl;
    }else{
        cout<<"Saldo (Q"<<saldo<<") insuficiente, Cliente: "<<idCliente<<" no puede restirar dinero :("<<endl;
    }
    
    sem_post(&semaforo); //liberar el cajero asi otro cliente accede

    pthread_exit(NULL);
}


int main(){
   int numClientes;
   cout <<"Ingrese el número de clientes"<<endl;
   cin >> numClientes;

   pthread_t hilos [numClientes];
   ClienteDatos clientes [numClientes];

   //Iniciar el semaforo
   sem_init (&semaforo, 0, 1);

   //solictiar monto  
   for (int i = 0; i < numClientes; i++)
   {
      cout << "Monto de retiro para el cliente "<< i + 1 << ":"<<endl;
      cin >> clientes[i].monto ;
      clientes[i].id = i+1;
   }
    

   //crear hilos
   for (int i = 0; i < numClientes; i++){
      pthread_create(&hilos[i], NULL, operacionCliente, (void*)&clientes[i]);
   }
   
   //Join
   for (int i = 0; i < numClientes; i++){
      pthread_join(hilos[i],NULL);
   }

   //Imprimir
   cout << "Saldo final: Q" << saldo << endl;
   
   sem_destroy(&semaforo);
   return 0;
}
