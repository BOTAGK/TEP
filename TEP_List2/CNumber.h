#ifndef CNumber_H
#define CNUmber_H
#include <string>
using namespace std;

class CNumber
{
public:

	static const int number_default_length = 2;
	static const int number_default_system = 10;

	CNumber();
	CNumber(int numericSystem, int iLength);
	CNumber(int numericSystem, int iLength, int* existingArray, bool positive);
	CNumber(const CNumber& otherNumber);
	~CNumber();


	void operator=(const int iValue);
	void operator=(const CNumber& pcNewVal);

	

	CNumber operator+(const CNumber& pcNewVal) const;
	CNumber operator*(const CNumber& pcNewVal) const;
	CNumber operator-(const CNumber& pcNewVal) const;
	CNumber operator-() const;
	CNumber operator/(const CNumber& pcNewVal) const;
	CNumber operator%(const CNumber& pcNewVal) const;

	CNumber operator&(const CNumber& pcNewVal) const;
	/*CNumber operator$(const CNumber & pcNewVal) const;*/

	CNumber operator^(const CNumber& pcNewVal) const;

	bool operator<(const CNumber& pcNewVal) const;
	bool operator>(const CNumber& pcNewVal) const;
	bool operator==(const CNumber& pcNewVal) const;
	bool operator<=(const CNumber& pcNewVal) const;
	bool operator>=(const CNumber& pcNewVal) const;

	CNumber baseConversion(const int iNewSystem) const;
	
	void deleteZeros();
	string sToStr();
	int* copyTable(const int* otherTable, int otherLength) const;
	

private:
	pair<CNumber, CNumber> divide(const CNumber& pcNewVal) const;
	CNumber negate() const;

	void trimZerosNoRealloc();
	void resetArray();
	void fixArray();
	
	
	bool setSize(int iSize);
	bool differentNSystem(const CNumber& pcNewVal) const;

	const int number_system;
	int* pi_number;
	int i_length;
	bool positive;
};
#endif