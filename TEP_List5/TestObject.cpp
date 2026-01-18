#include "TestObject.h"
TestObject::TestObject(int newId, string newName):
id(newId), name(newName) {
	cout << " [+] konstruktor TestObject: Id= " << id << "(" << name << ")" << endl;
}

TestObject::~TestObject() {
	cout << " [-] Destruktor TestObject: ID=" << id << "(" << name << ")" << endl;
}

void TestObject::sayHello() {
	cout << " Hej to: " << name << endl;
}

void TestObject::setName(string n) {
	name = n;
}