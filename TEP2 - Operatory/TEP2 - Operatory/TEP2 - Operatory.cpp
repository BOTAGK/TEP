#include <iostream>
#include "CNumber.h"
using namespace std;
int main()
{
	CNumber cv0, cv1, cs;
	cv0 = 8;
	cv1 = 2;
	cs = cv0 / cv1;
	cout << cs.sToString() << endl;
	/*cs = cv1 - cv0;
	cout << cs.sToString() << endl;
	cs = cv0 - cv1;
	cout << cs.sToString() << endl;*/
}
