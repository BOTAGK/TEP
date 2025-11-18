#pragma once
#include "CNode.h"
class CNodeOp :
    public CNode
{
public:
    static CNodeOp* create(string& token);
    virtual int getExpectedChildrenCount() const;
    bool isChildFull() const;
    

};

class CNodeOpAdd :
    public CNodeOp
{
public:
    double evaluate() const override;
    string nodeToStr() const override;
    CNode* clone(CTree* newOwner) const override;
};

class CNodeOpSub :
    public CNodeOp
{
public:
    double evaluate() const override;
    string nodeToStr() const override;
    CNode* clone(CTree* newOwner) const override;
};

class CNodeOpMult :
    public CNodeOp
{
public:
    double evaluate() const override;
    string nodeToStr() const override;
    CNode* clone(CTree* newOwner) const override;
};

class CNodeOpDiv :
    public CNodeOp
{
public:
    double evaluate() const override;
    string nodeToStr() const override;
    CNode* clone(CTree* newOwner) const override;
};


class CNodeOpSin :
    public CNodeOp
{
public:
    double evaluate() const override;
    string nodeToStr() const override;
    int getExpectedChildrenCount() const override;
    CNode* clone(CTree* newOwner) const override;
    
};

class CNodeOpCos :
    public CNodeOp
{
public:
    double evaluate() const override;
    string nodeToStr() const override;
    int getExpectedChildrenCount() const override;
    CNode* clone(CTree* newOwner) const override;
};

