#ifndef Pila_H
#define Pila_H

#include<iostream>

//Clase NodoP
template<class element>
class NodoP{
    private:
        element data;
        NodoP<element> *next;

    public:

    NodoP(element data): data(data), next(NULL){}

    element getData() const;

    void setData(element d);

    void setNext(NodoP<element>* n);

    NodoP<element>* getNext() const;

    ~NodoP(){}

};

template<class element>
element NodoP<element>::getData() const{
    return this->data;
}

template<class element>
void NodoP<element>::setData(element d){
    this->data=d;
}

template<class element>
void NodoP<element>::setNext(NodoP<element>* n){
    this->next=n;
}

template<class element>
NodoP<element>* NodoP<element>::getNext() const{
    return this->next;
}

//Clase Pila

template<class element>
class Pila{
    private:
        NodoP<element> *tope;
        int n;

    public:

    Pila(): tope(NULL), n(0){}

    ///Constructor copia clase Pila
    Pila(const Pila<element> &p);
    
    void aPilar(element e);

    void desaPilar();

    bool esVacia() const;

    ///obtener cantidad de elementos
    int getN() const;

    ///obtener tope
    element getTope() const;
    
    void vaciar();

    Pila<element>& operator=(const Pila<element> &p);

    ~Pila(){
        this->vaciar();
    }
};

template<class element>
Pila<element>& Pila<element>::operator=(const Pila<element> &p){
    if(this!=&p){
        this->vaciar();

        if(!p.esVacia()){
            NodoP<element> *aux, *nuevo;

            aux=p.tope;
            nuevo=new NodoP<element>(aux->getData());
            this->tope=nuevo;
            aux=aux->getNext();
        
            while (aux){
                nuevo->setNext(new NodoP<element>(aux->getData()));
                nuevo=nuevo->getNext();
                aux=aux->getNext();
            }
        
        }else{
            this->tope=NULL;
        }
        this->n=p.n;
        
    }
    return *this;
};

template<class element>
Pila<element>::Pila(const Pila<element> &p){
    if(!p.esVacia()){
        NodoP<element> *aux, *nuevo;

        aux=p.tope;
        nuevo=new NodoP<element>(aux->getData());
        this->tope=nuevo;
        aux=aux->getNext();
        
        while (aux){
            nuevo->setNext(new NodoP<element>(aux->getData()));
            nuevo=nuevo->getNext();
            aux=aux->getNext();
        }
        
    }else{
        this->tope=NULL;
    }
    this->n=p.n;
}

template<class element>
void Pila<element>::aPilar(element e){
    NodoP<element> *nuevo= new NodoP<element>(e);

    nuevo->setNext(this->tope);
    this->tope=nuevo;
    this->n++;
}

template<class element>
void Pila<element>::desaPilar(){
    NodoP<element> *aux;

    aux=this->tope;

    this->tope=aux->getNext();
    delete aux;

    this->n--;

    if(this->n==0){
        this->tope=NULL;
    }
}

template<class element>
bool Pila<element>::esVacia() const{
    if(this->n > 0){
        return false;
    }else{
        return true;
    }
}

template<class element>
int Pila<element>::getN() const{
    return this->n;
}

template<class element>
element Pila<element>::getTope() const{
    return this->tope->getData();
}

template<class element>
void Pila<element>::vaciar(){
    NodoP<element> *aux=this->tope;
    
    while(aux){
        NodoP<element> *aux2=aux;
        aux=aux->getNext();
        
        delete aux2;
    }

    this->tope=NULL;
    this->n=0;
}

#endif