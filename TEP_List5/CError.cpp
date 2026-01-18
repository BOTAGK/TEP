#include "CError.h"
#include <string>

CError:: CError() {
	tokenIndex = -1;
	message = "";
}
CError::CError(int token, const string& msg)
{
	tokenIndex = token;
	message = msg;
}


string CError::getMessage() const
{
	return "Error at token" + to_string(tokenIndex) + ": " + message;
}
