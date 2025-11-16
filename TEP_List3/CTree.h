#pragma once
#include <vector>
#include "CError.h"
#include <string>

using namespace std;

class CNode;
class CNodeVar;

class CTree
{
public:
	CTree();
	~CTree();

	CError comp(const vector<string>& tokens);
	string evaluate() const;
	CError create(const vector<string>& tokens);
	CError eLoad(const vector<string>& tokens);
	int size();
	CError join(const vector<string>& tokens);
	CNode* findLeaf(CNode* node);

	string treeToString() const;
	string printVariables();

	CNodeVar* findVariable(const string& token);
	string findVariableName(const CNodeVar* node) const;
	void registerVariable(const string& token, CNodeVar* node);
	
private:

	void fixTree();
	CNode* root;
	vector<pair<string, CNodeVar*>> variable;
	

};

