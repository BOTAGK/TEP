#include "CInterface.h"
#include <sstream>
#include <iostream>

CInterface::CInterface() {
	tree = NULL;
	quitFlag = false;

	map_without_arg["print"] = &CInterface::print;
	map_without_arg["vars"] = &CInterface::vars;
	map_without_arg["quit"] = &CInterface::quit;

	map_with_arg["enter"] = &CInterface::enter;
	map_with_arg["comp"] = &CInterface::comp;
	map_with_arg["join"] = &CInterface:: join;
}

CInterface::~CInterface() {
	if (tree != NULL) {
		delete tree;
	}
}

void CInterface::run() {
	string line;

	while (!quitFlag && cout << ">" && getline(cin, line)) {
		//czyscimy z niepotrzebnych znakow
		fixInput(line);

		istringstream iss(line);
		string command;
		
		vector<string> tokens;
		string token;

		iss >> command;

		while (iss >> token) {
			tokens.push_back(token);
		}

		if (!inputMethod(command, tokens)) {
			cout << "B³êdna metoda: " << command << "\n" << endl;
		}
	}

	cout << "Koniec programu\n " << endl;
}


void CInterface::enter(const vector<string> tokens) {
	
	CResult<CTree*, CError> result = CTree::create(tokens);
	
	if (result.bIsSuccess()) {
		cout << "Tree created succesfully " << "\n" << endl;
		
		if (tree != NULL) {
			delete tree;
		}
		
		tree = result.cGetValue();
		cout << tree->treeToString() << endl;
	}
	else {
		cout << "Failed to create tree.";
		printErrors(result);
	}
}

void CInterface::comp(const vector<string> tokens) {
	if (tree == NULL) {
		cout << "Error: No tree loaded. Use enter first" << endl;
	}
	else {
		CResult<void, CError> result = tree->comp(tokens);
		if (result.bIsSuccess()) {
			cout <<"Wynik: " << tree->evaluate() << endl;
		}
		else {
			cout << "Error: Failed to compute." << endl;
			printErrors(result);
		}
	}
}

void CInterface::join(const vector<string> tokens) {
	if (tree == NULL) {
		cout << "Error: No tree loaded. Use enter first" << endl;
	}
	else {
		CResult<void, CError> result = tree->join(tokens);
		
		if (result.bIsSuccess()) {
			cout << "Join succesfull." << endl;
			cout << "Wynik laczenia: " << tree->treeToString() << endl;
		}
		else {
			cout << "Error failed to join" << endl;
			printErrors(result);
		}
	}
}

void CInterface::print() {
	cout << tree -> treeToString() << "\n" << endl;
}

void CInterface::vars() {
	cout << tree->printVariables() << "\n" << endl;
}

void CInterface::quit() {
	quitFlag = true;
	cout << "Koniec programu" << endl;
}

bool CInterface::undesiredToken(const char& input) const {
	bool is_allowed = (input >= 'a' && input <= 'z') ||
				      (input >= 'A' && input <= 'Z') ||
					  (input >= '0' && input <= '9') ||
					   input == '+' || input == '-' || input == '*' || input == '/' ||
					   input == ' ' || input == '.' || input == ',';
	return !is_allowed;
}

void CInterface::fixInput(string& input) const {
	int count = input.size();
	int badChar = 0;


	for (int i = 0; i < count; i++) {
		if (undesiredToken(input[i])) {
			cout << "Pozbyto sie znaku: " << input[i] << "\n" << endl;
			badChar++;
		}
		else {
			if(i-badChar >= 0){
				input[i - badChar] = input[i];
			}
	
		}
	}
	input.resize(count - badChar);
}

bool CInterface::inputMethod(const string& method, const vector<string> tokens) {
	map<string, MethodPtrWithArg>::iterator itWithArg = map_with_arg.find(method);
	if (itWithArg != map_with_arg.end()) {
		(this ->*(itWithArg->second))(tokens);
		return true;
	}

	map<string, MethodPtrNoArg>::iterator itWithoutArg = map_without_arg.find(method);
	if (itWithoutArg != map_without_arg.end()) {
		(this ->*(itWithoutArg->second))();
		return true;
	}

	return false;
}


