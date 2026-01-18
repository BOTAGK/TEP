#pragma once
#include "CNode.h"
#include <string>
using namespace std;

class CNodeAbs :
    public CNode
{
public:
    CNodeAbs(const string& token);
    CNodeAbs(double val);
    double evaluate() const override;
    string nodeToStr() const override;
    CNode* clone(CTree* newOwner) const override;

private:
    double value;

};

