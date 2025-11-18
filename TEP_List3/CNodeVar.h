#pragma once
#include "CNode.h"
#include "CTree.h"
class CNodeVar : public CNode
{
public:
    virtual ~CNodeVar();
    void setValue(const string& val);

    static CNodeVar* create(const string& token, CTree* tree);
    double evaluate() const override;
    string nodeToStr() const override;
    CNode* clone(CTree* newOwner) const override;

private:
    CNodeVar(CTree* tree);

    CTree* pc_Tree;
    double value;
    
};

