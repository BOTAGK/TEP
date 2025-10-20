#ifndef CNumber_H
#define CNUmber_H

class CNumber
{
public:
	static const int number_default_length = 10;

	CNumber();
	~CNumber();
	void vSet(int iNewVal);
	void vSet(CNumber& pcNewVal);
	CNumber vAdd(CNumber& pcNewVal);
	CNumber vSub(CNumber& pcNewVal);
	CNumber vMul(CNumber& pcNewVal);
	CNumber vDiv(CNumber& pcNewVal);
	CNumber vAdd(int iNewVal);
	CNumber vSub(int iNewVal);
	CNumber vMul(int iNewVal);
	CNumber vDiv(int iNewVal);
private:
	int* pi_number;
	int i_length;
};

#endif

