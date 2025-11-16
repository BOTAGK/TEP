#ifndef CTable_H
#define CTable_H

#include <string>
using std::string;

class CTable
{
public:
	static const int default_i_tabel_len = 10;
	static const string default_name;

	CTable();
	CTable(string sName, int iTableLen);
	CTable(const CTable& pcOther);
	~CTable();
	void vSetName(string sName);
	void doubleClone(CTable& pcClone0, CTable& pcClone1);
	void print();
	void addTable(int* newTable, int iSize);
	bool bSetNewSize(int iTableLen);
	string sGetName();
	int iGetLength();
	CTable* pcClone();
private:
	string s_name;
	int i_table_len;
	int* pi_table;
};
#endif
