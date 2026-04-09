#ifndef ARBOLBIN_HPP
#define ARBOLBIN_HPP

#include<iostream>
#include<list>

//Clase Nodo Binario
template<class element>
class NodoBin{
    private:
        element info;
        NodoBin<element> *hijoIzq, *hijoDer;
    public:

        /// @brief Constructor de Nodo Binario
        /// @param info Elemento del nodo
        NodoBin(element info);

        /// @brief Segundo constructor de nodo binario
        /// @param info Elemento del nodo
        /// @param hijoIzq ptr al hijo izquierdo del nodo
        /// @param hijoDer ptr al hijo derecho del nodo
        NodoBin(element info, NodoBin<element> *hijoIzq, NodoBin<element> *hijoDer);

        /// @brief Obtener elemento almacenado en el nodo
        /// @return elemento del nodo
        element getInfo();

        /// @brief Modificar info del nodo
        /// @param info Nuevo elemento del nodo
        void setInfo(element info);

        /// @brief Obtener puntero al hijo izquierdo
        /// @return NodoBin<element>*
        NodoBin<element>* getHijoIzq();

        /// @brief Obtener puntero al hijo derecho
        /// @return NodoBin<element>*
        NodoBin<element>* getHijoDer();

        /// @brief Modificar hijo izquierdo
        /// @param ptr Puntero a NodoBin<element>
        void setHijoIzq(NodoBin<element> *ptr);

        /// @brief Modificar hijo derecho
        /// @param ptr Puntero a NodoBin<element>
        void setHijoDer(NodoBin<element> *ptr);

        ~NodoBin<element>{}
};

//Implementacion de metodos de NodoBin
template<class element>
NodoBin<element>::NodoBin(element info):info(info), hijoIzq(NULL), hijoDer(NULL){}

template<class element>
NodoBin<element>::NodoBin(element info, NodoBin<element> *hijoIzq, NodoBin<element> *hijoDer):info(info), hijoIzq(hijoIzq), hijoDer(hijoDer){}

template<class element>
element NodoBin<element>::getInfo(){
    return this->info;
}

template<class element>
void NodoBin<element>::setInfo(element info) {
    this->info = info;
}

template<class element>
NodoBin<element>* NodoBin<element>::getHijoIzq(){
    return this->hijoIzq;
}

template<class element>
NodoBin<element>* NodoBin<element>::getHijoDer(){
    return this->hijoDer;
}

template<class element>
void NodoBin<element>::setHijoIzq(NodoBin<element> *ptr){
    this->hijoIzq=ptr;
}

template<class element>
void NodoBin<element>::setHijoDer(NodoBin<element> *ptr){
    this->hijoDer=ptr;
}


//Definicio Clase Arbol Binario
template<class element>
class ArbolBin{
    private:
        NodoBin<element> *pRaiz;
        int peso;
    public:
        /// @brief Constructor Arbol Binario
        ArbolBin();

        /// @brief Constructor de copia profunda Arbol Binario
        /// @param a Arbol a copiar
        ArbolBin(const ArbolBin<element> &a);

        /// @brief Obtener raiz del arbol
        /// @return Elemento de la raiz del arbol
        element getRaiz();

        /// @brief Verificar si el arbol es nulo
        /// @return true si el arbol es nulo, false en caso contrario
        bool esNulo();

        /// @brief Verificar si el arbol es una hoja
        /// @return true si es hoja, false en caso contrario
        bool esHoja();

        /// @brief Obtener peso
        /// @return entero con la cantidad de elementos
        int getPeso();

        /// @brief Obtener subarbol izquierdo
        /// @return Copia profunda del subarbol 
        ArbolBin<element> getHijoIzq();

        /// @brief Obtener subarbol derecho
        /// @return Copia profunda del subarbol
        ArbolBin<element> getHijoDer();

        /// @brief Insertar elemento en la raiz
        /// @param info Elemento a insertar
        void insertarElemento(element info);

        /// @brief Insertar elemento
        /// @param padre padre del elemento a insertar
        /// @param info elemento a insertar
        void insertarElemento(element padre, element info);

        /// @brief Eliminar subarbol
        /// @param info raiz del subarbol
        void eliminarSubArbol(const element &info);

        /// @brief Obtener recorrido preorden del arbol
        /// @return lista con los elementos en preorden
        list<element> preOrden();

        /// @brief Obtener recorrido postorden del arbol
        /// @return lista con los elementos en postorden
        list<element> postOrden();

        /// @brief Obtener recorrido inorden del arbol
        /// @return lista con los elementos en inorden
        list<element> inOrden();

        /// @brief Obtener recorrido por niveles del arbol
        /// @return lista con los elementos por niveles
        list<element> porNiveles();

        /// @brief Obtener hojas del arbol
        /// @return Lista de los elementos hoja del arbol
        list<element> getHojas();

        void vaciar();

        ~ArbolBin();
};

template<class element>
ArbolBin<element>::ArbolBin(): pRaiz(NULL), peso(0){}

template<class element>
ArbolBin<element>::ArbolBin(const ArbolBin<element> &a){
    if(a.pRaiz==NULL){
        this->pRaiz=NULL;
        this->peso=0;
    }else{
        this->pRaiz=new NodoBin<element>(a.pRaiz->getInfo());
        this->peso=a.peso;
        list<NodoBin<element>*> colaA, colaC;
        colaA.push_back(a.pRaiz);
        colaC.push_back(this->pRaiz);
        while(!colaA.empty()){
            NodoBin<element>* nodoA=colaA.front();
            NodoBin<element>* nodoC=colaC.front();
            colaA.pop_front();
            colaC.pop_front();
            if(nodoA->getHijoIzq()!=NULL){
                nodoC->setHijoIzq(new NodoBin<element>(nodoA->getHijoIzq()->getInfo()));
                colaA.push_back(nodoA->getHijoIzq());
                colaC.push_back(nodoC->getHijoIzq());
            }
            if(nodoA->getHijoDer()!=NULL){
                nodoC->setHijoDer(new NodoBin<element>(nodoA->getHijoDer()->getInfo()));
                colaA.push_back(nodoA->getHijoDer());
                colaC.push_back(nodoC->getHijoDer());
            }
        }
    }
}

template<class element>
element ArbolBin<element>::getRaiz(){
    if(this->pRaiz!=NULL){
        return this->pRaiz->getInfo();
    }else{
        throw std::runtime_error("El arbol es nulo");
    }
}

template<class element>
bool ArbolBin<element>::esNulo(){
    return this->pRaiz==NULL;
}

template<class element>
bool ArbolBin<element>::esHoja(){
    if(this->pRaiz!=NULL){
        return this->pRaiz->getHijoIzq()==NULL && this->pRaiz->getHijoDer()==NULL;
    }else{
        throw std::runtime_error("El arbol es nulo");
    }
}

template<class element>
int ArbolBin<element>::getPeso(){
    return this->peso;
}

template<class element>
ArbolBin<element> ArbolBin<element>::getHijoIzq(){
    if(this->pRaiz!=NULL){
        ArbolBin<element> subArbol(this->pRaiz->getHijoIzq());
        return subArbol;
    }else{
        throw std::runtime_error("El arbol es nulo");
    }
}

template<class element>
ArbolBin<element> ArbolBin<element>::getHijoDer(){
    if(this->pRaiz!=NULL){
        ArbolBin<element> subArbol(this->pRaiz->getHijoDer());
        return subArbol;
    }else{
        throw std::runtime_error("El arbol es nulo");
    }
}

#endif