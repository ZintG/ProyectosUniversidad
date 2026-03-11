#include<iostream>
#include "lista.hpp"

using namespace std;

int main(){

    listaDoble<int> testCircular;

    int pos=1;
    for(int i=4; i<=10; i++){
        testCircular.insertar(i, pos);
        pos++;
    }

    cout<<"La lista tiene los elementos: ";

    for(int i=1; i<=testCircular.getN(); i++){
        if(i<testCircular.getN()){
            cout<<testCircular.consultar(i)<<" ,";
        }else{
            cout<<testCircular.consultar(i)<<"."<<endl;
        }
    }
    
    testCircular.hacerCircular();
    cout<<"La lista tiene los elementos: ";

    int numaux=testCircular.getN()+(testCircular.getN() /2);
    int indice2=1;

    for(int i=1; i<=numaux; i++){
        if(i<=testCircular.getN()){
            cout<<testCircular.consultar(i)<<" ,";
        }else{
            cout<<testCircular.consultar(indice2)*2<<" ";
            indice2++;
        }
    }
    cout<<endl;

    cout<<"el numero 4 esta en la posicion "<<testCircular.buscar(4)<<endl;

    listaDoble<int> testCircular2= testCircular2.invertir( testCircular);

    cout<<"La lista invertida tiene los elementos: ";

    for(int i=1; i<=testCircular2.getN(); i++){
        if(i<testCircular2.getN()){
            cout<<testCircular2.consultar(i)<<" ,";
        }else{
            cout<<testCircular2.consultar(i)<<" ."<<endl;
        }
    }

    return 0;
}