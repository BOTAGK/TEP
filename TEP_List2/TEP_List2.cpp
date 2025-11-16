// TEP_List2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "CNumber.h"
using namespace std;

int main()
{
    CNumber c_num_0, c_num_1;
    c_num_0 = 156;
    cout << c_num_0.sToStr() << endl;
    c_num_1 = 11;
    cout << c_num_1.sToStr() << endl;

    cout << "Dodawanie\n" << endl;
    CNumber c_dod;
    c_dod = c_num_0 + c_num_1;
    cout << c_dod.sToStr() << endl;

    cout << "Odejmowane\n" << endl;
    CNumber c_odd;
    c_odd = c_num_0 - c_num_1;
    cout << c_odd.sToStr() << endl;

    cout << "Mnozenie\n" << endl;
    CNumber c_mno;
    c_mno = c_num_0 * c_num_1;
    cout << c_mno.sToStr() << endl;

    cout << "Dzielenie\n" << endl;
    CNumber c_dziel;
    c_dziel = c_num_0 / c_num_1;
    cout << c_dziel.sToStr() << endl;
    cout << "Modulo\n" << endl;
    CNumber c_mod;
    c_mod = c_num_0 % c_num_1;
    cout << c_mod.sToStr() << endl;

    cout << "nowa podstawa\n" << endl;
    CNumber c_p2(2,10);
    c_p2 = c_num_0.baseConversion(2);
    cout << c_p2.sToStr() << endl;

    cout << "Modyfickacja\n" << endl;
    CNumber cv0, cv1;
    cv0 = 91234567;
    cv1 = 14532;
    CNumber res = cv0 ^ cv1;
    cout << res.sToStr() << endl;

    res = cv1 ^ cv0;
    cout << res.sToStr() << endl;

}
