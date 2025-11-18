#pragma once
#include <string>
#include "CTree.h"
#include <map>
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

	typedef void (CInterface::* MethodPtrNoArg)();
	typedef void (CInterface::* MethodPtrWithArg)(const vector<string> tokens);

	map<string, MethodPtrNoArg> map_without_arg;
	map<string, MethodPtrWithArg> map_with_arg;

	CTree tree;
	bool quitFlag;
};

