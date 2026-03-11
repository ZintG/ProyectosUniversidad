#ifndef PILA_H
#define PILA_H

#include<iostream>

//Clase nodop
template<class element>
class nodop{
    private:
        element data;
        nodop<element> *next;

    public:

    nodop(element data): data(data), next(NULL){}

    element getData() const;

    void setData(element d);

    void setNext(nodop<element>* n);

    nodop<element>* getNext() const;

    ~nodop(){}

};

template<class element>
element nodop<element>::getData() const{
    return this->data;
}

template<class element>
void nodop<element>::setData(element d){
    this->data=d;
}

template<class element>
void nodop<element>::setNext(nodop<element>* n){
    this->next=n;
}

template<class element>
nodop<element>* nodop<element>::getNext() const{
    return this->next;
}

//Clase Pila

template<class element>
class pila{
    private:
        nodop<element> *tope;
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
            nodop<element> *aux, *nuevo;

            aux=p.tope;
            nuevo=new nodop<element>(aux->getData());
            this->tope=nuevo;
            aux=aux->getNext();
        
            while (aux){
                nuevo->setNext(new nodop<element>(aux->getData()));
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
        nodop<element> *aux, *nuevo;

        aux=p.tope;
        nuevo=new nodop<element>(aux->getData());
        this->tope=nuevo;
        aux=aux->getNext();
        
        while (aux){
            nuevo->setNext(new nodop<element>(aux->getData()));
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
    nodop<element> *nuevo= new nodop<element>(e);

    nuevo->setNext(this->tope);
    this->tope=nuevo;
    this->n++;
}

template<class element>
void pila<element>::desapilar(){
    nodop<element> *aux;

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
    nodop<element> *aux=this->tope;
    
    while(aux){
        nodop<element> *aux2=aux;
        aux=aux->getNext();
        
        delete aux2;
    }

    this->tope=NULL;
    this->n=0;
}

#endif