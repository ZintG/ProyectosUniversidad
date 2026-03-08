#ifndef LISTA_H
#define LISTA_H

#include<iostream>

//Clase nodoDoble para listas doblemente enlazadas
template<class element>

class nodoDoble{
    private:
        element data;
        nodoDoble<element> *next, *previous;

    public:

    nodoDoble(element data): data(data), next(NULL), previous(NULL){}

    element getData() const;

    void setData(element d);

    void setNext(nodoDoble<element>* n);

    nodoDoble<element>* getNext() const;

    void setPrevious(nodoDoble<element>* p);

    nodoDoble<element>* getPrevious() const;

    ~nodoDoble(){}

};

template<class element>
element nodoDoble<element>::getData() const{
    return this->data;
}

template<class element>
void nodoDoble<element>::setData(element d){
    this->data=d;
}

template<class element>
void nodoDoble<element>::setNext(nodoDoble<element>* n){
    this->next=n;
}

template<class element>
nodoDoble<element>* nodoDoble<element>::getNext() const{
    return this->next;
}

template<class element>
nodoDoble<element>* nodoDoble<element>::getPrevious() const{
    return this->previous;
}

template<class element>
void nodoDoble<element>::setPrevious(nodoDoble<element>* p){
    this->previous=p;
}

//Clase Nodo para listas simplemente enlazadas

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

//Clase Lista simplemente enlazada

template<class element>
class lista{
    private:
        nodo<element> *primero, *ultimo;
        int n;
    public:
        lista(): primero(NULL), ultimo(NULL), n(0){}

        ///Constructor de copia profunda
        lista (const lista<element> &l);

        ///Obtener tamaño de la lista
        int getN() const;

        ///Insertar elemento en la posición pos>=1
        void insertar(element e, int pos);

        ///Consultar elemento en la posición pos>=1 y pos<=n
        element consultar(int pos) const;

        ///Eliminar elemento en la posición pos>=1
        void eliminar(int pos);

        ///retorna la posición del elemento e, si no se encuentra retorna -1
        int buscar(element e) const;

        ///Retorna una lista nueva con elementos de l invertidos
        lista<element> invertir(const lista<element> &l);

        /// Vacia la lista
        void vaciar();

        bool esVacia() const;

        ///Intercambia los elementos en las posiciones pos1 y pos2
        void intercambiar(int pos1, int pos2);

        ///Concatena la lista l2 al final de la lista actual
        void concatenar(const lista<element> &l2);

        lista<element>& operator=(const lista<element> &l);

        ~lista(){
            this->vaciar();
        }
};

template<class element>
lista<element>::lista(const lista<element> &l){
    this->n=l.n;
    if(l.esVacia()){
        this->primero=NULL;
        this->ultimo=NULL;
    }else{
        nodo<element> *aux1, *aux2;

        aux1=l.primero;
        aux2= new nodo<element>(aux1->getData());
        this->primero=aux2;
        aux1=aux1->getNext();
        while(aux1){
            aux2->setNext(new nodo<element>(aux1->getData()));
            aux2=aux2->getNext();
            aux1=aux1->getNext();
        }
        this->ultimo=aux2;
    }
}

template<class element>
int lista<element>::getN() const{
    return this->n;
}

template<class element>
void lista<element>::insertar(element e, int pos){
    if(pos==1){
        nodo<element> *nuevo= new nodo<element>(e);
        nuevo->setNext(this->primero);
        this->primero=nuevo;
        if(this->n==0){
            this->ultimo=nuevo;
        }
    }else if(pos>n){
        nodo<element> *nuevo= new nodo<element>(e);
        if(this->ultimo){
            this->ultimo->setNext(nuevo);
        }
        this->ultimo=nuevo;
        if(!this->primero){
            this->primero=nuevo;
        }
    }else{
        nodo<element> *nuevo= new nodo<element>(e);
        nodo<element> *aux=this->primero;
        for(int i=1; i<pos-1; i++){
            aux=aux->getNext();
        }
        nuevo->setNext(aux->getNext());
        aux->setNext(nuevo);
    }
    if(!(pos<1)){
        this->n++;
    }
}

template<class element>
element lista<element>::consultar(int pos) const{
    if(pos>=1 && pos<=this->n){
        nodo<element> *aux=this->primero;
        for(int i=1; i<pos; i++){
            aux=aux->getNext();
        }
        return aux->getData();
    }
}

template<class element>
void lista<element>::eliminar(int pos){
    if(pos==1){
        nodo<element> *aux=this->primero;
        this->primero=this->primero->getNext();
        delete aux;
    }else{
        nodo<element> *aux=this->primero;
        for(int i=1; i<pos-1; i++){
            aux=aux->getNext();
        }
        nodo<element> *aux2=aux->getNext();
        aux->setNext(aux2->getNext());
        if(pos==this->n){
            this->ultimo=aux;
        }
        delete aux2;
    }
    this->n--;

    if(this->n==0){
        this->ultimo=NULL;
        this->primero=NULL;
    }
}

template<class element>
int lista<element>::buscar(element e) const{
    nodo<element> *aux=this->primero;
    int pos=1;
    while(aux){
        if(aux->getData()==e){
            return pos;
        }
        aux=aux->getNext();
        pos++;
    }
    return -1;
}

template<class element>
lista<element> lista<element>::invertir(const lista<element> &l){
    lista<element> l2;
    nodo<element> *aux=l.primero;
    while(aux){
        l2.insertar(aux->getData(), 1);
        aux=aux->getNext();
    }
    return l2;
}

template<class element>
void lista<element>::vaciar(){
    nodo<element> *aux=this->primero;
    while(aux){
        nodo<element> *aux2=aux;
        aux=aux->getNext();
        delete aux2;
    }
    this->primero=NULL;
    this->ultimo=NULL;
    this->n=0;
}

template<class element>
bool lista<element>::esVacia() const{
    if(this->n==0){
        return true;
    }else{
        return false;
    }
}

template<class element>
void lista<element>::intercambiar(int pos1, int pos2){
    if(pos1>=1 && pos1<=this->n && pos2>=1 && pos2<=this->n){
        nodo<element> *aux1=this->primero;
        for(int i=1; i<pos1; i++){
            aux1=aux1->getNext();
        }
        nodo<element> *aux2=this->primero;
        for(int i=1; i<pos2; i++){
            aux2=aux2->getNext();
        }
        element temp=aux1->getData();
        aux1->setData(aux2->getData());
        aux2->setData(temp);
    }
}

template<class element>
void lista<element>::concatenar(const lista<element> &l2){
    nodo<element> *aux=l2.primero;    
    while(aux){
        this->insertar(aux->getData(), this->n+1);
        aux=aux->getNext();
    }
}

template<class element>
lista<element>& lista<element>::operator=(const lista<element> &l){
    if(this!=&l){
        this->vaciar();

        nodo<element> *aux=l.primero;
        while(aux){
            this->insertar(aux->getData(), this->n+1);
            aux=aux->getNext();
        }
    }
    return *this;
}

//Clase Lista doblemente enlazada

template<class element>
    class listaDoble{
    private:
        nodoDoble<element> *primero, *ultimo;
        int n;
    public:
        listaDoble(): primero(NULL), ultimo(NULL), n(0){}

        ///Constructor de copia profunda
        listaDoble (const listaDoble<element> &l);

        ///Obtener tamaño de la lista
        int getN() const;

        ///Insertar elemento en la posición pos>=1
        void insertar(element e, int pos);

        ///Consultar elemento en la posición pos>=1 y pos<=n
        element consultar(int pos) const;

        ///Eliminar elemento en la posición pos>=1
        void eliminar(int pos);

        ///retorna la posición del elemento e, si no se encuentra retorna -1
        int buscar(element e) const;

        ///Retorna una lista nueva con elementos de l invertidos
        listaDoble<element> invertir(const listaDoble<element> &l);

        ///Vacia la lista
        void vaciar();

        bool esVacia() const;

        ///Intercambia los elementos en las posiciones pos1 y pos2
        void intercambiar(int pos1, int pos2);

        ///Concatena la lista l2 al final de la lista actual
        void concatenar(const listaDoble<element> &l2);

        /*
        void hacerCircular();

        void deshacerCircular();

        Estos metodos no son compatibles con buscar ni invertir en su forma actual, solo usar si es necesario.
        */
        listaDoble<element>& operator=(const listaDoble<element> &l);

        ~listaDoble(){
            this->vaciar();
        }
    };

template<class element>
listaDoble<element>::listaDoble(const listaDoble<element> &l){
    this->n=l.n;
    if(l.esVacia()){
        this->primero=NULL;
        this->ultimo=NULL;
    }else{
        nodoDoble<element> *aux1, *aux2;

        aux1=l.primero;
        aux2= new nodoDoble<element>(aux1->getData());
        this->primero=aux2;
        aux1=aux1->getNext();
        while(aux1){
            aux2->setNext(new nodoDoble<element>(aux1->getData()));
            aux2->getNext()->setPrevious(aux2);
            aux2=aux2->getNext();
            aux1=aux1->getNext();
        }
        this->ultimo=aux2;
    }
}

template<class element>
int listaDoble<element>::getN() const{
    return this->n;
}

template<class element>
void listaDoble<element>::insertar(element e, int pos){
    if(pos==1){
        nodoDoble<element> *nuevo= new nodoDoble<element>(e);
        nuevo->setNext(this->primero);
        if(this->primero){
            this->primero->setPrevious(nuevo);
        }
        this->primero=nuevo;
        if(this->n==0){
            this->ultimo=nuevo;
        }
    }else if(pos>n){
        nodoDoble<element> *nuevo= new nodoDoble<element>(e);
        nuevo->setPrevious(this->ultimo);
        if(this->ultimo){
            this->ultimo->setNext(nuevo);
        }
        this->ultimo=nuevo;
        if(!this->primero){
            this->primero=nuevo;
        }
    }else{
        nodoDoble<element> *nuevo= new nodoDoble<element>(e);
        nodoDoble<element> *aux=this->primero;
        for(int i=1; i<pos-1; i++){
            aux=aux->getNext();
        }
        nuevo->setNext(aux->getNext());
        nuevo->setPrevious(aux);
        aux->getNext()->setPrevious(nuevo);
        aux->setNext(nuevo);
    }
    if(!(pos<1)){
        this->n++;
    }
}

template<class element>
element listaDoble<element>::consultar(int pos) const{
    if(pos>=1 && pos<= this->n){
        int mitad=this->n/2;
        nodoDoble<element> *aux;
        if(pos<=mitad){
            aux=this->primero;
            for(int i=1; i<pos; i++){
                aux=aux->getNext();
            }
            return aux->getData();
        }else{
            aux=this->ultimo;
            for(int i=1; i< this->n-pos+1; i++){
                aux=aux->getPrevious();
            }
            return aux->getData();
        }
    }
}

template<class element>
void listaDoble<element>::eliminar(int pos){
    if(pos==1){
        nodoDoble<element> *aux=this->primero;
        this->primero=this->primero->getNext();
        if(this->primero){
            this->primero->setPrevious(NULL);
        }
        delete aux;
    }else{
        nodoDoble<element> *aux=this->primero;
        for(int i=1; i<pos-1; i++){
            aux=aux->getNext();
        }
        nodoDoble<element> *aux2=aux->getNext();
        aux->setNext(aux2->getNext());
        if(aux2->getNext()){
            aux2->getNext()->setPrevious(aux);
        }
        if(pos==this->n){
            this->ultimo=aux;
            this->ultimo->setNext(NULL);
        }
        delete aux2;
    }
    this->n--;

    if(this->n==0){
        this->ultimo=NULL;
        this->primero=NULL;
    }
}

template<class element>
int listaDoble<element>::buscar(element e) const{
    nodoDoble<element> *aux=this->primero;
    int pos=1;
    while(aux){
        if(aux->getData()==e){
            return pos;
        }
        aux=aux->getNext();
        pos++;
    }
    return -1;
}

template<class element>
listaDoble<element> listaDoble<element>::invertir(const listaDoble<element> &l){
    listaDoble<element> l2;
    nodoDoble<element> *aux=l.primero;
    while(aux){
        l2.insertar(aux->getData(), 1);
        aux=aux->getNext();
    }
    return l2;
}

template<class element>
void listaDoble<element>::vaciar(){
    nodoDoble<element> *aux=this->primero;
    while(aux){
        nodoDoble<element> *aux2=aux;
        aux=aux->getNext();
        delete aux2;
    }
    this->primero=NULL;
    this->ultimo=NULL;
    this->n=0;
}

template<class element>
bool listaDoble<element>::esVacia() const{
    if(this->n==0){
        return true;
    }else{
        return false;
    }
}

template<class element>
void listaDoble<element>::intercambiar(int pos1, int pos2){
    if(pos1>=1 && pos1<=this->n && pos2>=1 && pos2<=this->n){
        nodoDoble<element> *aux1=this->primero;
        for(int i=1; i<pos1; i++){
            aux1=aux1->getNext();
        }
        nodoDoble<element> *aux2=this->primero;
        for(int i=1; i<pos2; i++){
            aux2=aux2->getNext();
        }
        element temp=aux1->getData();
        aux1->setData(aux2->getData());
        aux2->setData(temp);
    }
}

template<class element>
void listaDoble<element>::concatenar(const listaDoble<element> &l2){
    nodoDoble<element> *aux=l2.primero;    
    while(aux){
        this->insertar(aux->getData(), this->n+1);
        aux=aux->getNext();
    }
}
/*
template<class element>
void listaDoble<element>::hacerCircular(){
    if(this->n >0){
        this->ultimo->setNext(this->primero);
        this->primero->setPrevious(this->ultimo);
    }
}

template<class element>
void listaDoble<element>::deshacerCircular(){
    if(this->n >0){
        this->ultimo->setNext(NULL);
        this->primero->setPrevious(NULL);
    }
}
*/
template<class element>
listaDoble<element>& listaDoble<element>::operator=(const listaDoble<element> &l){
    if(this!=&l){
        this->vaciar();
        nodoDoble<element> *aux=l.primero;
        while(aux){
            this->insertar(aux->getData(), this->n+1);
            aux=aux->getNext();
        }
    }
    return *this;
}

#endif