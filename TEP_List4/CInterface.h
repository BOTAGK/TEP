#pragma once
#include <string>
#include "CTree.h"
#include <map>
#include <iostream>

using namespace std;

class CInterface
{
public:
	
	CInterface();
	~CInterface();

	bool inputMethod(const string& method, const vector<string> tokens);

	void run();
	void quit();

	void vars();
	void print();

	void enter(const vector<string> tokens);
	void comp(const vector<string> tokens);
	void join(const vector<string> tokens);

private:

	bool undesiredToken(const char& token) const;

	void fixInput(string& input) const;

	template <typename T>
	void printErrors(CResult<T, CError>& result);

	typedef void (CInterface::* MethodPtrNoArg)();
	typedef void (CInterface::* MethodPtrWithArg)(const vector<string> tokens);

	map<string, MethodPtrNoArg> map_without_arg;
	map<string, MethodPtrWithArg> map_with_arg;

	CTree* tree;
	bool quitFlag;
};

template <typename T>
void CInterface::printErrors(CResult<T, CError>& result) {
	vector<CError*>& vErrors = result.vGetErrors();
	for (int i = 0; i < vErrors.size(); i++) {
		cout << vErrors[i]->getMessage() << endl;
	}
}
