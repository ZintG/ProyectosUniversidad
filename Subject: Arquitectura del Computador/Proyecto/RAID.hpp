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

        RAID(int num, int size);

        virtual void writeInfo(const string &info)=0;

        virtual string readInfo()=0;

        virtual void recoverDisk(int diskNumber)=0;

        void diskFailure(int diskNumber);

        int getUsableCapacity() const;

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

//Clase Hija RAID5

class RAID5: public RAID{
    public:
        RAID5(int num, int size);

        void writeInfo(const string &info);

        string readInfo();

        int verifyDisksStaus();

        void recoverDisk(int diskNumber);
};

//Implementacion metodos de RAID5

RAID5::RAID5(int num, int size): RAID(num, size){
    this->totalCapacity=num*size;
    this->usableCapacity=(num*size)-size;
}

void RAID5::writeInfo(const string &info){
    //Obtener numero de bytes a insertar en la fila
    int segmentsNumber=this->disks.size()-1;

    //Recorrer Info
    int stringIndex=0;
    while(stringIndex<info.size()){
        //Obtener fila actual
        int currentRow=this->disks[0].getData().size();

        //Calcular en que disco va la paridad en la fila actual
        int parityDisk=currentRow % this->disks.size();

        //Vector para almacenar los bytes a guardar en la fila
        vector<unsigned char> currentBytes;


        /*Guarda el segmento de bytes a guardar de la fila actual en el vector.
        Si faltan bytes para terminar la fila rellena con caracter nulo*/
        for(int i=0; i<segmentsNumber; i++){
            if(stringIndex<info.size()){
                currentBytes.push_back(info[stringIndex]);
                stringIndex++;
            }else{
                currentBytes.push_back('\0');
            }
        }

        //Calculo de paridad de la fila actual
        unsigned char parity='\0';
        for(int j=0; j<currentBytes.size(); j++){
            parity^=currentBytes[j];
        }

        /*Insercion en discos, guarda los bytes en orden y el bytes de paridad en el
        disco correspondiente en la fila*/
        int insertionIndex=0;
        for(int k=0; k<this->disks.size(); k++){
            vector<unsigned char> diskData=this->disks[k].getData();
            if(k==parityDisk){
                diskData.push_back(parity);
            }else{
                diskData.push_back(currentBytes[insertionIndex]);
                insertionIndex++;
            }

            this->disks[k].writeData(diskData);
        }
    }
}

string RAID5::readInfo(){
    //Obtener numero de filas y numero de discos
    int numberOfRows=this->disks[0].getData().size();
    int numberOfDisks=this->disks.size();
    //string de salida
    string exitData;

    //recorrer cada fila
    for(int i=0; i<numberOfRows; i++){
        //calcular disco de paridad
        int parityDisk= i % numberOfDisks;
        //recorrer cada disco
        for(int j=0; j<numberOfDisks; j++){
            //si no es el diso de paridad de la fila guarda el caracter
            if(j!=parityDisk){
                //verificar si el caracter no es relleno ('\0)
                if(this->disks[j].getData()[i] != '\0'){
                    exitData+= this->disks[j].getData()[i];
                }
            }
        }
    }

    return exitData;
}

int RAID5::verifyDisksStaus(){
    //Obtener numero de Discos
    int numberOfDisks=this->disks.size();
    //Vector para guardar el indice del disco fallado y verificar si hay mas de un fallo
    vector<int> errorDisk;

    //recorrer discos y verificar estado
    for(int i=0; i<numberOfDisks; i++){
        if(!this->disks[i].getStatus()){
            errorDisk.push_back(i);
        }
    }

    //si hay mas de un disco fallado retorna -1 (error fatal)
    if(errorDisk.size()>1){
        return -1;
    }else{
        //retorna el indice del disco fallado
        return errorDisk[0];
    }
}

void RAID5::recoverDisk(int diskNumber){
    int numberOfRows;
    if(diskNumber==0){
        numberOfRows=this->disks[1].getData().size();
    }else{
        numberOfRows=this->disks[0].getData().size();
    }

    int numberOfDisks=this->disks.size();

    vector<unsigned char> recoveredData;

    for(int i=0; i<numberOfRows; i++){

        unsigned char recoveredByte='\0';
        for(int j=0; j<numberOfDisks; j++){
            if(j!=diskNumber){
                recoveredByte^=this->disks[j].getData()[i];
            }
        }

        recoveredData.push_back(recoveredByte);
    }
    this->disks[diskNumber].writeData(recoveredData);
}

#endif