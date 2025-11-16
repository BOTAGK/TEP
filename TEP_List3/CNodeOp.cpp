#include "CNodeOp.h"
using namespace std;

CNodeOp* CNodeOp::create(string& token) {
	if (token == "+") return new CNodeOpAdd();
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

string CNodeOpAdd::nodeToStr() const {
	if (!isChildFull()) return NULL;
	return "+ " + children[0]->nodeToStr() + " " + children[1]->nodeToStr();
}

double CNodeOpSub::evaluate() const {
	if (!isChildFull()) return NULL;

	return children[0]->evaluate() - children[1]->evaluate() ;
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

double CNodeOpDiv::evaluate() const {
	if (!isChildFull()) return NULL;

	return children[0]->evaluate() / children[1]->evaluate();
}

string CNodeOpDiv::nodeToStr() const {
	if (!isChildFull()) return NULL;
	return "/ " + children[0]->nodeToStr() + " " + children[1]->nodeToStr();
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

double CNodeOpCos::evaluate() const {
	if (!isChildFull()) return NULL;

	return cos(children[1]->evaluate());
}

string CNodeOpCos::nodeToStr() const {
	if (!isChildFull()) return NULL;
	return "cos " + children[0]->nodeToStr();
}

int CNodeOpCos::getExpectedChildrenCount() const { return 1; }




