#pragma once
#include <string>
using namespace std;

class CError
{
public:
	CError();
	CError(int tokenIndex, const string& message);
	string getMessage() const;
private:
	int tokenIndex;
	string message;
};

