#include "CNumber.h"
#include <iostream>
#include <string>
using namespace std;

CNumber::CNumber()
{
	i_length = i_DEFAULT_LENGTH;
	pi_number = new int[i_length];
	positive = true;
}

CNumber::CNumber(const int &number)
{
	i_length;
	pi_number = new int[1];
	positive;
	*this = 0;
}

CNumber::CNumber(int length, int* numberTable, bool pos)
{
	i_length = length;
	pi_number = numberTable;
	positive = pos;
}

CNumber::CNumber(const CNumber& otherNumber)
{
	i_length = otherNumber.i_length;
	positive = otherNumber.positive;
	int* pi_number_copy = tableCopy(otherNumber.pi_number, otherNumber.i_length);
	pi_number = pi_number_copy;
}

void CNumber::normalize()
{
	bool change = false;
	while (pi_number[i_length - 1] == 0 && i_length != 0) {
		i_length--;
		change = true;
	}
	if (change) {
		int* temp = tableCopy(pi_number, i_length);
		delete[] pi_number;
		pi_number = temp;
	}
}

CNumber::~CNumber()
{
	delete[] pi_number;
}

int* CNumber::tableCopy(const int* otherTable, int length) const
{
	int* result = new int[length];
	for (int ii = 0; ii < length; ii++) {
		result[ii] = otherTable[ii];
	}
	return result;
}

void CNumber::operator=(const int pcNewVal)
{
	positive = (pcNewVal >= 0);
	int temp = pcNewVal;
	if (!positive) temp *= -1;
	int new_length = 0;
	for (int ii = temp; ii > 0; ii = ii / 10) {
		new_length++;
	}
	i_length = new_length;
	delete[] pi_number;
	pi_number = new int[i_length];
	for (int ii = 0; ii < new_length; ii++) {
		pi_number[ii] = temp % 10 ;
		temp /= 10;
	}
}

void CNumber::operator=(const CNumber &other)
{
	positive = other.positive;
	if (pi_number != other.pi_number) {
		delete[] pi_number;
	}
	int* temp = tableCopy(other.pi_number, other.i_length);
	pi_number = temp;
	i_length = other.i_length;
}

CNumber CNumber::operator-() const
{
	if (*this == 0) return *this;
	return {i_length, tableCopy(pi_number, i_length), !positive};
}

CNumber CNumber::operator+(const CNumber& other) const
{
	int new_length = i_length + other.i_length;
	int* result = new int[new_length];
	for (int ii = 0; ii < other.i_length; ii++) {
		result[ii] = other.pi_number[ii];
	}
	for (int ii = 0; ii < i_length; ii++) {
		result[ii + other.i_length] = pi_number[ii];
	}
	return { new_length, result, true };
}

CNumber CNumber::operator-(const CNumber& other) const
{
	if (i_length <= other.i_length) {
		int* result = new int[1];
		result[0] = 0;
		return { 1, result, true };
	}
	else {
		int new_length = i_length - other.i_length;
		int* result = new int[new_length];
		for (int ii = i_length-1; ii >other.i_length-1; ii--) {
			result[ii - other.i_length] = pi_number[ii];
		}
		
		return { new_length, result, true };
	}
	
}

/*CNumber CNumber::operator+(const CNumber& other) const
{
	if (!positive && !other.positive) {
		return -(*this + other);
	}
	else if (!positive) {
		return other-*this;
	}
	else if (!other.positive) {
		return *this-other;
	}
	int passedOne = 0;
	int new_length = 0;
	if (i_length >= other.i_length) {
		new_length = i_length + 1;
	}
	else {
		new_length = other.i_length + 1;
	}

	int* result = new int[new_length];
	for (int ii = 0; ii < new_length; ii++) {
		int addition = passedOne;
		if (ii < i_length) {
			addition += pi_number[ii];
		}
		if (ii < other.i_length) {
			addition += other.pi_number[ii];
		}
		if (addition < 9) {
			result[ii] = addition;
			passedOne = 0;
		}
		else {
			result[ii] = addition % 10;
			passedOne = 1;
		}
	}
	return { new_length, result, true };
}*/

/*CNumber CNumber::operator-(const CNumber& other) const
{
	if (!positive && !other.positive) {
		return -(other-*this);
	}
	else if (!positive) {
		return -(*this+other);
	}
	else if (!other.positive) {
		return *this+other;
	}
	else if (*this < other) {
		return -(other - *this);
	}
	int stolen = 0;
	int new_length = 0;
	if (i_length >= other.i_length) {
		new_length = i_length;
	}
	else {
		new_length = other.i_length;
	}
	int* result = new int[new_length];

	for (int ii = 0; ii < new_length; ii++) {
		int substraction = stolen ;
		if (ii < i_length) {
			substraction += pi_number[ii];
		}
		if (ii < other.i_length) {
			substraction -= other.pi_number[ii];
		}
		if (substraction >= 0) {
			result[ii] = substraction;
			stolen = 0;
		}
		else {
			result[ii] = 10 + substraction;
			stolen = -1;
		}
	}
	return {new_length, result, true};
}*/

CNumber CNumber::operator*(const CNumber& other) const
{
	if (!positive && !other.positive) { 
	}
	else if (!positive) {
		return -(-*this * other);
	}
	else if (!other.positive) {
		return -(*this * -other);
	}
	int new_length = i_length + other.i_length;
	int* result = new int[new_length];

	for (int ii = 0; ii < new_length; ii++) {
		result[ii] = 0;
	}
	for (int iother = 0; iother < other.i_length; iother++) {
		for (int ii = 0; ii < i_length; ii++) {
			int multiplication = other.pi_number[iother] * pi_number[ii];
			result[ii + iother] += multiplication;
		}
	}
	
	int passed = 0;

	for (int ii = 0; ii < new_length; ii++) {
		result[ii] += passed % 10;
		passed /= 10;
		passed += result[ii] / 10;
		result[ii] %= 10;
	}

	return {new_length, result, true};
}

CNumber CNumber::operator/(const CNumber& other) const
{
	if (!positive && !other.positive) {
		return *this/other;
	}
	else if (!positive) {
		return -(*this/other);
	}
	else if (!other.positive) {
		return -(*this / other);
	}else
	if (other.pi_number[other.i_length - 1] == 0) return 0;
	else if (*this < other) return 0;

	CNumber	quotient = 0;
	quotient.setSize(i_length);
	CNumber remainder = 0;
	remainder.setSize(i_length);

	for (int ii = i_length - 1; ii >= 0; ii--) {
		for (int ij = remainder.i_length-1; ij > 0; ij--) {
			remainder.pi_number[ij] = remainder.pi_number[ij - 1];
		}

		remainder.pi_number[0] = pi_number[ii];

		while (remainder >= other) {
			remainder = remainder - other;
			quotient.pi_number[ii] += 1;
		}

		remainder.setSize(i_length);
	}

	quotient.normalize();
	return quotient;
}

bool CNumber::operator<(const CNumber& other) const
{
	return !(*this >= other);
}

bool CNumber::operator>(const CNumber& other) const
{
	return !(*this <= other);
}

bool CNumber::operator==(const CNumber& other) const
{
	CNumber this_copy = { *this };
	CNumber other_copy = { *this };
	this_copy.normalize();
	other_copy.normalize();

	if (i_length != other.i_length) return false;
	for (int ii = 0; ii < i_length; ii++) {
		if (pi_number[ii] != other.pi_number[ii]) return false;
	}
	return true;
}

bool CNumber::operator<=(const CNumber& other) const
{
	CNumber this_copy = { *this };
	CNumber other_copy = { *this };
	this_copy.normalize();
	other_copy.normalize();

	if (other_copy.i_length > this_copy.i_length) return true;
	if (other_copy.i_length < this_copy.i_length) return false;
	for (int ii = this_copy.i_length - 1; ii >= 0; ii--) {
		if (this_copy.pi_number[ii] > other_copy.pi_number[ii]) return false;
	}
	return true;
}

bool CNumber::operator>=(const CNumber& other) const
{
	CNumber this_copy = { *this };
	CNumber other_copy = { *this };
	this_copy.normalize();
	other_copy.normalize();

	if (other.i_length < i_length) return true;
	if (other.i_length > i_length) return false;
	for (int ii = i_length - 1; ii >= 0; ii--) {
		if (pi_number[ii] < other.pi_number[ii]) return false;
	}
	return true;
}


string CNumber::sToString()
{
	string result = "";
	for (int ii = i_length-1; ii >= 0; ii--) {
		result += to_string(pi_number[ii]) + " ";
	}
	cout << endl;
	return result;
}

void CNumber::setSize(int size)
{
	int* temp = new int[size];
	if (size > i_length) {
		for (int ii = 0; ii < i_length; ii++) {
			temp[ii] = pi_number[ii];
		}
		for (int ii = i_length; ii < size; ii++) {
			temp[ii] = 0;
		}
	}
	else {
		for (int ii = 0; ii < size; ii++) {
			temp[ii] = pi_number[ii];
		}
	}
	i_length = size;
	pi_number = temp;
}