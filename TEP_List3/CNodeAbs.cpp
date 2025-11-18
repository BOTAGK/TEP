#include "CNodeAbs.h"
#include <cstdlib>
#include <sstream>
using namespace std;

CNodeAbs::CNodeAbs(const string& token) {
	char* pEnd;
	value = strtod(token.c_str(), &pEnd);

	if (*pEnd != '\0') {
		value = 0.0;
	}
}

CNodeAbs::CNodeAbs(double val) {
	value = val;
}

string CNodeAbs::nodeToStr() const {
	stringstream ss;
	ss << value;
	return ss.str();
}

double CNodeAbs::evaluate() const {
	return value;
}

CNode* CNodeAbs::clone(CTree* newOwner) const {
	return new CNodeAbs(value);
}