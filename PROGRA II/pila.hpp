#ifndef PILA_H
#define PILA_H

#include<iostream>

//Clase Nodo
template<class element>
class nodo{
    private:
        element data;
        nodo<element> *next;

    public:

    nodo(element data): data(data), next(NULL){}

    element getData() const;

    void setData(element d);

    void setNext(nodo<element>* n);

    nodo<element>* getNext() const;

    ~nodo(){}

};

template<class element>
element nodo<element>::getData() const{
    return this->data;
}

template<class element>
void nodo<element>::setData(element d){
    this->data=d;
}

template<class element>
void nodo<element>::setNext(nodo<element>* n){
    this->next=n;
}

template<class element>
nodo<element>* nodo<element>::getNext() const{
    return this->next;
}

//Clase Pila

template<class element>
class pila{
    private:
        nodo<element> *tope;
        int n;

    public:

    pila(): tope(NULL), n(0){}

    ///Constructor copia clase pila
    pila(const pila<element> &p);
    
    void apilar(element e);

    void desapilar();

    bool esVacia() const;

    ///obtener cantidad de elementos
    int getN() const;

    ///obtener tope
    element getTope() const;
    
    void vaciar();

    pila<element>& operator=(const pila<element> &p);

    ~pila(){
        this->vaciar();
    }
};

template<class element>
pila<element>& pila<element>::operator=(const pila<element> &p){
    if(this!=&p){
        this->vaciar();

        if(!p.esVacia()){
            nodo<element> *aux, *nuevo;

            aux=p.tope;
            nuevo=new nodo<element>(aux->getData());
            this->tope=nuevo;
            aux=aux->getNext();
        
            while (aux){
                nuevo->setNext(new nodo<element>(aux->getData()));
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
pila<element>::pila(const pila<element> &p){
    if(!p.esVacia()){
        nodo<element> *aux, *nuevo;

        aux=p.tope;
        nuevo=new nodo<element>(aux->getData());
        this->tope=nuevo;
        aux=aux->getNext();
        
        while (aux){
            nuevo->setNext(new nodo<element>(aux->getData()));
            nuevo=nuevo->getNext();
            aux=aux->getNext();
        }
        
    }else{
        this->tope=NULL;
    }
    this->n=p.n;
}

template<class element>
void pila<element>::apilar(element e){
    nodo<element> *nuevo= new nodo<element>(e);

    nuevo->setNext(this->tope);
    this->tope=nuevo;
    this->n++;
}

template<class element>
void pila<element>::desapilar(){
    nodo<element> *aux;

    aux=this->tope;

    this->tope=aux->getNext();
    delete aux;

    this->n--;

    if(this->n==0){
        this->tope=NULL;
    }
}

template<class element>
bool pila<element>::esVacia() const{
    if(this->n > 0){
        return false;
    }else{
        return true;
    }
}

template<class element>
int pila<element>::getN() const{
    return this->n;
}

template<class element>
element pila<element>::getTope() const{
    return this->tope->getData();
}

template<class element>
void pila<element>::vaciar(){
    nodo<element> *aux=this->tope;
    
    while(aux){
        nodo<element> *aux2=aux;
        aux=aux->getNext();
        
        delete aux2;
    }

    this->tope=NULL;
    this->n=0;
}

#endif