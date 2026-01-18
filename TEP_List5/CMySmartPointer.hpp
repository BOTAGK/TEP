#pragma once
#include <iostream>
#include <vector>
#include "CRefCounter.h"

using namespace std;

template <typename T>
class CMySmartPointer
{
public:
	CMySmartPointer(T* pcPointer);
	CMySmartPointer(const CMySmartPointer& pcOther);
	~CMySmartPointer();

	CMySmartPointer& operator=(const CMySmartPointer& pcOther);
	
	T& operator*();
	T* operator->();
private:

	CRefCounter* pc_counter;
	T* pc_pointer;

	vector<CMySmartPointer<T>*>* address;
};

template<typename T>
CMySmartPointer<T>::CMySmartPointer(T* pcPointer) {
	
	address = new vector<CMySmartPointer<T>*>;
	address->push_back(this);

	pc_pointer = pcPointer;	
	pc_counter = new CRefCounter();
	pc_counter->iAdd();
}

template<typename T>
CMySmartPointer<T>::CMySmartPointer(const CMySmartPointer& pcOther) {

	address = pcOther.address;
	address -> push_back(this);

	pc_pointer = pcOther.pc_pointer;
	pc_counter = pcOther.pc_counter;
	pc_counter->iAdd();
}

template<typename T>
CMySmartPointer<T>::~CMySmartPointer() {
	
	auto EndIter  = find(address->begin(), address->end(), this);
	address->erase(address->begin(),EndIter);

	if (pc_counter->iDec() == 0) {
		delete pc_pointer;
		delete pc_counter;
		delete address;
	}
}

template<typename T>
CMySmartPointer<T>& CMySmartPointer<T>::operator=(const CMySmartPointer& pcOther) {
	if (this == &pcOther) {
		return *this;
	}

	if (pc_counter->iDec() == 0) {
		delete pc_pointer;
		delete pc_counter;
	}

	pc_pointer = pcOther.pc_pointer;
	pc_counter = pcOther.pc_counter;
	pc_counter->iAdd();

	return *this;
}

template<typename T>
T& CMySmartPointer<T>::operator*() {
	 return(*pc_pointer); 
}

template<typename T>
T* CMySmartPointer<T>::operator->() {
	return(pc_pointer);
}