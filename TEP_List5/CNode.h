#pragma once
#include "CError.h"
#include "CResult.h"
#include <vector>
#include <string>

class CTree;
using namespace std;


class CNode
{
public:
	CNode();
	virtual ~CNode();
	virtual string nodeToStr() const = 0;
	virtual double evaluate() const = 0;
	virtual int getExpectedChildrenCount() const;
	virtual CNode* clone(CTree* newOwner) const = 0;

	bool isLeaf() const ;
	CNode* getChild(int index) const;
	CNode* getParent() const;
	int getChildrenCount() const;
	bool replaceChild(CNode* oldChild, CNode* newChild);

	void fixNodes();//fill with CNodeVar 1 wszedzie gdize potrzeba
	static CResult<CNode*,CError> createNode(CTree* tree, const vector<string>& tokens, int& vectorIdx);
	static bool isTypeOfVar(const string& token);
	static bool isTypeOfAbs(const string& token);
	static bool isTypeOfOp(const string& token);
	void addChild(CNode* child);
protected:
	vector<CNode*> children;
	CNode* parent;

	
};

