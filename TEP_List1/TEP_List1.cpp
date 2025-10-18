// TEiP_Lab_1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "CTable.h"

bool b_alloc_table_fill_34(int iSize, int fillValue);
bool b_alloc_table_2_dim(int*** piTable, int iSizeX, int iSizeY);


int main()
{
    b_alloc_table_fill_34(5, 34);
    CTable table1;
    CTable table2("MojaTablica", 5);
   
}

//Czy robic to w osobnej klasie i nazewnictow klasy np Zad 1 czy jak
bool b_alloc_table_fill_34(int iSize, int fillValue) {

    if (iSize < 1) {
        return false;
    }

    int* piTable;
    piTable = new int[iSize];

    for (int i = 0; i < iSize; i++) {
        piTable[i] = fillValue;
        std::cout << piTable[i] << "\n";
    }

    std::cout << std::endl;

    delete[] piTable;

    return true;
}

bool b_alloc_table_2_dim(int*** piTable, int iSizeX, int iSizeY) {
    if (piTable == nullptr || iSizeX < 1 || iSizeY < 1) {
        return false;
    }
   
    *piTable = new (std::nothrow) int* [iSizeX];
    //brak wolnego miejsca w pamieci
    if (*piTable == nullptr) {
        return false;
    }

    for (int i = 0; i < iSizeX; i++) {
        (*piTable)[i] = new (std::nothrow) int[iSizeY];

        if (*piTable[i] == nullptr) {
            for (int j = 0; j < i; j++) {
                delete[] (*piTable)[j];
            }
            delete[] *piTable;
            //aby wskaznik nie wisial
            *piTable = nullptr;

            return false;
        }
    }
    return true;
}

bool b_dealloc_table_2_dim(int*** piTable, int iSizeX, int iSizeY) {
    if (piTable == nullptr || *piTable == nullptr) {
        return false;
    }
    
    for (int i = 0; i < iSizeX; i++) {
        delete[](*piTable)[i];
    }
    delete[] *piTable;
    *piTable = nullptr;

    return true;
}