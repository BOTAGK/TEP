#include "CNumber.h"
#include <iostream>

CNumber::CNumber()
:number_system(number_default_system)
{
	i_length = number_default_length;
	pi_number = new int[i_length];
	positive = true;

	resetArray();
}
CNumber::CNumber(int numericSystem, int iLength)
:number_system(numericSystem), i_length(iLength){
	pi_number = new int[iLength];
	positive = true;

	resetArray();
}

CNumber::CNumber(int numericSystem, int iLength, int* exisitngArray, bool pos)
:number_system(numericSystem),i_length(iLength), pi_number(exisitngArray), positive(pos){
	fixArray();
}

CNumber::CNumber(const CNumber& pcNewVal)
:number_system(pcNewVal.number_system), i_length (pcNewVal.i_length), positive (pcNewVal.positive)
{
	pi_number = copyTable(pcNewVal.pi_number, i_length);
}

int* CNumber::copyTable (const int* pcNewValTable, int pcNewValLength) const {
	int* newTable = new int[pcNewValLength];

	for (int i = 0; i < pcNewValLength; i++) {
		newTable[i] = pcNewValTable[i];
	}
	return newTable;
}

CNumber::~CNumber() {
	delete[] pi_number;
}

//mozliwa druga implementacja w ktorej liczba jest odrazu dzielona na cyfry i dodawane sa po kolei do danych pol 
void CNumber::operator=(const int iValue) {
	positive = (iValue >= 0);
	//pierwszy sposob implementacji

	pi_number[0] = iValue;
	fixArray();

	//drugi sposob implementacji
	/*int temp = iValue;
	if (!positive) temp = -temp;

	int length = 0;
	for (int i = temp; i > 0; i /= number_system) {
		length++;
	}
	i_length = length;
	delete[] pi_number;
	pi_number = new int[i_length];

	for (int i = 0; i < i_length; i++) {
		pi_number[i] = temp % number_system;
		temp /= number_system;
	}*/
}

void CNumber::operator=(const CNumber& pcNewVal){
	if (differentNSystem(pcNewVal)) {
		return *this = pcNewVal.baseConversion(number_system);
	}
	delete[] pi_number;
	pi_number = copyTable(pcNewVal.pi_number, pcNewVal.i_length);
	i_length = pcNewVal.i_length;
	positive = pcNewVal.positive;

}

CNumber CNumber::operator+(const CNumber& pcNewVal) const {
	//4 przypadki
	if (differentNSystem(pcNewVal)) {
		return *this + pcNewVal.baseConversion(number_system);
	}
	if (!positive && pcNewVal.positive) {
		 return pcNewVal - this->negate();
	}
	else if (positive && !pcNewVal.positive) {
		return *this - pcNewVal.negate();
	}

	int newLength = (i_length >= pcNewVal.i_length) ? i_length : pcNewVal.i_length;
	int* res = new int[newLength];

	for (int i = 0; i < newLength; i++) {
		res[i] = 0;
	}

	for (int i = 0; i < newLength; i++) {
		if (i < i_length) {
			res[i] += pi_number[i];
		}
		if (i < pcNewVal.i_length) {
			res[i] += pcNewVal.pi_number[i];
		}
	}

	return CNumber(number_system, newLength, res, positive);
}

CNumber CNumber::operator-(const CNumber& pcNewVal) const {
	if (differentNSystem(pcNewVal)) {
		return *this - pcNewVal.baseConversion(number_system);
	}
	else if (positive != pcNewVal.positive) {
		return *this + pcNewVal.negate();
	}

	
	if (*this == pcNewVal) {
		int* temp = new int[1];
		temp[0] = 0;
		return CNumber( number_system, 1, temp, positive );
	}

	bool isThisGreater = (*this >= pcNewVal);
	bool reverse = !positive;
	if (reverse) isThisGreater = !isThisGreater;

	//jesli oba dodatnie to logika bedzie inna niz jesli dwa ujemne 
	const CNumber& larger = isThisGreater ? *this : pcNewVal;
	const CNumber& smaller = isThisGreater ? pcNewVal : *this;

	bool resultP = (isThisGreater == positive);

	int newLength = larger.i_length;
	int* res = new int[newLength];

	int borrow = 0;
	for (int i = 0; i < newLength; i++) {
		int sub = borrow;
		if (i < larger.i_length) sub += larger.pi_number[i];
		if (i < smaller.i_length) sub -= smaller.pi_number[i];

		if (sub < 0) {
			sub += number_system;
			borrow = - 1;
		}
		else {
			borrow = 0;
		}
		
		res[i] = sub;
	}

	return CNumber( number_system, newLength, res, resultP );
}
CNumber CNumber::operator*(const CNumber& pcNewVal) const {
	if (differentNSystem(pcNewVal)) {
		return *this * pcNewVal.baseConversion(number_system);
	}
	bool resultP = (positive == pcNewVal.positive);

	int newLength = i_length + pcNewVal.i_length;

	int* res = new int[newLength];

	for (int i = 0; i < newLength; i++) {
		res[i] = 0;
	}

	for (int i = 0; i < i_length; i++) {
		for (int j = 0; j < pcNewVal.i_length; j++) {
			res[i + j] += pi_number[i] * pcNewVal.pi_number[j];
		}
	}

	return CNumber(number_system, newLength, res, resultP);
}
CNumber CNumber::operator/(const CNumber& pcNewVal) const {
	return divide(pcNewVal).first;
}
CNumber CNumber::operator%(const CNumber& pcNewVal) const {
	return divide(pcNewVal).second;
}

CNumber CNumber::baseConversion(const int iNewSystem) const {
	CNumber temp = *this;
	temp.positive = true;

	CNumber newBase(number_system, 1);
	newBase = iNewSystem;

	CNumber zero(number_system, 1);
	zero = 0;

	if (temp == zero) {
		int* res = new int[1];
		res[0] = 0;
		return CNumber(iNewSystem, 1, res, true);
	}

	int newLength = 0;
	CNumber countTemp = temp;
	while (countTemp > zero) {
		countTemp = countTemp / newBase;
		newLength++;
	}

	int* res = new int[newLength];

	for (int i = 0; i < newLength; i++) {
		CNumber remainder = temp % newBase;
		if (remainder.i_length > 0) {
			res[i] = remainder.pi_number[0];
		}
		else {
			res[i] = 0;
		}
		temp = temp / newBase;
	}

	return CNumber(iNewSystem, newLength, res, positive);
}

CNumber CNumber::operator-() const {
	CNumber res(number_system, 1);
	res = 0;
	if (*this == res) return *this;
	return { number_system ,i_length, copyTable(pi_number, i_length), !positive };
}

CNumber CNumber::operator^(const CNumber& pcNewVal) const {
	if (differentNSystem(pcNewVal)) {
		return *this ^ pcNewVal.baseConversion(number_system);
	}

	int newLength = i_length;
	int* res = new int[newLength];


	int count = 0;

	for (int i = 0; i < i_length; i++) {
		res[i] = 0;

		if (pi_number[i] != pcNewVal.pi_number[i]) {
			res[i-count] = pi_number[i];
		}
		else {
			count++;
		}
	}

	return CNumber(number_system, newLength, res, positive);
}


CNumber CNumber::operator&(const CNumber& pcNewVal) const {
	if (differentNSystem(pcNewVal)) {
		return *this & pcNewVal.baseConversion(number_system);
	}

	CNumber start = *this;
	CNumber end = pcNewVal;

	int newLength = start.i_length + pcNewVal.i_length;

	int* res = new int[newLength];
	
	for (int i = 0; i < end.i_length; i++) {
		res[i] = end.pi_number[i];
	}
	for (int i = 0; i < start.i_length; i++) {
		res[i + end.i_length] = start.pi_number[i];
	}

	return CNumber(number_system, newLength, res, positive);
}

//CNumber CNumber::operator$(const CNumber& pcNewVal) const {
//	if (differentNSystem(pcNewVal)) {
//		return *this $ pcNewVal.baseConversion(number_system);
//	}
//
//	else {
//
//		CNumber start = *this;
//		CNumber end = pcNewVal;
//		int newLength = start.i_length - end.i_length;
//
//		int i = 0;
//		while (i < end.i_length && start.pi_number[i + end.i_length] == end.pi_number[i]) {
//			i++;
//		}
//		//jelsi koncowk ktora chcemy odjac z tablicy jest rowna koncowce calej tablicy zmienaimy rozmiar i tyle 
//		//w przeciwnym razie poprstu zwracmy tablice;
//		if (i == end.i_length) {
//
//			if (start.setSize(newLength)) {
//				return start;
//			}
//			else {
//				CNumber res(number_system, 1);
//				res = 0;
//				return res;
//			}
//			
//		}
//		else {
//			return start;
//		}
//		
//	}
//}

pair<CNumber, CNumber> CNumber::divide(const CNumber& pcNewVal) const {
	if (pcNewVal.pi_number[pcNewVal.i_length - 1] == 0) {
		throw runtime_error("Dzielenie przez zero");
	}

	if (differentNSystem(pcNewVal)) {
		return divide(pcNewVal.baseConversion(number_system));
	}

	CNumber divisor = pcNewVal;
	divisor.positive = true;

	CNumber dividend = *this;
	dividend.positive = true;

	if (dividend < divisor) {
		CNumber quotient(number_system, 1);
		quotient = 0;
		return make_pair(quotient, dividend);
	}

	bool resultP = (positive == pcNewVal.positive);

	CNumber quotient(number_system, i_length);
	quotient.resetArray();
	quotient.positive = resultP;

	CNumber remainder(number_system, 1);
	remainder.positive = 0;

	for (int i = dividend.i_length - 1; i >= 0; i--) {
		remainder = remainder * CNumber(number_system, 1, new int[1] {number_system}, true);
		remainder = remainder + CNumber(number_system, 1, new int[1] {dividend.pi_number[i]}, true);

		int count = 0;
		while (remainder >= divisor) {
			remainder = remainder - divisor;
			count++;
		}
		quotient.pi_number[i] = count;
	}

	quotient.deleteZeros();
	remainder.deleteZeros();
	return make_pair(quotient, remainder);
}

bool CNumber::operator<(const CNumber& pcNewVal) const
{
	return !(*this >= pcNewVal);
}

bool CNumber::operator>(const CNumber& pcNewVal) const
{
	return !(*this <= pcNewVal);
}

bool CNumber::operator==(const CNumber& pcNewVal) const
{
	CNumber thisCopy = *this;
	CNumber pcNewValCopy = pcNewVal;

	if (differentNSystem(pcNewValCopy)) {
		pcNewValCopy = pcNewValCopy.baseConversion(thisCopy.number_system);
	}

	thisCopy.deleteZeros();
	pcNewValCopy.deleteZeros();

	if (thisCopy.positive != pcNewValCopy.positive) return false;
	if (thisCopy.i_length != pcNewValCopy.i_length) return false;
	for (int i = 0; i < thisCopy.i_length; i++) {
		if (thisCopy.pi_number[i] != pcNewValCopy.pi_number[i]) return false;
	}
	return true;
}

bool CNumber::operator<=(const CNumber& pcNewVal) const
{
	CNumber thisCopy = *this;
	CNumber pcNewValCopy = pcNewVal;

	if (differentNSystem(pcNewVal)) {
		pcNewValCopy = pcNewValCopy.baseConversion(thisCopy.number_system);
	}

	thisCopy.deleteZeros();
	pcNewValCopy.deleteZeros();

	if (thisCopy.positive && !pcNewValCopy.positive) return false;
	if (!thisCopy.positive && pcNewValCopy.positive) return true;
	if (thisCopy.positive) {
		if (thisCopy.i_length < pcNewValCopy.i_length) return true;
		if (thisCopy.i_length > pcNewValCopy.i_length) return false;

		for (int i = thisCopy.i_length - 1; i >= 0; i--) {
			if (thisCopy.pi_number[i] < pcNewValCopy.pi_number[i]) return true;
			if (thisCopy.pi_number[i] > pcNewValCopy.pi_number[i]) return false;
		}
		return true;
	}
	else {
		if (thisCopy.i_length > pcNewValCopy.i_length) return true;
		if (thisCopy.i_length < pcNewValCopy.i_length) return false;

		for (int i = thisCopy.i_length - 1; i >= 0; i--) {
			if (thisCopy.pi_number[i] > pcNewValCopy.pi_number[i]) return true;
			if (thisCopy.pi_number[i] < pcNewValCopy.pi_number[i]) return false;
		}

		return true;
	}
}

bool CNumber::operator>=(const CNumber& pcNewVal) const
{
	return pcNewVal <= *this;
}

void CNumber::fixArray() {
	int i = 0;
	while (i < i_length) {
		int& cell = pi_number[i];

		if (cell < 0) {
			cell = -cell;
		}

		if (cell >= number_system) {
			int surplus = cell / number_system;
			cell %= number_system;

			if (i == i_length - 1 ) {
				int temp = surplus;
				int additionalLength = 0;

				while (temp > 0) {
					additionalLength++;
					temp /= number_system;
				}

				setSize(i_length + additionalLength);
			}

			pi_number[i+1] += surplus;
		}
		i++;
	}
	deleteZeros();
}


void CNumber::deleteZeros() {
	int originaLength = i_length;
	trimZerosNoRealloc();

	if (i_length < originaLength) {
		int* temp = copyTable(pi_number, i_length);
		delete[] pi_number;
		pi_number = temp;
	}
}
void CNumber::trimZerosNoRealloc() {
	while (pi_number[i_length - 1] == 0 && i_length > 1) {
		i_length--;
	}
}

string CNumber::sToStr() {
	string res;
	if (!positive) {
		res += "-";
	}
	for (int i = i_length - 1; i >= 0; i--) {
		res += to_string(pi_number[i]) + " ";
	}
	return res;
}

void CNumber::resetArray() {
	for (int i = 0; i < i_length; i++) {
		pi_number[i] = 0;
	}
}

CNumber CNumber::negate() const {
	int* res = copyTable(pi_number, i_length);
	return CNumber( number_system, i_length, res, !positive );
}

bool CNumber::setSize(int iSize) {
	if (iSize < 1) {
		return false;
	}
	int* temp = new int[iSize];
	if (iSize > i_length) {
		for (int i = 0; i < i_length; i++) {
			temp[i] = pi_number[i];
		}
		for (int i = i_length; i < iSize; i++) {
			temp[i] = 0;
		}
	}
	else {
		for (int i = 0; i < iSize; i++) {
			temp[i] = pi_number[i];
		}
	}
	delete[] pi_number;
	i_length = iSize;
	pi_number = temp;
	return true;
}

bool CNumber::differentNSystem(const CNumber& pcNewVal) const {
	return number_system != pcNewVal.number_system;
}