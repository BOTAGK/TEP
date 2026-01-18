#pragma once
#include "CLogger.h"
#include <vector>
using std::vector;

class CTree;
class CError;


template <typename T, typename E>
class CResult
{
public:
	CResult(const T& cValue);
	CResult(E* pcError);
	CResult(const vector<E*>& vErrors);
	CResult(const CResult<T, E>& cOther);
	~CResult();
	static CResult<T, E> cOk(const T& cValue);
	static CResult<T, E> cFail(E* pcError);
	static CResult<T, E> cFail(const vector<E*>& vErrors);
	CResult<T, E>& operator=(const CResult<T, E>& cOther);
	bool bIsSuccess();
	T cGetValue();
	vector<E*>& vGetErrors();

	vector<E*> vExtractErrors();
private:
	void clear();


	T* pc_value;
	vector<E*> v_errors;
};

template <typename E>
class CResult<void, E>
{
public:
	CResult();
	CResult(E* pcError);
	CResult(const vector<E*>& vErrors);
	CResult(const CResult<void, E>& cOther);
	~CResult();
	static CResult<void, E> cOk();
	static CResult<void, E> cFail(E* pcError);
	static CResult<void, E> cFail(const vector<E*>& vErrors);
	CResult<void, E>& operator=(const CResult<void, E>& cOther);
	bool bIsSuccess();
	vector<E*>& vGetErrors();
	vector<E*> vExtractErrors();
private:
	void clear();

	vector<E*> v_errors;
};

template <typename T, typename E>
CResult<T, E>::CResult(const T& cValue) {
	pc_value = new T(cValue);
	CLogger::vLogSave(cValue);
}

template <typename T, typename E>
CResult<T, E>::CResult(E* pcError) {
	pc_value = NULL;
	v_errors.push_back(pcError);
	CLogger::vLogFailure(v_errors);
}

template <typename T, typename E>
CResult<T, E>::CResult(const vector<E*>& vErrors) {
	pc_value = NULL;
	v_errors = vErrors;
}

template <typename T, typename E>
CResult<T, E>::CResult(const CResult<T, E>& cOther) {
	if (cOther.pc_value != NULL) {
		pc_value = new T(*(cOther.pc_value));
	}
	else {
		pc_value = NULL;
		
		for (int i = 0; i < cOther.v_errors.size(); i++) {
			v_errors.push_back(new E( *(cOther.v_errors[i])));
		}
	}
}

template <typename T, typename E>
CResult<T, E>::~CResult() {
	clear();
}

template <typename T, typename E>
CResult<T, E> CResult<T, E>::cOk(const T& cValue) {
	return CResult<T, E>(cValue);
}

template <typename T, typename E>
CResult<T, E> CResult<T, E>::cFail(E* pcError) {
	return CResult<T, E>(pcError);
}

template <typename T, typename E>
CResult<T, E> CResult<T, E>::cFail(const vector<E*>& vErrors) {
	return CResult<T, E>(vErrors);
}

template <typename T, typename E>
CResult<T, E>& CResult<T, E>::operator=(const CResult<T, E>& cOther) {

	if (this == &cOther) {
		return *this;
	}

	clear();

	if (cOther.pc_value != NULL) {
		pc_value = new T(*(cOther.pc_value));
	}
	else {
		for (int i = 0; i < cOther.v_errors.size(); i++) {
			v_errors.push_back(new E(*(cOther.v_errors[i])));
		}
	}

	return *this;
}

template <typename T, typename E>
bool CResult<T, E>::bIsSuccess() {
	return pc_value != NULL;
}

template <typename T, typename E>
T CResult<T, E>::cGetValue()
{
	return *pc_value;
}

template <typename T, typename E>
vector<E*>& CResult<T, E>::vGetErrors() {
	return v_errors;
}
template <typename T, typename E>
void CResult<T, E>::clear() {
	if (pc_value != NULL) {
		delete pc_value;
		pc_value = NULL;
	}
	for (int i = 0; i < v_errors.size(); i++) {
		delete v_errors[i];
	}
	v_errors.clear();
}

template <typename T, typename E>
vector<E*> CResult<T, E>::vExtractErrors() {
	vector<E*> vTemp = v_errors;
	v_errors.clear();
	return vTemp;
}

template<typename E>
CResult<void, E>::CResult() {
	CLogger::vLogSuccess();
}

template<typename E>
CResult<void, E>::CResult(E* pcError) {
	v_errors.push_back(pcError);
	CLogger::vLogFailure(v_errors);
}

template<typename E>
CResult<void, E>::CResult(const vector<E*>& vErrors) {
	v_errors = vErrors;
}

template<typename E>
CResult<void, E>::CResult(const CResult<void, E>& cOther) {
	for (int i = 0; i < cOther.v_errors.size(); i++) {
		v_errors.push_back(new E(*(cOther.v_errors[i])));
	}
}

template<typename E>
CResult<void, E>::~CResult() {
	clear();
}

template<typename E>
CResult<void, E> CResult<void, E>::cOk() {
	return CResult<void, E>();
}

template<typename E>
CResult<void, E> CResult<void, E>::cFail(E* pcError) {
	return CResult<void, E>(pcError);
}

template<typename E>
CResult<void, E> CResult<void, E>::cFail(const vector<E*>& vErrors) {
	return CResult<void, E>(vErrors);
}

template<typename E>
CResult<void, E>& CResult<void, E>::operator=(const CResult<void, E>& cOther) {
	if (this == &cOther) return *this;

	clear();

	for (int i = 0; i< cOther.v_errors.size(); i++) {
		v_errors.push_back(new E(*(cOther.v_errors[i])));
	}

	return *this;
}

template<typename E>
bool CResult<void, E>::bIsSuccess() {
	return v_errors.empty();
}

template<typename E>
vector<E*>& CResult<void, E>::vGetErrors() {
	return v_errors;
}

template<typename E>
void CResult<void, E>::clear() {
	for (int i = 0; i < v_errors.size(); i++) {
		delete v_errors[i];
	}
	v_errors.clear();
}

template <typename E>
vector<E*> CResult<void, E>::vExtractErrors() {
	vector<E*> vTemp = v_errors;
	v_errors.clear();
	return vTemp;
}

template <>
CResult<CTree*, CError> CResult<CTree*, CError>::cFail(const vector<CError*>& vErrors);
template<>
CResult<CTree*, CError> CResult <CTree*, CError>::cFail(CError* error);
