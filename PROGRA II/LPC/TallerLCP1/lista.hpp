#ifndef Lista_H
#define Lista_H

#include<iostream>

//Clase NodoDoble para Listas doblemente enlazadas
template<class element>

class NodoDoble{
    private:
        element data;
        NodoDoble<element> *next, *previous;

    public:

    NodoDoble(element data): data(data), next(NULL), previous(NULL){}

    element getData() const;

    void setData(element d);

    void setNext(NodoDoble<element>* n);

    NodoDoble<element>* getNext() const;

    void setPrevious(NodoDoble<element>* p);

    NodoDoble<element>* getPrevious() const;

    ~NodoDoble(){}

};

template<class element>
element NodoDoble<element>::getData() const{
    return this->data;
}

template<class element>
void NodoDoble<element>::setData(element d){
    this->data=d;
}

template<class element>
void NodoDoble<element>::setNext(NodoDoble<element>* n){
    this->next=n;
}

template<class element>
NodoDoble<element>* NodoDoble<element>::getNext() const{
    return this->next;
}

template<class element>
NodoDoble<element>* NodoDoble<element>::getPrevious() const{
    return this->previous;
}

template<class element>
void NodoDoble<element>::setPrevious(NodoDoble<element>* p){
    this->previous=p;
}

//Clase Nodo para Listas simplemente enlazadas

template<class element>

class Nodo{
    private:
        element data;
        Nodo<element> *next;

    public:

    Nodo(element data): data(data), next(NULL){}

    element getData() const;

    void setData(element d);

    void setNext(Nodo<element>* n);

    Nodo<element>* getNext() const;

    ~Nodo(){}

};

template<class element>
element Nodo<element>::getData() const{
    return this->data;
}

template<class element>
void Nodo<element>::setData(element d){
    this->data=d;
}

template<class element>
void Nodo<element>::setNext(Nodo<element>* n){
    this->next=n;
}

template<class element>
Nodo<element>* Nodo<element>::getNext() const{
    return this->next;
}

//Clase Lista simplemente enlazada

template<class element>
class Lista{
    private:
        Nodo<element> *primero, *ultimo;
        int n;
    public:
        Lista(): primero(NULL), ultimo(NULL), n(0){}

        ///Constructor de copia profunda
        Lista (const Lista<element> &l);

        ///Obtener tamaño de la Lista
        int getN() const;

        ///Insertar elemento en la posición pos>=1
        void insertar(element e, int pos);

        ///Consultar elemento en la posición pos>=1 y pos<=n
        element consultar(int pos) const;

        ///Eliminar elemento en la posición pos>=1
        void eliminar(int pos);

        ///retorna la posición del elemento e, si no se encuentra retorna -1
        int buscar(element e) const;

        ///Retorna una Lista nueva con elementos de l invertidos
        Lista<element> invertir(const Lista<element> &l);

        /// Vacia la Lista
        void vaciar();

        bool esVacia() const;

        ///Intercambia los elementos en las posiciones pos1 y pos2
        void intercambiar(int pos1, int pos2);

        ///Concatena la Lista l2 al final de la Lista actual
        void concatenar(const Lista<element> &l2);

        Lista<element>& operator=(const Lista<element> &l);

        ~Lista(){
            this->vaciar();
        }
};

template<class element>
Lista<element>::Lista(const Lista<element> &l){
    this->n=l.n;
    if(l.esVacia()){
        this->primero=NULL;
        this->ultimo=NULL;
    }else{
        Nodo<element> *aux1, *aux2;

        aux1=l.primero;
        aux2= new Nodo<element>(aux1->getData());
        this->primero=aux2;
        aux1=aux1->getNext();
        while(aux1){
            aux2->setNext(new Nodo<element>(aux1->getData()));
            aux2=aux2->getNext();
            aux1=aux1->getNext();
        }
        this->ultimo=aux2;
    }
}

template<class element>
int Lista<element>::getN() const{
    return this->n;
}

template<class element>
void Lista<element>::insertar(element e, int pos){
    if(pos==1){
        Nodo<element> *nuevo= new Nodo<element>(e);
        nuevo->setNext(this->primero);
        this->primero=nuevo;
        if(this->n==0){
            this->ultimo=nuevo;
        }
    }else if(pos>n){
        Nodo<element> *nuevo= new Nodo<element>(e);
        if(this->ultimo){
            this->ultimo->setNext(nuevo);
        }
        this->ultimo=nuevo;
        if(!this->primero){
            this->primero=nuevo;
        }
    }else{
        Nodo<element> *nuevo= new Nodo<element>(e);
        Nodo<element> *aux=this->primero;
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
element Lista<element>::consultar(int pos) const{
    if(pos>=1 && pos<=this->n){
        Nodo<element> *aux=this->primero;
        for(int i=1; i<pos; i++){
            aux=aux->getNext();
        }
        return aux->getData();
    }
}

template<class element>
void Lista<element>::eliminar(int pos){
    if(pos==1){
        Nodo<element> *aux=this->primero;
        this->primero=this->primero->getNext();
        delete aux;
    }else{
        Nodo<element> *aux=this->primero;
        for(int i=1; i<pos-1; i++){
            aux=aux->getNext();
        }
        Nodo<element> *aux2=aux->getNext();
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
int Lista<element>::buscar(element e) const{
    Nodo<element> *aux=this->primero;
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
Lista<element> Lista<element>::invertir(const Lista<element> &l){
    Lista<element> l2;
    Nodo<element> *aux=l.primero;
    while(aux){
        l2.insertar(aux->getData(), 1);
        aux=aux->getNext();
    }
    return l2;
}

template<class element>
void Lista<element>::vaciar(){
    Nodo<element> *aux=this->primero;
    while(aux){
        Nodo<element> *aux2=aux;
        aux=aux->getNext();
        delete aux2;
    }
    this->primero=NULL;
    this->ultimo=NULL;
    this->n=0;
}

template<class element>
bool Lista<element>::esVacia() const{
    if(this->n==0){
        return true;
    }else{
        return false;
    }
}

template<class element>
void Lista<element>::intercambiar(int pos1, int pos2){
    if(pos1>=1 && pos1<=this->n && pos2>=1 && pos2<=this->n){
        Nodo<element> *aux1=this->primero;
        for(int i=1; i<pos1; i++){
            aux1=aux1->getNext();
        }
        Nodo<element> *aux2=this->primero;
        for(int i=1; i<pos2; i++){
            aux2=aux2->getNext();
        }
        element temp=aux1->getData();
        aux1->setData(aux2->getData());
        aux2->setData(temp);
    }
}

template<class element>
void Lista<element>::concatenar(const Lista<element> &l2){
    Nodo<element> *aux=l2.primero;    
    while(aux){
        this->insertar(aux->getData(), this->n+1);
        aux=aux->getNext();
    }
}

template<class element>
Lista<element>& Lista<element>::operator=(const Lista<element> &l){
    if(this!=&l){
        this->vaciar();

        Nodo<element> *aux=l.primero;
        while(aux){
            this->insertar(aux->getData(), this->n+1);
            aux=aux->getNext();
        }
    }
    return *this;
}

//Clase Lista doblemente enlazada

template<class element>
    class ListaDoble{
    private:
        NodoDoble<element> *primero, *ultimo;
        int n;
    public:
        ListaDoble(): primero(NULL), ultimo(NULL), n(0){}

        ///Constructor de copia profunda
        ListaDoble (const ListaDoble<element> &l);

        ///Obtener tamaño de la Lista
        int getN() const;

        ///Insertar elemento en la posición pos>=1
        void insertar(element e, int pos);

        ///Consultar elemento en la posición pos>=1 y pos<=n
        element consultar(int pos) const;

        ///Eliminar elemento en la posición pos>=1
        void eliminar(int pos);

        ///retorna la posición del elemento e, si no se encuentra retorna -1
        int buscar(element e) const;

        ///Retorna una Lista nueva con elementos de l invertidos
        ListaDoble<element> invertir(const ListaDoble<element> &l);

        ///Vacia la Lista
        void vaciar();

        bool esVacia() const;

        ///Intercambia los elementos en las posiciones pos1 y pos2
        void intercambiar(int pos1, int pos2);

        ///Concatena la Lista l2 al final de la Lista actual
        void concatenar(const ListaDoble<element> &l2);

        /// Convierte la Lista en circular
        void hacerCircular();

        /// Desconecta el final del inicio en una Lista circular
        void deshacerCircular();

        ListaDoble<element>& operator=(const ListaDoble<element> &l);

        ~ListaDoble(){
            this->vaciar();
        }
    };

template<class element>
ListaDoble<element>::ListaDoble(const ListaDoble<element> &l){
    this->n=l.n;
    if(l.esVacia()){
        this->primero=NULL;
        this->ultimo=NULL;
    }else{
        NodoDoble<element> *aux1, *aux2;

        aux1=l.primero;
        aux2= new NodoDoble<element>(aux1->getData());
        this->primero=aux2;
        aux1=aux1->getNext();
        for(int i=2; i<=l.n; i++){
            aux2->setNext(new NodoDoble<element>(aux1->getData()));
            aux2->getNext()->setPrevious(aux2);
            aux2=aux2->getNext();
            aux1=aux1->getNext();
        }
        this->ultimo=aux2;
    }
}

template<class element>
int ListaDoble<element>::getN() const{
    return this->n;
}

template<class element>
void ListaDoble<element>::insertar(element e, int pos){
    if(pos==1){
        NodoDoble<element> *nuevo= new NodoDoble<element>(e);
        nuevo->setNext(this->primero);
        if(this->primero){
            this->primero->setPrevious(nuevo);
        }
        this->primero=nuevo;
        if(this->n==0){
            this->ultimo=nuevo;
        }
    }else if(pos>n){
        NodoDoble<element> *nuevo= new NodoDoble<element>(e);
        nuevo->setPrevious(this->ultimo);
        if(this->ultimo){
            this->ultimo->setNext(nuevo);
        }
        this->ultimo=nuevo;
        if(!this->primero){
            this->primero=nuevo;
        }
    }else{
        NodoDoble<element> *nuevo= new NodoDoble<element>(e);
        NodoDoble<element> *aux=this->primero;
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
element ListaDoble<element>::consultar(int pos) const{
    if(pos>=1 && pos<= this->n){
        int mitad=this->n/2;
        NodoDoble<element> *aux;
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
void ListaDoble<element>::eliminar(int pos){
    if(pos==1){
        NodoDoble<element> *aux=this->primero;
        this->primero=this->primero->getNext();
        if(this->primero){
            this->primero->setPrevious(NULL);
        }
        delete aux;
    }else{
        NodoDoble<element> *aux=this->primero;
        for(int i=1; i<pos-1; i++){
            aux=aux->getNext();
        }
        NodoDoble<element> *aux2=aux->getNext();
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
int ListaDoble<element>::buscar(element e) const{
    NodoDoble<element> *aux=this->primero;
    for(int i=1; i<=this->n; i++){
        if(aux->getData()==e){
            return i;
        }
        aux=aux->getNext();
    }
    return -1;
}

template<class element>
ListaDoble<element> ListaDoble<element>::invertir(const ListaDoble<element> &l){
    ListaDoble<element> l2;
    NodoDoble<element> *aux=l.primero;
    for(int i=1; i<=l.n; i++){
        l2.insertar(aux->getData(), 1);
        aux=aux->getNext();
    }
    return l2;
}

template<class element>
void ListaDoble<element>::vaciar(){
    NodoDoble<element> *aux=this->primero;
    for(int i=1; i<=this->n; i++){
        NodoDoble<element> *aux2=aux;
        aux=aux->getNext();
        delete aux2;
    }
    this->primero=NULL;
    this->ultimo=NULL;
    this->n=0;
}

template<class element>
bool ListaDoble<element>::esVacia() const{
    if(this->n==0){
        return true;
    }else{
        return false;
    }
}

template<class element>
void ListaDoble<element>::intercambiar(int pos1, int pos2){
    if(pos1>=1 && pos1<=this->n && pos2>=1 && pos2<=this->n){
        NodoDoble<element> *aux1=this->primero;
        for(int i=1; i<pos1; i++){
            aux1=aux1->getNext();
        }
        NodoDoble<element> *aux2=this->primero;
        for(int i=1; i<pos2; i++){
            aux2=aux2->getNext();
        }
        element temp=aux1->getData();
        aux1->setData(aux2->getData());
        aux2->setData(temp);
    }
}

template<class element>
void ListaDoble<element>::concatenar(const ListaDoble<element> &l2){
    NodoDoble<element> *aux=l2.primero;    
    while(aux){
        this->insertar(aux->getData(), this->n+1);
        aux=aux->getNext();
    }
}

template<class element>
void ListaDoble<element>::hacerCircular(){
    if(this->n >0){
        this->ultimo->setNext(this->primero);
        this->primero->setPrevious(this->ultimo);
    }
}

template<class element>
void ListaDoble<element>::deshacerCircular(){
    if(this->n >0){
        this->ultimo->setNext(NULL);
        this->primero->setPrevious(NULL);
    }
}

template<class element>
ListaDoble<element>& ListaDoble<element>::operator=(const ListaDoble<element> &l){
    if(this!=&l){
        this->vaciar();
        NodoDoble<element> *aux=l.primero;
        for(int i=1; i<=l.n; i++){
            this->insertar(aux->getData(), this->n+1);
            aux=aux->getNext();
        }
    }
    return *this;
}

#endif