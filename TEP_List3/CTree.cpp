#include "CTree.h"
#include "CNode.h"
#include "CNodeVar.h"
#include <sstream>
CTree::CTree() {
	root = NULL;
}

CTree::~CTree() {
	delete root;
}

//-------------------Tworzenie drzewa ENTER --------------------------------------------------
CError CTree::create(const vector<string>& tokens) {
	//tworzy drzewo jesli wymaga fixowania to to robimy
	CError error = eLoad(tokens);

	if (error.lackArguments()) {
		fixTree();
	}

	return error;
}
CError CTree::eLoad(const vector<string>& tokens) {
	delete root;
	root = NULL;
	variable.clear();

	if (tokens.empty()) {
		return CError();
	}

	CError error;
	int index = 0;

	root = CNode::createNode(this, tokens, index, error);


	//jesli za duzo znakow sprawdzamy
	if (error.isSuccess() && index < tokens.size()) {
		return CError(index,false, "Error: TOO many unique variables");
	}

	//inaczej sukcess
	return error;
}

void CTree::fixTree() {
	//dodajemy wszedzie jedynki jako CNodeAbs gdzie sa potrzebne
	if (root != NULL) {
		root->fixNodes();
	}
}
//--------------------------------------COMP--------------------------------------------------
//co jesli lisciem jest variabla i zastepujemy go musimy usunac ta variable z vector variable Tree 
//dodanie liczby do CTree variable a nastepnie 

CError CTree::comp(const vector<string>& tokens) {
	if (tokens.size() != variable.size()) return CError(1, false, "Error: Wrong quantity of variables!");

	//sprawdzic czy typu ABS
	for (int i = 0; i < tokens.size(); i++) {
		if (!CNode::isTypeOfAbs(tokens[i])) {
			return CError(i, false, "Error: Variable isn't double");
		}
	}

	for (int i = 0; i < variable.size(); i++) {
		variable[i].second->setValue(tokens[i]);
	}

	return CError();
}

string CTree::evaluate() const {
	if (root == NULL) return "Brak roota.";

	double res = root->evaluate();
	stringstream ss;
	ss << res;
	return ss.str();
}
//----------------------------------------Join-------------------------------------------------

CError CTree::join(const vector<string>& tokens) {
	if (root == NULL) {
		return CError(-1, false, "Cannot join to an empty tree.");
	}
	
	CError error;
	int index = 0;
	CNode* newNode = CNode::createNode(this, tokens, index, error);
	
	if (error.lackArguments()) {
		newNode->fixNodes();
	}
	else if (!error.isSuccess()) {
		delete newNode;
		return error;
	}

	//znajdz lisc
	CNode* leaf = findLeaf(root);
	if (leaf == NULL) {
		delete newNode;
		return CError(-1, false, "Could not find a leaff in existing ");
	}

	//zamien lisc na noda
	CNode* parent = leaf->getParent();
	if (parent != NULL) {
		if (!parent->replaceChild(leaf, newNode)) {
			delete newNode;
			return CError(-1, false, "Failed to replace child in parent node.");
		}
	}
	else {
		delete root;
		root = newNode;
	}

	delete leaf;
	return CError();
}

CNode* CTree::findLeaf(CNode* node) {
	if (node == NULL || node->isLeaf()) {
		return node;
	}

	for (int i = 0; i < node->getExpectedChildrenCount(); i++) {
		CNode* leaf = findLeaf(node->getChild(i));
		if (leaf != NULL) {
			return leaf;
		}
	}

	return NULL;
}

//---------------------------------------FUNKCJE POMOCNICZE------------------------------------

CNodeVar* CTree::findVariable(const string& token) {
	for (vector<pair<string, CNodeVar*>>::iterator it = variable.begin(); it != variable.end(); it++){

		if (it->first == token) {
			return it->second;
		}
	}

	return NULL;
}
string CTree::findVariableName(const CNodeVar* node) const {
	for (vector<pair<string, CNodeVar*>>::const_iterator it = variable.begin(); it != variable.end(); it++) {
		if (it->second == node) {
			return it->first;
		}
	}
	return "[unkown variable]";
}
void CTree::registerVariable(const string& token, CNodeVar* node) {
	
	variable.push_back(make_pair(token, node));
}

string CTree::printVariables() {

	stringstream ss;
	for (vector<pair<string, CNodeVar*>>::iterator it = variable.begin(); it != variable.end(); it++) {
		ss << it->first << " ";
	}
	return ss.str();
}

string CTree::treeToString() const {
	return root->nodeToStr();
}