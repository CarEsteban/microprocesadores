#include <iostream>

using namespace std;

int main(){
    int num1;
    int num2;
    
    cout << "Ingrese el primer numero entero" << endl; 
    cin >> num1;
    cout << "Ingrese el segundo numero entero" << endl; 
    cin >> num2;

    int *ptr1 = &num1;
    int *ptr2 = &num2;

    int suma = *ptr1 + *ptr2;
    int producto = *ptr1 * *ptr2;

    cout << "Numero 1: " << num1 << " -- Puntero: " << *ptr1 << endl;
    cout << "Numero 2: " << num2 << " -- Puntero: " << *ptr2 << endl;

    // Intercambio de valores usando punteros
    int temp = *ptr1;
    *ptr1 = *ptr2;
    *ptr2 = temp;

    cout << "Despues del intercambio:" << endl;
    cout << "Primer numero: " << num1 << endl;
    cout << "Segundo numero: " << num2 << endl;
    cout << "La suma de los numeros es: " << suma << endl;
    cout << "El producto de los numeros es: " << producto << endl;
    
    // Determinar el mayor número
    int mayor = (num1 > num2) ? num1 : num2;
    cout << "El mayor numero es: " << mayor << endl;

    return 0;
}
