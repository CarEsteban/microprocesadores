/*---------------------------------------
* UNIVERSIDAD DEL VALLE DE GUATEMALA
* Sistemas Operativos
* Autor: Esteban Cárcamo, Nicolás Concuá
* Fecha: 2024/09/24
*
* ---------------------------------------
* Variables de condición p/acceder a 
* region crítica 
* variables de condición.
*----------------------------------------
*/

#include <stdio.h>
#include <pthread.h>
#include <string>
 
using namespace std;

pthread_mutex_t candado;
pthread_cond_t cond;
bool julioComp = false;

struct Producto {
    string nombre;
    double precioUnitario;
    double costoFijo;
    string mes1 ;
    int vendidoMes1;
    string mes2;
    int vendidoMes2;
};

struct Resultados{
    double ventasJulio;
    double utilidadJulio;
    double ventasAgosto;
    double utilidadAgosto;
};

//pasar multiples parametros a args

struct Args{
    Producto *producto;
    Resultados *resultados;
};

void *calc_products(void *args){

    Args *data = (Args*)args;
    Producto *producto = data -> producto;
    Resultados *resultados = data -> resultados;

    pthread_mutex_lock(&candado);
    
}



int main()
{

    Producto productos[8] = {
        /*nombre producto, precio unitario, costo fijo, mes, unidades vendidas */
        {"Porción pastel de chocolate", 60.00, 20.00, "julio", 300, "agosto", 250},
        {"White mocha", 32.00, 19.20, "julio", 400, "agosto", 380},
        {"Café americano 8onz", 22, 13.20, "julio", 1590, "agosto", 800},
        {"Latte 8onz", 24.00, 17.20,"julio", 200, "agosto", 250},
        {"Toffee coffee", 28, 20.10,"julio", 390, "agosto", 600},
        {"Cappuccino 8onz", 24,17.20,"julio", 1455, "agosto", 1200},
        {"S'mores Latte", 32, 23,"julio", 800, "agosto", 1540},
        {"Café tostado molido", 60.00, 20.00,"julio", 60, "agosto", 15} 
    }; 

    int cantidadProductos = 8,i;

    pthread_t ids[cantidadProductos];

    //declaracion de variables para los hilos junto a los atributos
    
    pthread_attr_t attr;

    pthread_attr_init(&attr);

    pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_JOINABLE);

	pthread_mutex_init(&candado, NULL);
	pthread_cond_init(&cond, NULL);

    for ( i = 0; i < cantidadProductos; i++)
    {
        pthread_create(&ids[i], &attr, calc_products, (void *)&productos[i]);

    }
    

    


    return 0;
}
