#include "CError.h"
#include <string>

CError:: CError() {
	tokenIndex = -1;
	lack_of_arguments = false;
	is_success = true;
	message = "";
}
CError::CError(int token,bool lackArg, const string& msg)
{
	tokenIndex = token;
	lack_of_arguments = lackArg;
	message = msg;
	is_success = false;
}

bool CError::lackArguments() const {
	return lack_of_arguments;
}

bool CError::isSuccess() const
{
	return is_success;
}

string CError::getMessage() const
{
	if (is_success) {
		return "Operation completed succesfully";
	}

	return "Error at token" + to_string(tokenIndex) + ": " + message;
}
