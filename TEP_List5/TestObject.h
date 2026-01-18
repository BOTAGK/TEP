#pragma once
#include <iostream>
#include <string>
using namespace std;

class TestObject
{
public:
	TestObject(int newId, string newName);
	~TestObject();
	void sayHello();
	void setName(string n);
	
private:
	int id;
	string name;

};

