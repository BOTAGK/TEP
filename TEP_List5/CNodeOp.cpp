#include "CNodeOp.h"
#include <iostream>
using namespace std;

CNodeOp* CNodeOp::create(string& token) {
	if (token == "+") return new CNodeOpAdd;
	if (token == "-") return new CNodeOpSub;
	if (token == "*") return new CNodeOpMult;
	if (token == "/") return new CNodeOpDiv;
	if (token == "cos") return new CNodeOpCos;
	if (token == "sin")	return new CNodeOpSin;
	return NULL;
}

int CNodeOp::getExpectedChildrenCount() const {return 2;}

bool CNodeOp::isChildFull() const {
	return children.size() == getExpectedChildrenCount();
}


double CNodeOpAdd::evaluate() const {
	if (!isChildFull()) return NULL;

	return children[0]->evaluate() + children[1]->evaluate();
}

CNode* CNodeOpAdd::clone(CTree* newOwner) const {
	CNodeOpAdd* newNode = new CNodeOpAdd();
	for (size_t i = 0; i < children.size(); i++) {
		newNode->addChild(children[i]->clone(newOwner));
	}

	return newNode;
}

string CNodeOpAdd::nodeToStr() const {
	if (!isChildFull()) return NULL;
	return "+ " + children[0]->nodeToStr() + " " + children[1]->nodeToStr();
}

double CNodeOpSub::evaluate() const {
	if (!isChildFull()) return NULL;

	return children[0]->evaluate() - children[1]->evaluate() ;
}

CNode* CNodeOpSub::clone(CTree* newOwner) const {
	CNodeOpSub* newNode = new CNodeOpSub();
	for (size_t i = 0; i < children.size(); i++) {
		newNode->addChild(children[i]->clone(newOwner));
	}

	return newNode;
}

string CNodeOpSub::nodeToStr() const {
	if (!isChildFull()) return NULL;
	return "- " + children[0]->nodeToStr() + " " + children[1]->nodeToStr();
}

double CNodeOpMult::evaluate() const {
	if (!isChildFull()) return NULL;

	return children[0]->evaluate() * children[1]->evaluate();
}

string CNodeOpMult::nodeToStr() const {
	if (!isChildFull()) return NULL;
	return "* " + children[0]->nodeToStr() + " " + children[1]->nodeToStr();
}

CNode* CNodeOpMult::clone(CTree* newOwner) const {
	CNodeOpMult* newNode = new CNodeOpMult();
	for (size_t i = 0; i < children.size(); i++) {
		newNode->addChild(children[i]->clone(newOwner));
	}

	return newNode;
}

double CNodeOpDiv::evaluate() const {
	if (!isChildFull()) return NULL;

	if (children[1]->evaluate() == 0.0) {
		cout << "Dzielenie przez zero!" << endl;
		return NULL;
	}

	return children[0]->evaluate() / children[1]->evaluate();
}

string CNodeOpDiv::nodeToStr() const {
	if (!isChildFull()) return NULL;
	return "/ " + children[0]->nodeToStr() + " " + children[1]->nodeToStr();
}

CNode* CNodeOpDiv::clone(CTree* newOwner) const {
	CNodeOpDiv* newNode = new CNodeOpDiv();
	for (size_t i = 0; i < children.size(); i++) {
		newNode->addChild(children[i]->clone(newOwner));
	}

	return newNode;
}

double CNodeOpSin::evaluate() const {
	if (!isChildFull()) return NULL;

	return sin(children[0]->evaluate());
}

string CNodeOpSin::nodeToStr() const {
	if (!isChildFull()) return NULL;
	return "sin " + children[0]->nodeToStr();
}

int CNodeOpSin::getExpectedChildrenCount() const { return 1;}

CNode* CNodeOpSin::clone(CTree* newOwner) const {
	CNodeOpSin* newNode = new CNodeOpSin();
	for (size_t i = 0; i < children.size(); i++) {
		newNode->addChild(children[i]->clone(newOwner));
	}

	return newNode;
}

double CNodeOpCos::evaluate() const {
	if (!isChildFull()) return NULL;

	return cos(children[1]->evaluate());
}

string CNodeOpCos::nodeToStr() const {
	if (!isChildFull()) return NULL;
	return "cos " + children[0]->nodeToStr();
}

int CNodeOpCos::getExpectedChildrenCount() const { return 1; }

CNode* CNodeOpCos::clone(CTree* newOwner) const {
	CNodeOpCos* newNode = new CNodeOpCos();
	for (size_t i = 0; i < children.size(); i++) {
		newNode->addChild(children[i]->clone(newOwner));
	}

	return newNode;
}




