#pragma once
#include <string>
using namespace std;

class CError
{
public:
	CError();
	CError(int tokenIndex,bool lackArg, const string& message);
	bool isSuccess() const;
	bool lackArguments() const;
	string getMessage() const;
private:

	bool is_success;
	bool lack_of_arguments;
	int tokenIndex;
	string message;

};

