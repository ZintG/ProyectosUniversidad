#include<iostream>
#include "listas.hpp"

using namespace std;

int main(){
    string saludo="Hola Mundo";
    nodo<int> n(5);
    cout<<n.getData()<<endl;
    cout<<saludo<<endl;
    lista<int> l;
    l.insertar(5, 1);
    getchar();

    return 0;
}