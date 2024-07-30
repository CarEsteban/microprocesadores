#include <iostream> // Inclusión de la biblioteca estándar

using namespace std;

int main() {
    int var = 5;
    int *ptr = &var;
    //valor
    cout<<*ptr<<endl;
    //direccion
    cout<<ptr<<endl;

}
