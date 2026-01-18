#include "CTree.h"
#include "CNode.h"
#include "CNodeVar.h"
#include <sstream>

int CTree::iCopyCount = 0;
int CTree::iMoveCount = 0;

CTree::CTree() {
	root = NULL;
}

CTree::CTree(const CTree& other) {
	iCopyCount++;

	root = NULL;
	if (other.root != NULL) {
		root = other.root->clone(this);
	}
}

CTree::~CTree() {
	delete root;
}

CTree::CTree(CTree&& pcOther) {

	iMoveCount++;

	root = pcOther.root;
	variable = move(pcOther.variable);

	pcOther.root = NULL;
	pcOther.variable.clear();
}

CTree& CTree::operator=(CTree&& pcOther) {
	if (this == &pcOther) {
		return *this;
	}

	iMoveCount++;

	delete root;
	root = pcOther.root;
	variable = move(pcOther.variable);

	pcOther.root = NULL;
	pcOther.variable.clear();

	return *this;
}

//-------------------Tworzenie drzewa ENTER --------------------------------------------------
CResult<CTree*, CError> CTree::create(const vector<string>& tokens) {
	CTree* tree = new CTree();

	CResult<void, CError> loadResult = tree->eLoad(tokens);

	if (loadResult.bIsSuccess()) {
		return CResult<CTree*, CError>::cOk(tree);
	}
	else {
		delete tree;
		return CResult<CTree*, CError>::cFail(loadResult.vExtractErrors());
	}
}
CResult<void, CError> CTree::eLoad(const vector<string>& tokens) {
	if (root != NULL) {
		delete root;
		root = NULL;
	}
	variable.clear();

	if (tokens.empty()) {
		return CResult<void, CError>::cOk();
	}

	int index = 0;

	CResult<CNode*, CError> result = CNode::createNode(this, tokens, index);


	//jesli za duzo znakow sprawdzamy
	if (!result.bIsSuccess()) {
		return CResult<void, CError>::cFail(result.vExtractErrors());
	}

	CNode* newRoot = result.cGetValue();

	if (index < tokens.size()) {
		delete newRoot;
		return CResult<void, CError>::cFail(new CError(index, "Error: Too many unique variables (extra tokens)"));
	}

	root = newRoot;
	return CResult<void, CError>::cOk();
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

CResult<void, CError> CTree::comp(const vector<string>& tokens) {
	if (tokens.size() != variable.size()) {
		return CResult<void, CError>::cFail(new CError(1, "Error: Wrong quantity of variables!"));
	}

	//sprawdzic czy typu ABS
	for (int i = 0; i < tokens.size(); i++) {
		if (!CNode::isTypeOfAbs(tokens[i])) {
			return CResult<void, CError>::cFail(new CError(i, "Error: Variable isn't double"));
		}
	}

	for (int i = 0; i < variable.size(); i++) {
		variable[i].second->setValue(tokens[i]);
	}

	return CResult<void, CError>::cOk();
}

string CTree::evaluate() const {
	if (root == NULL) return "Brak roota.";

	double res = root->evaluate();
	stringstream ss;
	ss << res;
	return ss.str();
}
//----------------------------------------Join-------------------------------------------------

CResult<void, CError> CTree::join(const vector<string>& tokens) {
	if (root == NULL) {
		return CResult<void, CError>::cFail(new CError(-1, "Cannot join to an empty tree."));
	}

	int index = 0;

	CResult<CNode*, CError> result = CNode::createNode(this, tokens, index);

	if (!result.bIsSuccess()) {
		return CResult<void, CError>::cFail(result.vExtractErrors());
	}

	CNode* newNode = result.cGetValue();

	//znajdz lisc
	CNode* leaf = findLeaf(root);
	if (leaf == NULL) {
		delete newNode;
		return CResult<void, CError>::cFail(new CError(-1, "Could not find a leaf in existing tree"));
	}

	for(int i = 0; i < variable.size(); i++){
		if (variable[i].second == leaf) {
			variable.erase(variable.begin() + i);
		}
	}


	//zamien lisc na noda
	CNode* parent = leaf->getParent();
	if (parent != NULL) {
		if (!parent->replaceChild(leaf, newNode)) {
			delete newNode;
			return CResult<void, CError>::cFail(new CError(-1, "Failed to replace child in parent node."));
		}
	}
	else {
		root = newNode;
	}

	delete leaf;
	return CResult<void, CError>::cOk();
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

//----------------------------------------Modyfikacja---------------------------------------

int CTree::countLeafs() {
	int count = 0;
	if (root != NULL) {
		countLeafsRec(root, count);
	}
	
	return count;
}

void CTree::countLeafsRec(CNode* node, int& count) {
	if (node->isLeaf()) {
		count++;
		return;
	}

	for (int i = 0; i < node->getExpectedChildrenCount(); i++) {
		countLeafsRec(node->getChild(i), count);
	}
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
	if (root != NULL) {
		return root->nodeToStr();
	}
	else {
		return "NULL";
	}
	
}

CTree& CTree::operator=(const CTree& other) {
	if (this == &other) {
		return *this;
	}

	iCopyCount++;

	delete root;
	root = NULL;
	variable.clear();

	if (other.root != NULL) {
		root = other.root->clone(this);
	}

	return *this;
}

CTree CTree::operator+(const CTree& other) const {
	CTree result = *this;

	if (other.root == NULL) {
		return result;
	}

	string otherTree = other.treeToString();
	vector<string> tokens;
	stringstream ss(otherTree);
	string token;
	while (ss >> token) {
		tokens.push_back(token);
	}

	result.join(tokens);

	return result;
}