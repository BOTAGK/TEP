// TEP_List5.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "CMySmartPointer.hpp"
#include "TestObject.h"
#include "CTree.h"

int main()
{
    //----------------------SmartPointer -----------------------------
       
    cout << "Test 1" << endl;
    {
        CMySmartPointer<TestObject> ptr1(new TestObject(1, "Obiekt 1"));
        ptr1->sayHello();
    }
    
    cout << "Koniec Test 1 (Obiekt powinien sie usunac )" << endl;

    cout << "=== TEST 2: Konstruktor Kopiuj¹cy (Wspoldzielenie) ===" << endl;
    {
        CMySmartPointer<TestObject> ptr1(new TestObject(2, "Obiekt Wspolny"));

        {
            cout << "   > Wchodze w wewnetrzny zakres..." << endl;
            CMySmartPointer<TestObject> ptr2 = ptr1; // Kopiujemy wskaŸnik (licznik = 2)
            ptr2->sayHello();
            cout << "   > Wychodze z wewnetrznego zakresu (ptr2 ginie)..." << endl;
        }
        // Tutaj ptr2 zgin¹³, ale licznik spad³ z 2 na 1. Obiekt NIE powinien byæ usuniêty.
        cout << "   > Jestem z powrotem w glownym zakresie. Obiekt nadal powinien zyc." << endl;
        ptr1->sayHello(); // Nadal dzia³a!
    }
    // Teraz ptr1 ginie, licznik spada do 0 -> Destruktor obiektu.
    cout << "=== Koniec TEST 2 ===\n" << endl;


    cout << "=== TEST 3: Operator Przypisania (=) ===" << endl;
    {
        CMySmartPointer<TestObject> ptrA(new TestObject(10, "A - Stary"));
        CMySmartPointer<TestObject> ptrB(new TestObject(20, "B - Nowy"));

        cout << "   > Wykonuje przypisanie: ptrA = ptrB;" << endl;
        cout << "   > Oczekujemy: 'A - Stary' ginie natychmiast, 'B - Nowy' zyje dalej." << endl;

        ptrA = ptrB; // Stary obiekt A (licznik 1->0) powinien zostaæ usuniêty TU I TERAZ.
        // Obiekt B (licznik 1->2) jest teraz trzymany przez oba wskaŸniki.

        cout << "   > Po przypisaniu. Sprawdzam ptrA:" << endl;
        ptrA->sayHello(); // Powinno wypisaæ "B - Nowy"
    }
    // Tutaj oba wskaŸniki (ptrA i ptrB) wskazuj¹ na "B - Nowy". 
    // Gdy wyjd¹ z zakresu, licznik spadnie 2->1->0 i "B - Nowy" zostanie usuniêty.
    cout << "=== Koniec TEST 3 ===\n" << endl;


    cout << "=== TEST 4: Dereferencja i operator * ===" << endl;
    {
        CMySmartPointer<int> intPtr(new int(123));
        cout << "   Wartosc pod wskaznikiem: " << *intPtr << endl;
        *intPtr = 999;
        cout << "   Zmieniona wartosc: " << *intPtr << endl;
    }
    cout << "=== Koniec TEST 4 ===\n" << endl;

    //----------------------Move semantics-----------------------------
    //CTree t1, t2;
    //
    //CTree::iCopyCount = 0;
    //CTree::iMoveCount = 0;

    //cout << "\n1. Test operatora dodawania (C = A + B):" << endl;

    //CTree t3;
    //t3 = t1 + t2;

    //cout << "Liczba kopii (Deep Copy): " << CTree::iCopyCount << endl;
    //cout << "Liczba przeniesien (Move): " << CTree::iMoveCount << endl;

    //cout << "\n----------------------------------------" << endl;
    //cout << "WNIOSKI Z TESTU 1:" << endl;
    //cout << "- Kopie: Powinna byc 1 (wewnatrz operatora+, linijka CTree result(*this))" << endl;
    //cout << "- Przeniesienia: Powinno byc min. 1 (przypisanie wyniku do treeC)" << endl;
    //cout << "  Gdyby nie Move Semantics, mielibysmy tu 2 lub 3 kopie!" << endl;
    //cout << "----------------------------------------" << endl;


    //// Reset liczników
    //CTree::iCopyCount = 0;
    //CTree::iMoveCount = 0;

    //cout << "\n2. Test std::move (A = move(C)):" << endl;

    //t1 = std::move(t3);

    //cout << "Liczba kopii (Deep Copy): " << CTree::iCopyCount << endl;
    //cout << "Liczba przeniesien (Move): " << CTree::iMoveCount << endl;

    //cout << "\n----------------------------------------" << endl;
    //cout << "WNIOSKI Z TESTU 2:" << endl;
    //cout << "- Kopie: Musi byc 0. To czysta kradziez wskaznikow." << endl;
    //cout << "- Przeniesienia: Musi byc 1." << endl;
    //cout << "----------------------------------------" << endl;

    return 0;
}


//CIntDeleter 
//public CIntDeleter(int *piDelete)
//public ~CIntDeleter(){delete *piDelete}
//private int *piDelete
//rozszerzyc o tempalte
//licznik aby ostanti wskaznik usuwal

//move semantcis konstrutkor przenoszaczay 
//CTable(CTable && pcTable) podwojan referencja dziala jak pojedyncza ale 
//iSize = pcTab.iSize
//piTab = pcOther.piTab
//pcOther.piTabl = NULL;
//konustrkotr zazwyczaj wie kiedy ma uzyc konstruktora przenoszacego ale jesli chcemy wywolac zmusic to
//w metodzie jakiejs piszemy std::move(cTab) ktory dodaje dwa ampresanty 

