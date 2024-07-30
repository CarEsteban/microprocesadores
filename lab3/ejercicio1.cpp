#include <iostream>

using namespace std;

int main() {
    int dato;

    cout<<"Ingrese un numero entre 0 y 35"<<endl;
    cin>>dato;

    if (dato<0 || dato>35){
        cout<<"Numero no válido"<<endl;
    }
    
    if (dato<=9){
        cout<<dato<<endl;
    }else{
        int numletra = dato + 55;
        char letra = static_cast<char>(numletra);

        cout<<letra<<", valor:"<<dato<<endl;
    }
    




    return 0;
}