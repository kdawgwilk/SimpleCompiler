//
//  Node.cpp
//  SimpleCompiler
//
//  Created by Kaden Wilkinson on 2/22/17.
//  Copyright © 2017 Kaden Wilkinson. All rights reserved.
//

#include "Node.hpp"

// MARK: - Node

Node::~Node() {

}

// MARK: - Start

StartNode::StartNode(ProgramNode *programNode)
: mProgramNode(programNode) {
    MSG("StartNode - Init")
}

StartNode::~StartNode() {
    MSG("StartNode   - Delete Begin")
    delete mProgramNode;
    MSG("StartNode   - Delete End")
}

void StartNode::Interpret() {
    mProgramNode->Interpret();
}

// MARK: - Program

ProgramNode::ProgramNode(BlockNode *blockNode)
: mBlockNode(blockNode) {
    MSG("ProgramNode - Init")
}

ProgramNode::~ProgramNode() {
    MSG("ProgramNode - Delete Begin")
    delete mBlockNode;
    MSG("ProgramNode - Delete End")
}

void ProgramNode::Interpret() {
    mBlockNode->Interpret();
}

// MARK: - Block

BlockNode::BlockNode(SymbolTableClass *symbolTable, StatementGroupNode *statmentGroupNode)
: mSymbolTable(symbolTable)
, mStatementGroupNode(statmentGroupNode) {
    MSG("BlockNode - Init")
}

BlockNode::~BlockNode() {
    MSG("BlockNode - Delete Begin")
    delete mStatementGroupNode;
    MSG("BlockNode - Delete End")
}

void BlockNode::Interpret() {
    mSymbolTable->PushScope();
    mStatementGroupNode->Interpret();
    mSymbolTable->PopScope();
}

// MARK: - StatementGroup

StatementGroupNode::StatementGroupNode() {
    MSG("StatementGroupNode - Init")
}

StatementGroupNode::~StatementGroupNode() {
    MSG("StatementGroupNode - Delete Begin")
    for (StatementNode *statement : mStatementNodes) {
        delete statement;
    }
    MSG("StatementGroupNode - Delete End")
}

void StatementGroupNode::AddStatement(StatementNode *statementNode) {
    mStatementNodes.push_back(statementNode);
}

void StatementGroupNode::Interpret() {
    for (StatementNode *statement : mStatementNodes) {
        statement->Interpret();
    }
}

// MARK: - IfStatement

IfStatementNode::IfStatementNode(ExpressionNode *expressionNode, StatementNode *statementNode)
: mExpressionNode(expressionNode)
, mStatementNode(statementNode)
{
    MSG("IfStatementNode - Init")
}

IfStatementNode::~IfStatementNode() {
    MSG("IfStatementNode - Delete Begin")
    delete mExpressionNode;
    delete mStatementNode;
    MSG("IfStatementNode - Delete End")
}

void IfStatementNode::Interpret() {
    if (mExpressionNode->Evaluate()) {
        mStatementNode->Interpret();
    }
}

// MARK: - WhileStatement

WhileStatementNode::WhileStatementNode(ExpressionNode *expressionNode, StatementNode *statementNode)
: mExpressionNode(expressionNode)
, mStatementNode(statementNode)
{
    MSG("IfStatementNode - Init")
}

WhileStatementNode::~WhileStatementNode() {
    MSG("WhileStatementNode - Delete Begin")
    delete mExpressionNode;
    delete mStatementNode;
    MSG("WhileStatementNode - Delete End")
}

// TODO: Finish
void WhileStatementNode::Interpret() {
    while (mExpressionNode->Evaluate()) {
        mStatementNode->Interpret();
    }
}


// MARK: - DeclarationStatement


DeclarationStatementNode::DeclarationStatementNode(IdentifierNode *identifierNode)
: mIdentifierNode(identifierNode) {
    MSG("DeclarationStatementNode - Init")
}

DeclarationStatementNode::~DeclarationStatementNode() {
    MSG("DeclarationStatementNode - Delete Begin")
    delete mIdentifierNode;
    MSG("DeclarationStatementNode - Delete End")
}

void DeclarationStatementNode::Interpret() {
    mIdentifierNode->DeclareVariable();
}

// MARK: - AssignmentStatement

AssignmentStatementNode::AssignmentStatementNode(IdentifierNode *identifierNode, ExpressionNode *expressionNode)
: mIdentifierNode(identifierNode)
, mExpressionNode(expressionNode) {
    MSG("AssignmentStatementNode - Init")
}

AssignmentStatementNode::~AssignmentStatementNode() {
    MSG("AssignmentStatementNode - Delete Begin")
    delete mIdentifierNode;
    delete mExpressionNode;
    MSG("AssignmentStatementNode - Delete End")
}

void AssignmentStatementNode::Interpret() {
    int value = mExpressionNode->Evaluate();
    mIdentifierNode->SetValue(value);
}

// MARK: - PlusEqualStatement

PlusEqualStatementNode::PlusEqualStatementNode(IdentifierNode *identifierNode, ExpressionNode *expressionNode)
: mIdentifierNode(identifierNode)
, mExpressionNode(expressionNode) {
    MSG("PlusEqualStatementNode - Init")

}

PlusEqualStatementNode::~PlusEqualStatementNode() {
    MSG("PlusEqualStatementNode - Delete Begin")
    delete mIdentifierNode;
    delete mExpressionNode;
    MSG("PlusEqualStatementNode - Delete End")
}

void PlusEqualStatementNode::Interpret() {
    int value = mExpressionNode->Evaluate();
    int currentValue = mIdentifierNode->Evaluate();
    mIdentifierNode->SetValue(currentValue + value);
}

// MARK: - MinusEqualStatement

MinusEqualStatementNode::MinusEqualStatementNode(IdentifierNode *identifierNode, ExpressionNode *expressionNode)
: mIdentifierNode(identifierNode)
, mExpressionNode(expressionNode) {
    MSG("MinusEqualStatementNode - Init")

}

MinusEqualStatementNode::~MinusEqualStatementNode() {
    MSG("MinusEqualStatementNode - Delete Begin")
    delete mIdentifierNode;
    delete mExpressionNode;
    MSG("MinusEqualStatementNode - Delete End")
}

void MinusEqualStatementNode::Interpret() {
    int value = mExpressionNode->Evaluate();
    int currentValue = mIdentifierNode->Evaluate();
    mIdentifierNode->SetValue(currentValue - value);
}


// MARK: - TimesEqualStatement

TimesEqualStatementNode::TimesEqualStatementNode(IdentifierNode *identifierNode, ExpressionNode *expressionNode)
: mIdentifierNode(identifierNode)
, mExpressionNode(expressionNode) {
    MSG("TimesEqualStatementNode - Init")
    int value = mExpressionNode->Evaluate();
    mIdentifierNode->SetValue(value);
}

TimesEqualStatementNode::~TimesEqualStatementNode() {
    MSG("TimesEqualStatementNode - Delete Begin")
    delete mIdentifierNode;
    delete mExpressionNode;
    MSG("TimesEqualStatementNode - Delete End")
}

void TimesEqualStatementNode::Interpret() {
    int value = mExpressionNode->Evaluate();
    int currentValue = mIdentifierNode->Evaluate();
    mIdentifierNode->SetValue(currentValue * value);
}

// MARK: - DivideEqualStatement

DivideEqualStatementNode::DivideEqualStatementNode(IdentifierNode *identifierNode, ExpressionNode *expressionNode)
: mIdentifierNode(identifierNode)
, mExpressionNode(expressionNode) {
    MSG("DivideEqualStatementNode - Init")

}

DivideEqualStatementNode::~DivideEqualStatementNode() {
    MSG("DivideEqualStatementNode - Delete Begin")
    delete mIdentifierNode;
    delete mExpressionNode;
    MSG("DivideEqualStatementNode - Delete End")
}

void DivideEqualStatementNode::Interpret() {
    int value = mExpressionNode->Evaluate();
    int currentValue = mIdentifierNode->Evaluate();
    mIdentifierNode->SetValue(currentValue / value);
}


// MARK: - Expression

ExpressionNode::~ExpressionNode() {

}


// MARK: - CoutStatement

CoutStatementNode::CoutStatementNode(ExpressionNode *expressionNode)
: mExpressionNode(expressionNode) {
    MSG("CoutStatementNode - Init")
}

CoutStatementNode::~CoutStatementNode() {
    MSG("CoutStatementNode - Delete Begin")
    delete mExpressionNode;
    MSG("CoutStatementNode - Delete End")
}

void CoutStatementNode::Interpret() {
    int value = mExpressionNode->Evaluate();
    cout << value << endl;
}

// MARK: - Integer

IntegerNode::IntegerNode(int integer)
: mInteger(integer) {
    MSG("IntegerNode - Init")
}

int IntegerNode::Evaluate() {
    return mInteger;
}

// MARK: - Identifier

IdentifierNode::IdentifierNode(string label, SymbolTableClass *symbolTable)
: mLabel(label)
, mSymbolTable(symbolTable) {
    MSG("IdentifierNode - Init")
}

IdentifierNode::~IdentifierNode() {

}

void IdentifierNode::DeclareVariable() {
    mSymbolTable->AddEntry(mLabel);
}

void IdentifierNode::SetValue(int value) {
    mSymbolTable->SetValue(mLabel, value);
}

int IdentifierNode::GetIndex() {
    return mSymbolTable->GetIndex(mLabel);
}

int IdentifierNode::Evaluate() {
    return mSymbolTable->GetValue(mLabel);
}

// MARK: - BinaryOperator

BinaryOperatorNode::BinaryOperatorNode(ExpressionNode *leftSide, ExpressionNode *rightSide)
: mLeftSide(leftSide)
, mRightSide(rightSide) {
    MSG("BinaryOperatorNode - Init")
}

BinaryOperatorNode::~BinaryOperatorNode() {
    MSG("BinaryOperatorNode - Delete Begin")
    delete mLeftSide;
    delete mRightSide;
    MSG("BinaryOperatorNode - Delete End")
}

// MARK: - Or

OrNode::OrNode(ExpressionNode *leftSide, ExpressionNode *rightSide)
: BinaryOperatorNode(leftSide, rightSide) {

}

int OrNode::Evaluate() {
    return mLeftSide->Evaluate() || mRightSide->Evaluate();
}

// MARK: - And

AndNode::AndNode(ExpressionNode *leftSide, ExpressionNode *rightSide)
: BinaryOperatorNode(leftSide, rightSide) {

}

int AndNode::Evaluate() {
    return mLeftSide->Evaluate() && mRightSide->Evaluate();
}

// MARK: - Plus

PlusNode::PlusNode(ExpressionNode *leftSide, ExpressionNode *rightSide)
: BinaryOperatorNode(leftSide, rightSide) {
    MSG("PlusNode - Init")
}

int PlusNode::Evaluate() {
    return mLeftSide->Evaluate() + mRightSide->Evaluate();
}

// MARK: - Minus

MinusNode::MinusNode(ExpressionNode *leftSide, ExpressionNode *rightSide)
: BinaryOperatorNode(leftSide, rightSide) {
    MSG("PlusNode - Init")
}

int MinusNode::Evaluate() {
    return mLeftSide->Evaluate() + mRightSide->Evaluate();
}

// MARK: - Times

TimesNode::TimesNode(ExpressionNode *leftSide, ExpressionNode *rightSide)
: BinaryOperatorNode(leftSide, rightSide) {
    MSG("PlusNode - Init")
}

int TimesNode::Evaluate() {
    return mLeftSide->Evaluate() + mRightSide->Evaluate();
}

// MARK: - Divide

DivideNode::DivideNode(ExpressionNode *leftSide, ExpressionNode *rightSide)
: BinaryOperatorNode(leftSide, rightSide) {
    MSG("PlusNode - Init")
}

int DivideNode::Evaluate() {
    return mLeftSide->Evaluate() + mRightSide->Evaluate();
}

// MARK: - Less

LessNode::LessNode(ExpressionNode *leftSide, ExpressionNode *rightSide)
: BinaryOperatorNode(leftSide, rightSide) {
    MSG("LessNode - Init")
}

int LessNode::Evaluate() {
    return mLeftSide->Evaluate() + mRightSide->Evaluate();
}

// MARK: - LessEqual

LessEqualNode::LessEqualNode(ExpressionNode *leftSide, ExpressionNode *rightSide)
: BinaryOperatorNode(leftSide, rightSide) {
    MSG("LessEqualNode - Init")
}

int LessEqualNode::Evaluate() {
    return mLeftSide->Evaluate() + mRightSide->Evaluate();
}

// MARK: - Greater

GreaterNode::GreaterNode(ExpressionNode *leftSide, ExpressionNode *rightSide)
: BinaryOperatorNode(leftSide, rightSide) {
    MSG("GreaterNode - Init")
}

int GreaterNode::Evaluate() {
    return mLeftSide->Evaluate() + mRightSide->Evaluate();
}

// MARK: - GreaterEqual

GreaterEqualNode::GreaterEqualNode(ExpressionNode *leftSide, ExpressionNode *rightSide)
: BinaryOperatorNode(leftSide, rightSide) {
    MSG("GreaterEqualNode - Init")
}

int GreaterEqualNode::Evaluate() {
    return mLeftSide->Evaluate() + mRightSide->Evaluate();
}

// MARK: - Equal

EqualNode::EqualNode(ExpressionNode *leftSide, ExpressionNode *rightSide)
: BinaryOperatorNode(leftSide, rightSide) {
    MSG("EqualNode - Init")
}

int EqualNode::Evaluate() {
    return mLeftSide->Evaluate() + mRightSide->Evaluate();
}

// MARK: - NotEqual

NotEqualNode::NotEqualNode(ExpressionNode *leftSide, ExpressionNode *rightSide)
: BinaryOperatorNode(leftSide, rightSide) {
    MSG("NotEqualNode - Init")
}

int NotEqualNode::Evaluate() {
    return mLeftSide->Evaluate() + mRightSide->Evaluate();
}

// MARK: - UnaryOperator

UnaryOperatorNode::UnaryOperatorNode(ExpressionNode *expression)
: mExpression(expression) {
    MSG("UnaryOperatorNode - Init")
}

UnaryOperatorNode::~UnaryOperatorNode() {
    MSG("UnaryOperatorNode - Delete Begin")
    delete mExpression;
    MSG("UnaryOperatorNode - Delete End")
}

// MARK: - Not

NotNode::NotNode(ExpressionNode *expression)
: UnaryOperatorNode(expression){
    MSG("NotNode - Init")
}

int NotNode::Evaluate() {
    return !mExpression->Evaluate();
}

// MARK: - Not

NegativeNode::NegativeNode(ExpressionNode *expression)
: UnaryOperatorNode(expression) {
    MSG("NegativeNode - Init")
}

int NegativeNode::Evaluate() {
    return -mExpression->Evaluate();
}






