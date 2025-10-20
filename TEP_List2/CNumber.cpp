#include "CNumber.h"
#include <iostream>

CNumber::CNumber(){
	i_length = number_default_length;
	pi_number = new int[i_length];
}
CNumber::~CNumber() {
	delete[] pi_number;
}