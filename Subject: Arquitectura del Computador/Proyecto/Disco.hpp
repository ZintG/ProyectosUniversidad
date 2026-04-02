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
        Disco(string name): diskName(name){}

        vector<unsigned char> readData();

        void writeData(vector<unsigned char> newData);

        
};

#endif