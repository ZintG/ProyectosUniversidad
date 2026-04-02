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
};

//Implementacion metodos de RAID5

RAID5::RAID5(int num, int size): RAID(num, size){
    this->totalCapacity=num*size;
    this->usableCapacity=(num*size)-size;
}


#endif