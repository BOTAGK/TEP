#include "CInterface.h"
#include <sstream>
#include <iostream>

CInterface::CInterface() {
	quitFlag = false;

	map_without_arg["print"] = &CInterface::print;
	map_without_arg["vars"] = &CInterface::vars;
	map_without_arg["quit"] = &CInterface::quit;

	map_with_arg["enter"] = &CInterface::enter;
	map_with_arg["comp"] = &CInterface::comp;
	map_with_arg["join"] = &CInterface:: join;
}

CInterface::~CInterface() {

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

		//wykonuje metode chyba ze bledna 
		if (!inputMethod(command, tokens)) {
			cout << "B³êdna metoda: " << command << "\n";
		}
	}

	cout << "Koniec programu\n " << endl;
}

void CInterface::enter(const vector<string> tokens) {
	

	CError result = tree.create(tokens);
	
	cout << result.getMessage() << "\n" << endl;
	
	if (result.lackArguments()) {
		cout << "Tree after being fixed: " << "\n" << endl;
	}
	cout << tree.treeToString() << endl;
}

void CInterface::comp(const vector<string> tokens) {
	CError result = tree.comp(tokens);

	cout << result.getMessage() << "\n" << endl;

	if (result.isSuccess()) {
		cout << "Wynik: " + tree.evaluate() << "\n" << endl;
	}

}

void CInterface::join(const vector<string> tokens) {

}

void CInterface::print() {
	cout << tree.treeToString() << "\n" << endl;
}

void CInterface::vars() {
	cout << tree.printVariables() << "\n" << endl;
}

void CInterface::quit() {
	quitFlag = true;
	cout << "Koniec programu" << endl;
}

bool CInterface::undesiredToken(const char& input) {
	bool is_allowed = (input >= 'a' && input <= 'z') ||
				      (input >= 'A' && input <= 'Z') ||
					  (input >= '0' && input <= '9') ||
					   input == '+' || input == '-' || input == '*' || input == '/' ||
					   input == ' ' || input == '.' || input == ',';
	return !is_allowed;
}

void CInterface::fixInput(string& input) {
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
