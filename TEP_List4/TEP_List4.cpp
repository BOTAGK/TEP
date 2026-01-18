// TEP_List4.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "CInterface.h"
#include "CTree.h"

int main()
{
    //CInterface interface;
    //interface.run();

    CTree* c1 = nullptr;
    CResult<CTree*, CError> result1 = CTree::create({ "+","1","1" });

    if (result1.bIsSuccess()) {
        c1 = result1.cGetValue();
        cout << c1->treeToString() << endl;
    } else {
        // Handle error
        cout << "Error creating tree c1" << endl;
    }

    CTree* c2 = nullptr;
    CTree* c3 = nullptr;

    CResult<CTree*, CError> result2 = CTree::create({ "-","2","2" });
    if (result2.bIsSuccess()) {
        c2 = result2.cGetValue();
    } else {
        cout << "Error creating tree c2" << endl;
    }

    if (c1 != nullptr && c2 != nullptr) {
        c3 = new CTree(*c1 + *c2);
        cout << c3->treeToString() << endl;
    }

    // Clean up memory
    delete c1;
    delete c2;
    delete c3;
}

//1. zmienic CError
//*napisac klase ktora bedzie zapisywac do pliku
//*zmienic drzewo aby zmaiast retur null return CError dzialal na CResult i zwracal poprstu CResult jako return
//* 

//zajecia:
//# include "table.cpp" na koncu headera
//standardowo wszystko w headerze
//narasstajaco jeden plik o maksymalnej pojemnosci