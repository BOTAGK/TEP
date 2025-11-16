#include "CTable.h"
#include <iostream>

using std::string;
using std::cout;
using std::endl;

const string CTable::default_name = "CTabel";

CTable::CTable() {
	s_name = default_name;
	i_table_len = default_i_tabel_len;
	
	cout << "bezp: '" << s_name << "'\n" << endl;

	pi_table = new int[i_table_len];
}


CTable::CTable(string sName, int iTableLen) {
	s_name = sName;
	i_table_len = iTableLen;

	cout << "parametr: '" << s_name << "'\n" << endl;

	pi_table = new int[i_table_len];
}

CTable::CTable(const CTable& pcOther) {
	s_name = pcOther.s_name + "_copy";
	i_table_len = pcOther.i_table_len;

	pi_table = new int[i_table_len];

	for (int i = 0; i < i_table_len; i++) {
		pi_table[i] = pcOther.pi_table[i];
	}

	cout << "kopiuj: '" << s_name << "'\n" << endl;
}

CTable::~CTable() {
	cout << "usuwam: '" << s_name << "'\n" << endl;

	delete[] pi_table;
}

void CTable::vSetName(string sName) {
	s_name = sName;
}

void CTable::doubleClone(CTable& pcClone0, CTable& pcClone1) {
	pcClone0 = *(new CTable(*this));
	pcClone1 = *(new CTable(*this));
}
void CTable::addTable(int* newTable, int iSize) {
	int elem_to_add = (i_table_len < iSize) ? i_table_len : iSize;

	for (int i = 0; i < elem_to_add; i++) {
		pi_table[i] = newTable[i];
	}
}

void CTable::print() {
	for (int i = 0; i < i_table_len; i++) {
		cout << pi_table[i] << " " << endl;
	}
	cout << "'\n" << endl;
}
string CTable::sGetName() {
	return s_name;
}
int CTable::iGetLength() {
	return i_table_len;
}

bool CTable::bSetNewSize(int newITableLen) {
	if (newITableLen < 1 ) {
		return false;
	}
	int* pi_table_copy;
	pi_table_copy = new int[newITableLen];

	int elem_to_copy = (i_table_len < newITableLen) ? i_table_len : newITableLen;
	
	for (int i = 0; i < elem_to_copy; i++) {
		pi_table_copy[i] = pi_table[i];
	}

	delete[] pi_table;

	pi_table = pi_table_copy;
	i_table_len = newITableLen;
	return true;
}

CTable* CTable::pcClone() {
	return new CTable(*this);
}


