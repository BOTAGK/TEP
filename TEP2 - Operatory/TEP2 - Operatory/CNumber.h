#pragma once
#include <string>
using namespace std;

const int i_DEFAULT_LENGTH = 10;

class CNumber
{
public:
	CNumber();
	CNumber(const int &number);
	CNumber(int length, int* numberTable, bool pos);
	CNumber(const CNumber& otherNumber);
	void normalize();
	~CNumber();

	int* tableCopy(const int* otherTable, int length) const;

	void operator=(const int pcNewVal);
	void operator=(const CNumber &other);
	CNumber operator-() const;
	CNumber operator+(const CNumber& other) const;
	CNumber operator-(const CNumber& other) const;
	CNumber operator*(const CNumber& other) const;
	CNumber operator/(const CNumber& other) const;

	bool operator<(const CNumber& other) const;
	bool operator>(const CNumber& other) const;
	bool operator==(const CNumber& other) const;
	bool operator<=(const CNumber& other) const;
	bool operator>=(const CNumber& other) const;

	string sToString();

private:
	int i_length;
	int* pi_number;
	bool positive;
	void setSize(int size);
};

