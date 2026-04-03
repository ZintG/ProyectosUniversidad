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

        RAID(int diskNum, int diskSize);

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
    disks[diskNumber].borrarData();
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

        string readInfo() override;

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

#endif