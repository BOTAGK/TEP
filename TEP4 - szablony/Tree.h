#pragma once
#include <string>
using namespace std;

const char space = ' ';
const char first_digit = 48;
const char last_digit = 57;

template <typename T> class Tree
{
	enum Type { empty = 0, single_operator, double_operator, data, variable };
	class Node {
	public:
		string contents;
		bool isFull;
		Type type;
		Node* left_child;
		Node* right_child;
		Node* parent;
		Node();
		Node(Node* new_parent);
		~Node();
		bool addContent(string input);
	};
public:
	Tree();
	~Tree();

	Node* getRoot();
	void setRoot(Node* root);

	bool enter(string formula);
	void stringToTree(string* input, int size, int& check_correct);
	string treeToString() const;
	void treeToStringParser(Node* current, string& result) const;
	void fillWithOnes();
	Node* findNextToInput(Node* current) const;
	string* analize(string input, int& inputsize);
	bool isUndesired(char input);
	void vars();
	string* getVariableNames(int& size);
	bool contains(string* input, int size, string name);
	void checkForVariables(Node* current, string& result);
	int getVariableIndex(string*& input, int size, string name);
	T comp(string args);
	T compRec(Node* current, string*& args, string*& vars, int size);
	T convertData(string input);
	string stringSubstract(string input1, string input2);
	string stringMultiply(string input1, string input2);
	string stringDivide(string input1, string input2);
	void print();
	void printDown(Node* current) const;
	bool join(string formula);
	Node* findReplacable();
	Node* findReplacableRec(Node* current);
	string* trim(string*& original, int& size);

	string sValToString();
	void sValToStringRec(Node* current, string& result);

	void operator=(const Tree otherTree);
	Tree operator+(const Tree otherTree) const;

private:
	Node* root;
};

template <typename T>
Tree<T>::Tree()
{
	root = new Node();
}

template <typename T>
Tree<T>::~Tree()
{
	delete root;
}
template <typename T>
typename Tree<T>::Node* Tree<T>::getRoot()
{
	return root;
}
template <typename T>
void Tree<T>::setRoot(Node* new_root)
{
	delete root;
	root = new_root;
}
template <typename T>
bool Tree<T>::enter(string formula)
{
	int input_size = 0;
	string* input = analize(formula, input_size);
	int check_correct = 0;
	stringToTree(input, input_size, check_correct);
	if (check_correct == 0) {
		return true;
	}
	else if (check_correct > 0) {
		cout << "The formula contained too many arguments. Ignoring the following part of the formula:" << endl;
		for (int i = check_correct; i < input_size; i++) {
			cout << input[i] << " ";
		}
		cout << endl;
		cout << "the corrected formula is: ";
		this->print();
		cout << endl;
		return false;
	}
	else if (check_correct == -1) {
		cout << "The formula lacked arguments. Filling the formula with '1'..." << endl;
		fillWithOnes();
		cout << "the corrected formula is: ";
		this->print();
		cout << endl;
		return false;
	}
	else {
		return false;
	}
}
template <typename T>
void Tree<T>::stringToTree(string* input, int size, int& i)
{
	Node* current = root;
	for (i; i < size; i++) {
		if (current == nullptr) {
			return;
		}
		current->addContent(input[i]);
		current = findNextToInput(current);
	}
	if (current == nullptr) {
		i = 0;
	}
	else if (current->type == empty) {
		i = -1;
	}
}
template <typename T>
string Tree<T>::treeToString() const
{
	string result = " ";
	treeToStringParser(root, result);
	return result;
}
template <typename T>
void Tree<T>::treeToStringParser(Node* current, string& result) const
{
	result = result + current->contents + " ";
	if (current->left_child != nullptr) {
		printDown(current->left_child);
	}if (current->right_child != nullptr) {
		printDown(current->right_child);
	}
}
template <typename T>
void Tree<T>::fillWithOnes()
{
	Node* current = findNextToInput(root);
	while (current != nullptr && current->type == empty) {
		current->addContent("1");
		current = findNextToInput(current);
	}
}
template <typename T>
typename Tree<T>::Node* Tree<T>::findNextToInput(Node* current) const
{
	if (current->type == empty) return current;
	else if (current->left_child != nullptr && current->left_child->isFull == false) {
		return findNextToInput(current->left_child);
	}
	else if (current->right_child != nullptr && current->right_child->isFull == false) {
		return findNextToInput(current->right_child);
	}
	else {
		current->isFull = true;
		if (current->parent == nullptr) return nullptr;
		else return findNextToInput(current->parent);
	}
}
template <typename T>
string* Tree<T>::analize(string input, int& size)
{
	int input_size = input.size();
	size = 0;
	if (input_size == 0) {
		return nullptr;
	}
	if (input[0] != space) {
		size++;
	}
	for (int i = 1; i < input_size; i++) {
		if (input[i] != space && input[i - 1] == space) {
			size++;
		}
	}
	string* result = new string[size];
	int temp_iterator = 0;
	string temp = "";
	for (int i = 0; i < input_size; i++) {
		if (input[i] != space) {
			if (isUndesired(input[i])) {
				cout << "skipping the following sign: " << input[i] << endl;
			}
			else {
				temp += input[i];
			}
		}
		else if (temp != "") {
			result[temp_iterator] = temp;
			temp = "";
			temp_iterator++;
		}
	}
	if (temp != "") {
		result[temp_iterator] = temp;
	}
	return result;
}
template <>
string* Tree<float>::analize(string input, int& size)
{
	int input_size = input.size();
	size = 0;
	if (input_size == 0) {
		return nullptr;
	}
	if (input[0] != space) {
		size++;
	}
	for (int i = 1; i < input_size; i++) {
		if (input[i] != space && input[i - 1] == space) {
			size++;
		}
	}
	string* result = new string[size];
	int temp_iterator = 0;
	int dot_counter = 0;
	string temp = "";
	for (int i = 0; i < input_size; i++) {
		if (input[i] != space) {
			if (isUndesired(input[i])) {
				cout << "skipping the following sign: " << input[i] << endl;
			}
			else {
				if (input[i] == '.') {
					if (dot_counter < 1) {
						temp += input[i];
					}
					dot_counter++;
				}
				else {
					temp += input[i];
				}
				
			}
		}
		else if (temp != "") {
			result[temp_iterator] = temp;
			temp = "";
			dot_counter = 0;
			temp_iterator++;
		}
	}
	if (temp != "") {
		result[temp_iterator] = temp;
	}
	return result;
}

template <>
string* Tree<double>::analize(string input, int& size)
{
	int input_size = input.size();
	size = 0;
	if (input_size == 0) {
		return nullptr;
	}
	if (input[0] != space) {
		size++;
	}
	for (int i = 1; i < input_size; i++) {
		if (input[i] != space && input[i - 1] == space) {
			size++;
		}
	}
	string* result = new string[size];
	int temp_iterator = 0;
	int dot_counter = 0;
	string temp = "";
	for (int i = 0; i < input_size; i++) {
		if (input[i] != space) {
			if (isUndesired(input[i])) {
				cout << "skipping the following sign: " << input[i] << endl;
			}
			else {
				if (input[i] == '.') {
					if (dot_counter < 1) {
						temp += input[i];
					}
					dot_counter++;
				}
				else {
					temp += input[i];
				}

			}
		}
		else if (temp != "") {
			result[temp_iterator] = temp;
			temp = "";
			dot_counter = 0;
			temp_iterator++;
		}
	}
	if (temp != "") {
		result[temp_iterator] = temp;
	}
	return result;
}

template <typename T>
bool isUndesired(char input) {
	return (input <= ')' || (input >= ':' && input <= '@') || (input >= ']' && input <= '`') || input >= '{' || input == ',' || input =='.');
}

template <>
bool Tree<float>::isUndesired(char input) {
	return (input <= ')' || (input >= ':' && input <= '@') || (input >= ']' && input <= '`') || input >= '{' || input == ',');
}

template <>
bool Tree<double>::isUndesired(char input) {
	return (input <= ')' || (input >= ':' && input <= '@') || (input >= ']' && input <= '`') || input >= '{' || input == ',');
}

template <typename T>
void Tree<T>::vars()
{
	int size = 0;
	string* variables = getVariableNames(size);
	for (int i = 0; i < size; i++) {
		cout << variables[i] << " ";
	}
	cout << endl;
}
template <typename T>
string* Tree<T>::getVariableNames(int& size)
{
	string raw_variables = "";
	checkForVariables(root, raw_variables);
	int input_size = raw_variables.size();
	int temp_size = 0;
	if (input_size == 0) {
		return nullptr;
	}
	if (raw_variables[0] != space) {
		temp_size++;
	}
	for (int i = 1; i < input_size; i++) {
		if (raw_variables[i] != space && raw_variables[i - 1] == space) {
			temp_size++;
		}
	}
	string* result = new string[temp_size];
	for (int i = 0; i < temp_size; i++) {
		result[i] = "0";
	}
	int temp_iterator = 0;
	string temp = "";
	for (int i = 0; i < input_size; i++) {
		if (raw_variables[i] != space) {
			temp += raw_variables[i];
		}
		else if (temp != "" && !contains(result, temp_size, temp)) {
			result[temp_iterator] = temp;
			temp = "";
			temp_iterator++;
		}
	}
	if (temp != "") {
		result[temp_iterator] = temp;
	}
	result = trim(result, temp_size);
	size = temp_size;
	return result;
}
template <typename T>
bool Tree<T>::contains(string* input, int size, string name)
{
	for (int i = 0; i < size; i++) {
		if (input[i] == name) {
			return true;
		}
	}
	return false;
}
template <typename T>
void Tree<T>::checkForVariables(Node* current, string& result)
{
	if (current->type == variable) {
		result = result + " " + current->contents;
	}
	else if (current->type == double_operator || current->type == single_operator) {
		checkForVariables(current->left_child, result);
		if (current->type == double_operator) {
			checkForVariables(current->right_child, result);
		}
	}
}
template <typename T>
int Tree<T>::getVariableIndex(string*& input, int size, string name)
{
	int i = 0;
	for (i; i < size; i++) {
		if (input[i] == name) {
			return i;
		}
	}
	return -1;
}
template <typename T>
T Tree<T>::comp(string args)
{
	int variables_count = 0;
	string* variables = getVariableNames(variables_count);
	int args_count = 0;
	string* args_list = analize(args, args_count);
	if (args_count != variables_count) {
		cout << "Inccorent number of arguments" << endl;
		return 0;
	}
	compRec(root, args_list, variables, args_count);
}
template <typename T>
T Tree<T>::compRec(Node* current, string*& args, string*& vars, int size)
{
	if (current == nullptr) {
		return 0;
	}
	if (current->type == data) {
		return convertData(current->contents);
	}
	else if (current->type == single_operator) {
		if (current->contents == "sin") {
			return sin(compRec(current->left_child, args, vars, size));
		}
		else {
			return cos(compRec(current->left_child, args, vars, size));
		}
	}
	else if (current->type == double_operator) {
		if (current->contents == "+") {
			return compRec(current->left_child, args, vars, size) + compRec(current->right_child, args, vars, size);
		}
		else if (current->contents == "-") {
			return compRec(current->left_child, args, vars, size) - compRec(current->right_child, args, vars, size);
		}
		else if (current->contents == "*") {
			return compRec(current->left_child, args, vars, size) * compRec(current->right_child, args, vars, size);
		}
		else if (current->contents == "/") {
			return compRec(current->left_child, args, vars, size) / compRec(current->right_child, args, vars, size);
		}
	}
	else if (current->type == variable) {
		return convertData(args[getVariableIndex(vars, size, current->contents)]);
	}
}

template <>
string Tree<string>::compRec(Node* current, string*& args, string*& vars, int size)
{
	if (current == nullptr) {
		return 0;
	}
	if (current->type == data) {
		return current->contents;
	}
	else if (current->type == single_operator) {
		if (current->contents == "sin") {
			return "";
		}
		else {
			return "";
		}
	}
	else if (current->type == double_operator) {
		if (current->contents == "+") {
			return compRec(current->left_child, args, vars, size) + compRec(current->right_child, args, vars, size);
		}
		else if (current->contents == "-") {
			return stringSubstract(compRec(current->left_child, args, vars, size), compRec(current->right_child, args, vars, size));
		}
		else if (current->contents == "*") {
			return stringMultiply(compRec(current->left_child, args, vars, size), compRec(current->right_child, args, vars, size));
		}
		else if (current->contents == "/") {
			return stringDivide(compRec(current->left_child, args, vars, size), compRec(current->right_child, args, vars, size));
		}
	}
	else if (current->type == variable) {
		return args[getVariableIndex(vars, size, current->contents)];
	}
}
template <typename T>
T Tree<T>::convertData(string input) {
	return stoi(input);
}
template<>
string Tree<string>::stringSubstract(string input1, string input2)
{
	if (input2.size() > input1.size()) {
		return "";
	}
	int last_known = -1;
	for (int i = 0; i < input1.size() - input2.size(); i++) {
		bool is_the_same = true;
		for (int j = 0; j < input2.size(); i++) {
			if (input1[i + j] != input2[i + j]) is_the_same = false;
		}
		if (is_the_same) {
			last_known = i;
		}
	}
	string result = input1;
	return (last_known < 0) ? input1: result.replace(last_known, input2.size(),"");
}
template<>
string Tree<string>::stringMultiply(string input1, string input2)
{
	string result = input1;
	int i = 0;
	while (i <= result.size()) {
		if (result[i] == input2[i]) {
			result.replace(i, 1, input2);
			i += input2.size();
		}
		i++;
	}
	return result;
}
template<>
string Tree<string>::stringDivide(string input1, string input2)
{
	if (input2.size() > input1.size()) {
		return "";
	}
	string result;
	int i = 0;
	while (i <= result.size()) {
		bool is_the_same = true;
		for (int j = 0; j < input2.size(); i++) {
			if (result[i + j] != input2[i + j]) is_the_same = false;
		}
		if (is_the_same) {
			result.replace(i, input2.size(),"");
			i -= input2.size();
		}
		i++;
	}

	return result;
}
template <>
int Tree<int>::convertData(string input) {
	return stoi(input);
}
template <>
double Tree<double>::convertData(string input) {
	return stod(input);
}
template <>
float Tree<float>::convertData(string input) {
	return stof(input);
}


template <typename T>
void Tree<T>::print()
{
	printDown(root);
}
template <typename T>
void Tree<T>::printDown(Node* current) const
{
	cout << current->contents << " ";
	if (current->left_child != nullptr) {
		printDown(current->left_child);
	}if (current->right_child != nullptr) {
		printDown(current->right_child);
	}
}
template <typename T>
bool Tree<T>::join(string formula)
{
	Node* replacable_parent = findReplacable()->parent;
	Tree* otherTree = new Tree();
	otherTree->enter(formula);
	if (replacable_parent == nullptr) {
		root = otherTree->getRoot();
		otherTree->setRoot(nullptr);
		delete otherTree;
	}
	else {
		if (replacable_parent->left_child->type == variable || replacable_parent->left_child->type == data) {
			delete replacable_parent->left_child;
			replacable_parent->left_child = otherTree->getRoot();
			otherTree->setRoot(nullptr);
			delete otherTree;
		}
		else {
			delete replacable_parent->right_child;
			replacable_parent->right_child = otherTree->getRoot();
			otherTree->setRoot(nullptr);
			delete otherTree;
		}
	}
	return true;
}
template <typename T>
typename Tree<T>::Node* Tree<T>::findReplacable()
{
	return findReplacableRec(root);
}
template <typename T>
typename Tree<T>::Node* Tree<T>::findReplacableRec(Node* current)
{
	if (current != nullptr && (current->type == variable || current->type == data)) {
		return current;
	}
	else if (current->type == double_operator || current->type == single_operator) {
		findReplacableRec(current->left_child);
		if (current->type == double_operator) {
			findReplacableRec(current->right_child);
		}
	}
	return nullptr;
}
template <typename T>
string* Tree<T>::trim(string*& original, int& size)
{
	int new_size = 0;
	for (int i = 0; i < size; i++) {
		if (original[i] != "0") {
			new_size++;
		}
	}
	string* result = new string[new_size];
	for (int i = 0; i < new_size; i++) {
		result[i] = original[i];
	}
	size = new_size;
	return result;
}


template<typename T>
string Tree<T>::sValToString()
{
	string result = "";
	sValToString(root, result);
	return result;
}
template<typename T>
void Tree<T>::sValToStringRec(Node* current, string& result)
{
	if (current->type == data) {
		result = result + current->contents + " ";
	}
	else if(current->type == double_operator || current->type == single_operator){
		sValToString(current->left_child, result);
		if (current->type == double_operator) {
			sValToString(current->right_child, result);
		}
	}
}


template <typename T>
void Tree<T>::operator=(const Tree otherTree)
{
	delete this;
	this->enter(otherTree.treeToString());
}
template <typename T>
Tree<T> Tree<T>::operator+(const Tree otherTree) const
{
	Tree result = Tree();
	result.enter(this->treeToString());
	result.join(otherTree.treeToString());
	return result;
}
template <typename T>
Tree<T>::Node::Node()
{
	isFull = false;
	type = Tree::Type::empty;
	contents = "";
	left_child = nullptr;
	right_child = nullptr;
	parent = nullptr;
}
template <typename T>
Tree<T>::Node::Node(Node* new_parent)
{
	isFull = false;
	type = Tree::Type::empty;
	contents = "";
	left_child = nullptr;
	right_child = nullptr;
	parent = new_parent;
}
template <typename T>
Tree<T>::Node::~Node()
{
	if (type = double_operator) {
		delete left_child;
		delete right_child;
	}
	else if (type = single_operator) {
		delete left_child;
	}
}
template <typename T>
bool Tree<T>::Node::addContent(string input)
{
	contents = input;
	bool isVariable = false;
	int dot_count = 0;
	int size = input.size();
	for (int i = 0; i < size; i++) {
		if (input[i] < first_digit || input[i] > last_digit || (dot_count > 0 && input[i] == '.')) {
			if (input[i] == '.') {
				dot_count++;
			}
			isVariable = true;
			if ((i == 0) && (input[0] == '-') && (size > 1)) {
				isVariable = false;
			}
		}
	}
	if (contents == "+" || contents == "-" || contents == "*" || contents == "/") {
		type = double_operator;
		left_child = new Node(this);
		right_child = new Node(this);
	}
	else if (contents == "sin" || contents == "cos") {
		type = single_operator;
		left_child = new Node(this);
	}
	else if (isVariable) {
		type = variable;
		isFull = true;
	}
	else {
		type = data;
		isFull = true;
	}

	return true;
}

template <>
bool Tree<string>::Node::addContent(string input)
{
	contents = input;
	bool isVariable = false;
	int size = input.size();
	for (int i = 0; i < size; i++) {
		if (!(input[i] < first_digit || input[i] > last_digit)) {
			isVariable = true;
		}
	}
	if (contents == "+" || contents == "-" || contents == "*" || contents == "/") {
		type = double_operator;
		left_child = new Node(this);
		right_child = new Node(this);
	}
	else if (contents == "sin" || contents == "cos") {
		type = single_operator;
		left_child = new Node(this);
	}
	else if (isVariable) {
		type = variable;
		isFull = true;
	}
	else {
		type = data;
		isFull = true;
	}

	return true;
}

template <>
bool Tree<int>::Node::addContent(string input)
{
	contents = input;
	bool isVariable = false;
	int size = input.size();
	for (int i = 0; i < size; i++) {
		if (input[i] < first_digit || input[i] > last_digit) {
			isVariable = true;
		}
		if (i == 0 && input[0] == '=' && size > 1) {
			isVariable = false;
		}
	}
	if (contents == "+" || contents == "-" || contents == "*" || contents == "/") {
		type = double_operator;
		left_child = new Node(this);
		right_child = new Node(this);
	}
	else if (contents == "sin" || contents == "cos") {
		type = single_operator;
		left_child = new Node(this);
	}
	else if (isVariable) {
		type = variable;
		isFull = true;
	}
	else {
		type = data;
		isFull = true;
	}

	return true;
}

