#include "CNode.h"
#include "CNodeOp.h"
#include "CNodeVar.h"
#include "CNodeAbs.h"

CNode::CNode() {
	parent = NULL;
}
CNode::~CNode() {
	for (size_t i = 0; i < children.size(); i++) {
		delete children[i];
	}
}

CNode* CNode::createNode(CTree* tree, const vector<string>& tokens, int& vectorIdx, CError& error) {
	if (!error.isSuccess()) {
		return NULL;
	}

	if (vectorIdx >= tokens.size()) {
		error = CError(vectorIdx, true, "Unexpected end, expected more arguments");
		return NULL;
	}

	string currentToken = tokens[vectorIdx];
	vectorIdx++;

	CNode* newNode = NULL;

	if (isTypeOfAbs(currentToken)) {
		newNode = new CNodeAbs(currentToken);
	}
	else if (isTypeOfOp(currentToken)) {
		newNode = CNodeOp::create(currentToken);
	}
	else if (isTypeOfVar(currentToken)) {
		//zapytanie w drzewiedo i czy juz istnieje 
		newNode = CNodeVar::create(currentToken, tree);
	}
	else {
		error = CError(vectorIdx, false, "Unkown token: " + currentToken);
		return NULL;
	}

	int childCount = newNode->getExpectedChildrenCount();
	for (int i = 0; i < childCount; i++) {

		CNode* child = createNode(tree, tokens, vectorIdx, error);

		if (child == NULL) {
			if (error.lackArguments()) {
				return newNode;

			}
			delete newNode;
			return NULL;
		}

		newNode->addChild(child);
	}

	return newNode;
}

void CNode::addChild(CNode* child) {
	if (child != NULL) {
		children.push_back(child);
		child->parent = this;
	}
}

void CNode::fixNodes() {
	for (size_t i = 0; i < children.size(); i++) {
		children.at(i)->fixNodes();
	}
	
	int expectedCount = getExpectedChildrenCount();
	while(children.size() < expectedCount) {
		CNode* newChild = new CNodeAbs("1");
		addChild(newChild);
	}
}

bool CNode::isTypeOfAbs(const string& token){
	if (token.empty()) return false;

	char* pEnd;
	double val = strtod(token.c_str(), &pEnd);

	return *pEnd == '\0';
}
bool CNode::isTypeOfVar(const string& token) {
	if (token.empty()) return false;

	return true;
}
bool CNode::isTypeOfOp(const string& token) {
	const string supportedOps[] = { "+", "-", "*", "/", "sin", "cos" };
	
	int numberOfOps = sizeof(supportedOps) / sizeof(supportedOps[0]);

	for (int i = 0; i < numberOfOps; i++) {
		if (token == supportedOps[i]) {
			return true;
		}
	}

	return false;
}

int CNode::getExpectedChildrenCount() const { return 0; }

bool CNode::isLeaf() const {
	return children.empty();
}

CNode* CNode::getParent() const {
	return parent;
}

int CNode::getChildrenCount() const {
	return children.size();
}

CNode* CNode::getChild(int index) const {
	if (index >= 0 && index < children.size()) {
		return children[index];
	}
	return NULL;
}

bool CNode::replaceChild(CNode* oldC, CNode* newC) {
	for (size_t i = 0; i < children.size(); i++) {
		if (children[i] == oldC) {
			children[i] = newC;
			newC->parent = this;
			return true; 
		}
	}
	return false;
}



