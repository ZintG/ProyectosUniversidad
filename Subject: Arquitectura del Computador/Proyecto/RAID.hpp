#ifndef RAID_H
#define RAID_H

#include<iostream>
#include<vector>
#include<string>
#include<cstdio>
#include"Disco.hpp"

using namespace std;

//Clase base RAID
class RAID{
    protected:
        vector<Disco> disks;
        int sizeOfDisks;
        int usableCapacity, totalCapacity;

    public:
        /// @brief Constructor de clase abstracta RAID
        /// @param num Numero de discos
        /// @param size Capacidad de los discos en GB
        RAID(int num, int size);

        /// @brief Metodo virtual para escribir informacion
        /// @param info string que contiene la informacion a escribir
        virtual void writeInfo(const string &info)=0;

        /// @brief Metodo Virtual para leer la informacion del arreglo
        /// @return string con la informacion completa
        virtual string readInfo()=0;

        /// @brief Metodo virtual para recuperar un disco caido.
        /// @param diskNumber Numero del disco caido
        virtual void recoverDisk(int diskNumber)=0;

        /// @brief Simular fallo de disco. Borra toda su informacion
        /// @param diskNumber Numero del disco al que se le va a borrar la informacion
        void diskFailure(int diskNumber);

        /// @brief Obtener capacidad real utilizable del arreglo
        /// @return numero entero que representa la capacidad en GB
        int getUsableCapacity() const;

        /// @brief Obtener capacidad total del arreglo
        /// @return numero entero que representa la capacidad en GB
        int getTotalCapacity() const;

        virtual ~RAID(){}
};

//Implementacion metodos de RAID

RAID::RAID(int num, int size):sizeOfDisks(size){
    for(int i=0; i<num; i++){
        char label[200];

        sprintf(label, "disk%d.bin", i);

        string diskLabel=label;

        Disco newDisk(diskLabel, size);

        this->disks.push_back(newDisk);
    }
}

void RAID::diskFailure(int diskNumber){
    disks[diskNumber].eraseData();
}

int RAID::getTotalCapacity() const{
    return this->totalCapacity;
}

int RAID::getUsableCapacity() const{
    return this->usableCapacity;
}

#endif