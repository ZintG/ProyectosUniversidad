#ifndef DISCO_H
#define DISCO_H

#include<iostream>
#include<fstream>
#include<string>
#include<vector>

using namespace std;
class Disco{
    private:
        string diskName;
        int diskSize;
        static int numberOfExistingDisk;
        vector<unsigned char> data;
    public:
        ///@brief Constructor de la clase Disco.
        ///@param name Nombre del archivo. Si el archivo no existe lo crea
        ///@param size Capacidad del Disco en GB
        Disco(string name, int size);

        /// @brief Leer data de un disco
        /// @return vector<unsigned char>, cada espacio del vector es un byte
        vector<unsigned char> getData() const;

        /// @brief Guardar data modificada en un disco
        /// @param newData recibe vector<unsigned char> y lo escribe en el archivo(sobreescritura)
        void writeData(const vector<unsigned char> &newData);

        /// @brief Obtener capacidad del Disco en GB
        /// @return Capcaidad del Disco en int
        int getDiskSize() const;

        /// @brief Obtener numeros de discos existentes
        /// @return Numero de discos existentes, int 
        int getNumberOfDisk() const;

        /// @brief Inicializar contador de discos estatico
        void startDiskCounter();

        /// @brief Eliminar la data del Disco(archivo)
        void borrarData();

        /// @brief Destructor (No borra el archivo)
        ~Disco();
};

Disco::Disco(string name, int size): diskName(name), diskSize(size){
    this->numberOfExistingDisk++;

    //Abrir archivo en modo lectura
    ifstream disk(this->diskName, ios::binary);
    //verificar que existe y se abrio correctamente
    if(disk.is_open()){
        //cargar informacion del archivo en el vector data
        unsigned char nuevo;
        while(disk.read((char*)&nuevo, sizeof(nuevo))){
            this->data.push_back(nuevo);
        }
        disk.close();
    }else{
        //Si el archivo no se abrio o no existe se crea
        ofstream newDisk(this->diskName, ios::binary);
        //verificacion de apertura/creacion correcta
        if(!newDisk.is_open()){
            cerr<<"Error al abrir/crear archivo"<<endl;
        }else{
            newDisk.close();
        }
    }
}

vector<unsigned char> Disco::getData() const{
    return this->data;
}

void Disco::writeData(const vector<unsigned char> &newData){
    //Cargar datos modificados en el objeto
    this->data=newData;

    ofstream disk(this->diskName, ios::binary);

    if(disk.is_open()){
        //Escribir en el archivo
        disk.write((char*)this->data.data(), this->data.size());

        disk.close();
    }else{
        cerr<<"Error al abrir el archivo"<<endl;
    }
}


#endif