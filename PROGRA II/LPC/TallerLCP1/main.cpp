#include<iostream>
#include<string>
#include<cstdio>
#include"lista.hpp"

using namespace std;

class Participante{
    private:
        string nombre;
        int numero;
    public:
        Participante(string n, int num): nombre(n), numero(num){}

        string getNombre(){
            return nombre;
        }

        int getNumero(){
            return numero;
        }
};

//procedimiento para leer los nombres de los participantes
void leerLista(Lista<Participante> &l);

void eliminarDelCirculo(Lista<Participante> &l, int &posicionInicial, int &posicionOriginalEliminado, int pasosAvanzar, int &sentido);

int main(){
    int n, k, p, q;


    cin>>n;

    for(int i=1; i<=n; i++){

        cin>>k;
        cin>>p;
        cin>>q;

        Lista<Participante> circulo;

        //limpiar buffer antes de leer la lista
        while(getchar()!='\n');

        leerLista(circulo);

        int posicion=1;
        bool flagPrimerCiclo=true;
        int sentido=1;
        int posicionOriginalEliminado;


        while(circulo.getN()>1){
            if(flagPrimerCiclo){
                eliminarDelCirculo(circulo, posicion, posicionOriginalEliminado, k, sentido);
            }else{
                if(posicionOriginalEliminado%2==0){
                    eliminarDelCirculo(circulo, posicion, posicionOriginalEliminado, p, sentido);
                }else{
                    eliminarDelCirculo(circulo, posicion, posicionOriginalEliminado, q, sentido);
                }
            }
            flagPrimerCiclo=false;
        }
        Participante ganador=circulo.consultar(1);
        if(i<n){
            cout<<ganador.getNombre()<<endl;
        }else{
            cout<<ganador.getNombre()<<endl;
        }
        circulo.vaciar();

    }
}

void leerLista(Lista<Participante> &l){
    char aux;

    int i=1;

    while(((aux=cin.get()) != '\n')&& aux!=EOF){
        if(aux=='"'){
            string nombre;
            while(((aux=cin.get())!='"') && aux!=EOF){
                nombre+=aux;
            }
            Participante p(nombre, i);
            l.insertar(p, i);
            i++;
        }
    }
}

void eliminarDelCirculo(Lista<Participante> &l, int &posicionInicial, int &posicionOriginalEliminado, int pasosAvanzar, int &sentido){
    int desplazamiento;
    if(sentido<0){
        pasosAvanzar*=-1;
        desplazamiento=pasosAvanzar+1;
    }else{
        desplazamiento=pasosAvanzar-1;
    }
    int posicionNueva=(((posicionInicial-1+desplazamiento)%l.getN())+l.getN())%l.getN()+1;

    Participante p=l.consultar(posicionNueva);
    posicionOriginalEliminado=p.getNumero();
    l.eliminar(posicionNueva);
    posicionInicial=posicionNueva;
    sentido*=-1;
}