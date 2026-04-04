#ifndef RAID10_H
#define RAID10_H

#include<iostream>
#include<vector>
#include<string>
#include<cstdio>
#include"Disco.hpp"
#include"RAID.hpp"

using namespace std;

class RAID10: public RAID{
    public:
        /// @brief Constructor de arreglo RAID 10
        /// @param num Numero de Discos
        /// @param size Capacidad de los discos(entero)
        RAID10(int num, int size);

        /// @brief Escribir informacion en RAID 10
        /// @param info string de informacion a escribir
        void writeInfo(const string &info);

        /// @brief leer informacion de RAID 10
        /// @return string con toda la informacion almacenada en el arreglo
        string readInfo();

        /// @brief Verificar el estado de los discos
        /// @return Retorna un vector con el indice de los discos caidos.
        vector<int> verifyDisksStatus();

        /// @brief Recuperar informacion de disco caido
        /// @param diskNumber Numero del disco caido
        void recoverDisk(int diskNumber);

        ~RAID10(){}
};

//Implementacion metodos de RAID10

RAID10::RAID10(int num, int size): RAID(num, size){
    this->totalCapacity=num*size;
    this->usableCapacity=(num*size)/2;
}

void RAID10::writeInfo(const string &info){
    int segmentsNumber=this->disks.size()/2;
    int numberOfDisks=this->disks.size();

    int stringIndex=0;

    while(stringIndex<info.size()){

        vector<unsigned char> currentBytes;
        for(int i=0; i<segmentsNumber; i++){
            if(stringIndex<info.size()){
                currentBytes.push_back(info[stringIndex]);
                stringIndex++;
            }else{
                currentBytes.push_back('\0');
            }
        }

        int insertionIndex=0;
        for(int j=0; j<numberOfDisks; j+=2){
            vector<unsigned char> diskData=this->disks[j].getData();

            diskData.push_back(currentBytes[insertionIndex]);

            this->disks[j].writeData(diskData);
            this->disks[j+1].writeData(diskData);
            insertionIndex++;
        }
    }
}

string RAID10::readInfo(){
    //string de salida
    string exitData;

    int numberOfDisks=this->disks.size();
    int numberOfRows=this->disks[0].getData().size();

    for(int i=0; i<numberOfRows; i++){
        for(int j=0; j<numberOfDisks; j+=2){
            unsigned char c= this->disks[j].getData()[i];
            if(c != '\0'){
                exitData+= c;
            }
        }
    }

    return exitData;
}

vector<int> RAID10::verifyDisksStatus(){
    //obtener numero de discos
    int numberOfDisks=this->disks.size();

    //vector de salida
    vector<int> errorDisks;

    //verificar el estado de cada disco
    for(int i=0; i<numberOfDisks; i++){
        if(!this->disks[i].getStatus()){
            errorDisks.push_back(i);
        }
    }

    return errorDisks;
}

void RAID10::recoverDisk(int diskNumber){
    int recoveryIndex;
    if(diskNumber%2 == 0){
        recoveryIndex=diskNumber+1;
    }else{
        recoveryIndex=diskNumber-1;
    }
    if(this->disks[recoveryIndex].getStatus()){
        this->disks[diskNumber].writeData(this->disks[recoveryIndex].getData());
        this->disks[diskNumber].changeStatus();
    }else{
        cerr<<"[RAID10] Error al recuperar discos, el disco "<<diskNumber<<" y su pareja estan caidos."<<endl;
    }
}

#endif