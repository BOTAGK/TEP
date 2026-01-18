#pragma once
#include <vector>
#include "CError.h"
#include "CResult.h"
#include <string>

using namespace std;

class CNode;
class CNodeVar;

class CTree
{
public:
	CTree();
	CTree(const CTree& other);
	~CTree();


	static CResult<CTree*, CError> create(const vector<string>& tokens);

	CResult<void, CError> comp(const vector<string>& tokens);
	CResult<void, CError> join(const vector<string>& tokens);

	string evaluate() const;
	
	
	int size();
	
	CNode* findLeaf(CNode* node) ;
	int countLeafs();

	CTree operator+(const CTree& pcNewVal) const;
	CTree& operator=(const CTree& pcNewVal);
	
	CTree(CTree&& pcOther);
	CTree& operator=(CTree&& pcOther);


	string treeToString() const;
	string printVariables();

	CNodeVar* findVariable(const string& token);
	string findVariableName(const CNodeVar* node) const;
	void registerVariable(const string& token, CNodeVar* node);
	
private:

	CResult<void, CError> eLoad(const vector<string>& tokens);
	void fixTree();

	void countLeafsRec(CNode* node, int& coun);
	CNode* root;
	vector<pair<string, CNodeVar*>> variable;
	

};

