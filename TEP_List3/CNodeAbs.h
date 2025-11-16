#pragma once
#include "CNode.h"
#include <string>
using namespace std;

class CNodeAbs :
    public CNode
{
public:
    CNodeAbs(const string& token);
    double evaluate() const override;
    string nodeToStr() const override;

private:
    double value;

};

