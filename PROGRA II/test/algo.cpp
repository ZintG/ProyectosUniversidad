#include<iostream>
#include<cstdio>
#include "lista.hpp"
#include "cola.hpp"
#include "pila.hpp"

using namespace std;

int main(){
    string saludo="Hola Mundo";
    nodo<int> n(5);

    lista<int> l;

    pila<int> p;

    cola<int> c;

    l.insertar(1,1);

    p.apilar(2);

    c.encolar(3);
    
    cout<<"Lista: "<<l.consultar(1)<<endl;

    cout<<"Pila: "<<p.getTope()<<endl;

    cout<<"Cola: "<<c.getPrimero()<<endl;

    cout<<"Nodo: "<<n.getData()<<endl;
    cout<<saludo<<endl;

    getchar();

    return 0;
}