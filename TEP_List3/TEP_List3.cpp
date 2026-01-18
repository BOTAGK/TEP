// TEP_List3.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "CInterface.h"
#include "CTree.h"

int main()
{
    /*CInterface inter;

    inter.run();*/

    /*CTree c1, c2, res;
    c1.create({ "+", "1", "2" });
   
    c2.create({ "*", "3", "4" });
    cout << c1.treeToString() << endl;
    cout << c2.treeToString() << endl;
    res = c1 + c2;
    cout << res.treeToString() << endl;*/

    CTree c1;
    c1.create({ "+", "+", "+", "1", "1", "1", "1" });
    cout << c1.treeToString() << "\n" << endl;
    cout << c1.countLeafs() << endl;
}

//wektor na poziomie CNode (CNode -> (CNodeOP, CNodeVar, CNodeAbsolute) 
//CNodeOP-> CNode+ itd
//CNode pola: vector<CNode* > children, sTOStr, parent(np do sprawdzenia glebokosci)
// w CNodeVar mamy miec Ctree* pc_tree pyta drzewa czy drzewo posieda vektor <CVariable*> cvats 
//wiec CNodeVar musi jescze miec CNodeVar* pcVar aby tworzyc pozostale nody na podstawie pierwszego
//nody beda sie wczytywac ze stringa a nie parser pcTree -> eLoad(string) zwraca klase gdzie jest blad
//static CNode* pcCreateNode(cstring token, errorr *pcERror) albo vektor i klonowanie w zaleznosci od nazwy
//albo seria ifow
//wlasne cError 
//eLoad(vector 
//pc.Root = pcCreateNode(pvTor ->
//pc.root = eload(pvTokens,1) -> pc.child; for(i =0; i < ) pc.child = pcCreateNode(pvTokens,off)
// //pcChild.push, pcChild -> eLoad
//CError eLoad(pvTokens, int, offStart, int* piOffEnd)
//podzielic pliki 