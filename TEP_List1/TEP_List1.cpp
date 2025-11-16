// TEiP_Lab_1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "CTable.h"

bool b_alloc_table_fill_34(int iSize, int fillValue);
bool b_alloc_table_2_dim(int*** piTable, int iSizeX, int iSizeY);
bool b_dealloc_table_2_dim(int*** piTable, int iSizeX);


int main()
{
    b_alloc_table_fill_34(5, 34);
    int** piTable = 0;
    b_alloc_table_2_dim(&piTable, 5, 4);
    b_dealloc_table_2_dim(&piTable, 5);
    CTable table1;
    CTable table2("MojaTablica", 4);
    
    table1.vSetName("nowa nazwa");
    table1.bSetNewSize(4);
    std::cout << "Nowe imie " << table1.sGetName() << std::endl;
    std::cout << "Nowa dlugosc " << table1.iGetLength() << std::endl;
    int* newTable = new int[4];
    for (int i = 0; i < 4; i++) {
        newTable[i] = i+1;
    }

    table1.addTable(newTable, 4);
    table1.print();

    CTable clone0;
    CTable clone1;
    table1.doubleClone(clone0, clone1);
    clone0.print();
    clone1.print();
}

bool b_alloc_table_fill_34(int iSize, int fillValue) {

    if (iSize < 1) {
        return false;
    }

    int* piTable;
    piTable = new (std::nothrow) int[iSize];

    if (piTable == 0) {
        return false;
    }

    for (int i = 0; i < iSize; i++) {
        piTable[i] = fillValue;
        std::cout << piTable[i] << "\n";
    }

    std::cout << std::endl;

    delete[] piTable;

    return true;
}

bool b_alloc_table_2_dim(int*** piTable, int iSizeX, int iSizeY) {
    if (piTable == 0 || iSizeX < 1 || iSizeY < 1) {
        return false;
    }
   
    *piTable = new (std::nothrow) int* [iSizeX];
    //brak wolnego miejsca w pamieci
    if (*piTable == nullptr) {
        return false;
    }

    for (int i = 0; i < iSizeX; i++) {
        (*piTable)[i] = new (std::nothrow) int[iSizeY];

        if ((*piTable)[i] == nullptr) {
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

bool b_dealloc_table_2_dim(int*** piTable, int iSizeX) {
    if (piTable == 0 || *piTable == 0) {
        return false;
    }
    
    for (int i = 0; i < iSizeX; i++) {
        delete[](*piTable)[i];
    }
    delete[] *piTable;
    *piTable = 0;

    return true;
}