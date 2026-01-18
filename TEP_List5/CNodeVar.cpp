#include "CNodeVar.h"
#include "CTree.h"

CNodeVar::CNodeVar(CTree* tree) : pc_Tree(tree) {
	value = 0.0;
}
CNodeVar::~CNodeVar() {}

CNodeVar* CNodeVar::create(const string& token, CTree* tree) {
	if (tree == NULL) return NULL;

	CNodeVar* existingNode = tree->findVariable(token);

	if (existingNode != NULL) {
		return existingNode;
	}
	else {
		CNodeVar* newNode = new CNodeVar(tree);

		tree->registerVariable(token, newNode);
		return newNode;
	}
}

string CNodeVar::nodeToStr() const {
	if (pc_Tree != NULL) {
		return pc_Tree->findVariableName(this);
	}
	return "[unbound_var]";
}

double CNodeVar::evaluate() const {
	return value;
}

void CNodeVar::setValue(const string& val) {
	char* pEnd;

	value = strtod(val.c_str(), &pEnd);

	if (*pEnd != '\0') {
		value = 0.0;
	}
}

CNode* CNodeVar::clone(CTree* newOwner) const {
	string varName = pc_Tree->findVariableName(this);

	return CNodeVar::create(varName, newOwner);
}