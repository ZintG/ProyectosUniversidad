#ifndef COLA_H
#define COLA_H

#include<iostream>

//Clase nodoc
template<class element>
class nodoc{
    private:
        element data;
        nodoc<element> *next;

    public:

    nodoc(element data): data(data), next(NULL){}

    element getData() const;

    void setData(element d);

    void setNext(nodoc<element>* n);

    nodoc<element>* getNext() const;

    ~nodoc(){}

};

template<class element>
element nodoc<element>::getData() const{
    return this->data;
}

template<class element>
void nodoc<element>::setData(element d){
    this->data=d;
}

template<class element>
void nodoc<element>::setNext(nodoc<element>* n){
    this->next=n;
}

template<class element>
nodoc<element>* nodoc<element>::getNext() const{
    return this->next;
}

//Clase Cola
template<class element>
class cola{
    private:
        nodoc<element> *primero, *ultimo;
        int n;
    public:

        cola(): primero(NULL), ultimo(NULL), n(0){}

        cola(const cola<element> &c);

        element getPrimero() const;

        element getUltimo() const;

        void encolar(element e);

        void desencolar();

        bool esVacia() const;

        int getN() const;

        void vaciar();

        cola<element>& operator=(const cola<element> &c);

        ~cola(){
            this->vaciar();
        }
};

template<class element>
cola<element>::cola(const cola<element> &c){
    if(c.esVacia()){
        this->n=0;
        this->ultimo=NULL;
        this->primero=NULL;
    }else{
        nodoc<element> *aux=c.primero;

        while(aux){
            this->encolar(aux->getData());
            aux=aux->getNext();
        }
    }
}

template<class element>
cola<element>& cola<element>::operator=(const cola<element> &c){
    if(this!= &c){
        this->vaciar();
        
        if(c.esVacia()){
            this->n=0;
            this->ultimo=NULL;
            this->primero=NULL;
        }else{
            nodoc<element> *aux=c.primero;

            while(aux){
                this->encolar(aux->getData());
                aux=aux->getNext();
            }
        }
    }
    return *this;
}

template<class element>
element cola<element>::getPrimero() const{
    return this->primero->getData();
}

template<class element>
element cola<element>::getUltimo() const{
    return this->ultimo->getData();
}

template<class element>
void cola<element>::encolar(element e){
    nodoc<element> *nuevo;

    nuevo=new nodoc<element>(e);

    if(this->ultimo){
        this->ultimo->setNext(nuevo);
    }
    this->ultimo=nuevo;
    if(!this->primero){
        this->primero=nuevo;
    }
    this->n++;
}

template<class element>
void cola<element>::desencolar(){
    nodoc<element> *aux=this->primero;

    this->primero=this->primero->getNext();
    delete aux;
    this->n--;

    if(this->n==0){
        this->ultimo=NULL;
        this->primero=NULL;
    }
}

template<class element>
bool cola<element>::esVacia() const{
    if(n==0){
        return true;
    }
    return false;
}

template<class element>
int cola<element>::getN() const{
    return this->n;
}

template<class element>
void cola<element>::vaciar(){
    while(this->n >0){
        this->desencolar();
    }
}

#endif