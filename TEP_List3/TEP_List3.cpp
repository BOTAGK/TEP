// TEP_List3.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "CInterface.h"

int main()
{
    CInterface inter;

    inter.run();
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