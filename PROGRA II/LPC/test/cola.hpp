#ifndef Cola_H
#define Cola_H

#include<iostream>

//Clase NodoC
template<class element>
class NodoC{
    private:
        element data;
        NodoC<element> *next;

    public:

    NodoC(element data): data(data), next(NULL){}

    element getData() const;

    void setData(element d);

    void setNext(NodoC<element>* n);

    NodoC<element>* getNext() const;

    ~NodoC(){}

};

template<class element>
element NodoC<element>::getData() const{
    return this->data;
}

template<class element>
void NodoC<element>::setData(element d){
    this->data=d;
}

template<class element>
void NodoC<element>::setNext(NodoC<element>* n){
    this->next=n;
}

template<class element>
NodoC<element>* NodoC<element>::getNext() const{
    return this->next;
}

//Clase Cola
template<class element>
class Cola{
    private:
        NodoC<element> *primero, *ultimo;
        int n;
    public:

        Cola(): primero(NULL), ultimo(NULL), n(0){}

        Cola(const Cola<element> &c);

        element getPrimero() const;

        element getUltimo() const;

        void enColar(element e);

        void desenColar();

        bool esVacia() const;

        int getN() const;

        void vaciar();

        Cola<element>& operator=(const Cola<element> &c);

        ~Cola(){
            this->vaciar();
        }
};

template<class element>
Cola<element>::Cola(const Cola<element> &c){
    if(c.esVacia()){
        this->n=0;
        this->ultimo=NULL;
        this->primero=NULL;
    }else{
        NodoC<element> *aux=c.primero;

        while(aux){
            this->enColar(aux->getData());
            aux=aux->getNext();
        }
    }
}

template<class element>
Cola<element>& Cola<element>::operator=(const Cola<element> &c){
    if(this!= &c){
        this->vaciar();
        
        if(c.esVacia()){
            this->n=0;
            this->ultimo=NULL;
            this->primero=NULL;
        }else{
            NodoC<element> *aux=c.primero;

            while(aux){
                this->enColar(aux->getData());
                aux=aux->getNext();
            }
        }
    }
    return *this;
}

template<class element>
element Cola<element>::getPrimero() const{
    return this->primero->getData();
}

template<class element>
element Cola<element>::getUltimo() const{
    return this->ultimo->getData();
}

template<class element>
void Cola<element>::enColar(element e){
    NodoC<element> *nuevo;

    nuevo=new NodoC<element>(e);

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
void Cola<element>::desenColar(){
    NodoC<element> *aux=this->primero;

    this->primero=this->primero->getNext();
    delete aux;
    this->n--;

    if(this->n==0){
        this->ultimo=NULL;
        this->primero=NULL;
    }
}

template<class element>
bool Cola<element>::esVacia() const{
    if(n==0){
        return true;
    }
    return false;
}

template<class element>
int Cola<element>::getN() const{
    return this->n;
}

template<class element>
void Cola<element>::vaciar(){
    while(this->n >0){
        this->desenColar();
    }
}

#endif