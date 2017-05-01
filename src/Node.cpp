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

void StartNode::Code(InstructionsClass &instructions) {
    mProgramNode->Code(instructions);
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

void ProgramNode::Code(InstructionsClass &instructions) {
    mBlockNode->Code(instructions);
}

// MARK: - Block

BlockNode::BlockNode(SymbolTableClass *symbolTable, StatementGroupNode *statmentGroupNode)
: mStatementGroupNode(statmentGroupNode)
, mSymbolTable(symbolTable) {
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

void BlockNode::Code(InstructionsClass &instructions) {
    mSymbolTable->PushScope();
    mStatementGroupNode->Code(instructions);
    mSymbolTable->PopScope();
}

// MARK: - StatementGroup

StatementGroupNode::StatementGroupNode() {
    MSG("StatementGroupNode - Init")
}

StatementGroupNode::~StatementGroupNode() {
    MSG("StatementGroupNode - Delete Begin")
    for (StatementNode *statement : mStatementNodes) {
        if (statement != NULL) {
            delete statement;
        }
    }
    MSG("StatementGroupNode - Delete End")
}

void StatementGroupNode::AddStatement(StatementNode *statementNode) {
    mStatementNodes.push_back(statementNode);
}

void StatementGroupNode::Interpret() {
    for (StatementNode *statement : mStatementNodes) {
        if (statement != NULL) {
            statement->Interpret();
        }
    }
}

void StatementGroupNode::Code(InstructionsClass &instructions) {
    for (StatementNode *statement : mStatementNodes) {
        if (statement != NULL) {
            statement->Code(instructions);
        }

    }
}

// MARK: - IfStatement

IfStatementNode::IfStatementNode(ExpressionNode *expressionNode, StatementNode *ifStatementNode, StatementNode *elseStatementNode)
: mExpressionNode(expressionNode)
, mIfStatementNode(ifStatementNode)
, mElseStatementNode(elseStatementNode)
{
    MSG("IfStatementNode - Init")
}

IfStatementNode::~IfStatementNode() {
    MSG("IfStatementNode - Delete Begin")
    delete mExpressionNode;
    delete mIfStatementNode;
    if (mElseStatementNode != NULL) {
        delete mElseStatementNode;
    }
    MSG("IfStatementNode - Delete End")
}

void IfStatementNode::Interpret() {
    if (mExpressionNode->Evaluate()) {
        mIfStatementNode->Interpret();
    } else if (mElseStatementNode != NULL) {
        mElseStatementNode->Interpret();
    }
}

void IfStatementNode::Code(InstructionsClass &instructions) {
    mExpressionNode->CodeEvaluate(instructions);
    unsigned char *jumpAddress      = instructions.SkipIfZeroStack(); // pops a non-zero or a zero from the stack
    //get address of where the newxt instruction should go
    unsigned char *address1         = instructions.GetAddress();
    mIfStatementNode->Code(instructions);
    unsigned char *address2         = instructions.GetAddress();
    unsigned char sizeOfCode        = address2 - address1;
    instructions.SetOffset(jumpAddress, sizeOfCode);
    if (mElseStatementNode != NULL && mExpressionNode->Evaluate() == 0) {
        mElseStatementNode->Code(instructions);
        unsigned char *address4     = instructions.GetAddress();
        unsigned char sizeOfCode2   = address4 - address2;
        instructions.SetOffset(jumpAddress, sizeOfCode2);
    }
}

// MARK: - WhileStatement

WhileStatementNode::WhileStatementNode(ExpressionNode *expressionNode, StatementNode *statementNode)
: mExpressionNode(expressionNode)
, mStatementNode(statementNode)
{
    MSG("WhileStatementNode - Init")
}

WhileStatementNode::~WhileStatementNode() {
    MSG("WhileStatementNode - Delete Begin")
    delete mExpressionNode;
    delete mStatementNode;
    MSG("WhileStatementNode - Delete End")
}

void WhileStatementNode::Interpret() {
    while (mExpressionNode->Evaluate()) {
        mStatementNode->Interpret();
    }
}

void WhileStatementNode::Code(InstructionsClass &instructions) {
    unsigned char *address0         = instructions.GetAddress();
    mExpressionNode->CodeEvaluate(instructions);
    unsigned char *jumpAddress      = instructions.SkipIfZeroStack(); // pops a non-zero or a zero from the stack
    unsigned char *address1         = instructions.GetAddress();
    mStatementNode->Code(instructions);
    unsigned char *jumpAddress2     = instructions.Jump();
    unsigned char *address2         = instructions.GetAddress();
    unsigned char sizeOfCode        = address2 - address1;
    instructions.SetOffset(jumpAddress, sizeOfCode);
    instructions.SetOffset(jumpAddress2, (address0 - address2));
}

// MARK: - DoWhileStatement

DoWhileStatementNode::DoWhileStatementNode(ExpressionNode *expressionNode, StatementNode *statementNode)
: mExpressionNode(expressionNode)
, mStatementNode(statementNode)
{
    MSG("DoWhileStatementNode - Init")
}

DoWhileStatementNode::~DoWhileStatementNode() {
    MSG("DoWhileStatementNode - Delete Begin")
    delete mExpressionNode;
    delete mStatementNode;
    MSG("DoWhileStatementNode - Delete End")
}

void DoWhileStatementNode::Interpret() {
    do {
        mStatementNode->Interpret();
    } while (mExpressionNode->Evaluate());
}

void DoWhileStatementNode::Code(InstructionsClass &instructions) {
    mStatementNode->Code(instructions);
    unsigned char *address1         = instructions.GetAddress();
    mExpressionNode->CodeEvaluate(instructions);
    unsigned char *expressionJump   = instructions.SkipIfZeroStack(); // pops a non-zero or a zero from the stack
    unsigned char *address2         = instructions.GetAddress();
    mStatementNode->Code(instructions);
    unsigned char *loopJump         = instructions.Jump();
    unsigned char *address4         = instructions.GetAddress();
    instructions.SetOffset(expressionJump, address4 - address2);
    instructions.SetOffset(loopJump, (address1 - address4));
}

// MARK: - WhileStatement

RepeatStatementNode::RepeatStatementNode(ExpressionNode *expressionNode, StatementNode *statementNode)
: mExpressionNode(expressionNode)
, mStatementNode(statementNode)
{
    MSG("DoWhileStatementNode - Init")
}

RepeatStatementNode::~RepeatStatementNode() {
    MSG("DoWhileStatementNode - Delete Begin")
    delete mExpressionNode;
    delete mStatementNode;
    MSG("DoWhileStatementNode - Delete End")
}

void RepeatStatementNode::Interpret() {
    for (int i = 0;  i < mExpressionNode->Evaluate(); i++) {
        mStatementNode->Interpret();
    }
}

void RepeatStatementNode::Code(InstructionsClass &instructions) {
    mExpressionNode->CodeEvaluate(instructions);
    unsigned char *address0         = instructions.GetAddress();
    instructions.PopPushPush();
    unsigned char *jumpAddress1     = instructions.SkipIfZeroStack();
    unsigned char *address1         = instructions.GetAddress();
    instructions.PushValue(1);
    instructions.PopPopSubPush();
    mStatementNode->Code(instructions);
    unsigned char *jumpAddress2     = instructions.Jump();
    unsigned char *address2         = instructions.GetAddress();
    instructions.SetOffset(jumpAddress2, (address0 - address2));
    instructions.SetOffset(jumpAddress1, (address2 - address1));
    instructions.Pop();
}


// MARK: - DeclarationStatement

DeclarationStatementNode::DeclarationStatementNode(IdentifierNode *identifierNode, ExpressionNode *expressionNode)
: mIdentifierNode(identifierNode)
, mExpressionNode(expressionNode) {
    MSG("DeclarationStatementNode - Init")
}

DeclarationStatementNode::~DeclarationStatementNode() {
    MSG("DeclarationStatementNode - Delete Begin")
    delete mIdentifierNode;
    if (mExpressionNode != NULL) {
        delete mExpressionNode;
    }
    MSG("DeclarationStatementNode - Delete End")
}

void DeclarationStatementNode::Interpret() {
    mIdentifierNode->DeclareVariable();
    if (mExpressionNode != NULL) {
        int value = mExpressionNode->Evaluate();
        mIdentifierNode->SetValue(value);
    }
}

void DeclarationStatementNode::Code(InstructionsClass &instructions) {
    mIdentifierNode->DeclareVariable();
    if (mExpressionNode != NULL) {
        mExpressionNode->CodeEvaluate(instructions);
        int index = mIdentifierNode->GetIndex();
        instructions.PopAndStore(index);
    }
}

AssignmentNode::AssignmentNode(IdentifierNode *identifierNode, ExpressionNode *expressionNode)
: mIdentifierNode(identifierNode)
, mExpressionNode(expressionNode) {

}

AssignmentNode::~AssignmentNode() {
    MSG("AssignmentNode - Delete Begin")
    delete mIdentifierNode;
    delete mExpressionNode;
    MSG("AssignmentNode - Delete End")
}

// MARK: - AssignmentStatement

AssignmentStatementNode::AssignmentStatementNode(IdentifierNode *identifierNode, ExpressionNode *expressionNode)
: AssignmentNode(identifierNode, expressionNode) {
    MSG("AssignmentStatementNode - Init")
}

void AssignmentStatementNode::Interpret() {
    int value = mExpressionNode->Evaluate();
    mIdentifierNode->SetValue(value);
}

void AssignmentStatementNode::Code(InstructionsClass &instructions) {
    mExpressionNode->CodeEvaluate(instructions);
    int index = mIdentifierNode->GetIndex();
    instructions.PopAndStore(index);
}

// MARK: - PlusEqualStatement

PlusEqualStatementNode::PlusEqualStatementNode(IdentifierNode *identifierNode, ExpressionNode *expressionNode)
: AssignmentNode(identifierNode, expressionNode) {
    MSG("PlusEqualStatementNode - Init")

}

void PlusEqualStatementNode::Interpret() {
    int value = mExpressionNode->Evaluate();
    int currentValue = mIdentifierNode->Evaluate();
    mIdentifierNode->SetValue(currentValue + value);
}

void PlusEqualStatementNode::Code(InstructionsClass &instructions) {
    mExpressionNode->CodeEvaluate(instructions);
    mIdentifierNode->CodeEvaluate(instructions);
    instructions.PopPopAddPush();
    instructions.PopAndStore(mIdentifierNode->GetIndex());
}

// MARK: - MinusEqualStatement

MinusEqualStatementNode::MinusEqualStatementNode(IdentifierNode *identifierNode, ExpressionNode *expressionNode)
: AssignmentNode(identifierNode, expressionNode) {
    MSG("MinusEqualStatementNode - Init")

}

void MinusEqualStatementNode::Interpret() {
    int value = mExpressionNode->Evaluate();
    int currentValue = mIdentifierNode->Evaluate();
    mIdentifierNode->SetValue(currentValue - value);
}

void MinusEqualStatementNode::Code(InstructionsClass &instructions) {
    mExpressionNode->CodeEvaluate(instructions);
    mIdentifierNode->CodeEvaluate(instructions);
    instructions.PopPopSubPush();
    instructions.PopAndStore(mIdentifierNode->GetIndex());
}

// MARK: - TimesEqualStatement

TimesEqualStatementNode::TimesEqualStatementNode(IdentifierNode *identifierNode, ExpressionNode *expressionNode)
: AssignmentNode(identifierNode, expressionNode) {
    MSG("TimesEqualStatementNode - Init")
}

void TimesEqualStatementNode::Interpret() {
    int value = mExpressionNode->Evaluate();
    int currentValue = mIdentifierNode->Evaluate();
    mIdentifierNode->SetValue(currentValue * value);
}

void TimesEqualStatementNode::Code(InstructionsClass &instructions) {
    mExpressionNode->CodeEvaluate(instructions);
    mIdentifierNode->CodeEvaluate(instructions);
    instructions.PopPopMulPush();
    instructions.PopAndStore(mIdentifierNode->GetIndex());
}

// MARK: - DivideEqualStatement

DivideEqualStatementNode::DivideEqualStatementNode(IdentifierNode *identifierNode, ExpressionNode *expressionNode)
: AssignmentNode(identifierNode, expressionNode) {
    MSG("DivideEqualStatementNode - Init")
}

void DivideEqualStatementNode::Interpret() {
    int value = mExpressionNode->Evaluate();
    int currentValue = mIdentifierNode->Evaluate();
    mIdentifierNode->SetValue(currentValue / value);
}

void DivideEqualStatementNode::Code(InstructionsClass &instructions) {
    mExpressionNode->CodeEvaluate(instructions);
    mIdentifierNode->CodeEvaluate(instructions);
    instructions.PopPopDivPush();
    instructions.PopAndStore(mIdentifierNode->GetIndex());
}

// MARK: - Expression

ExpressionNode::~ExpressionNode() {

}

// MARK: - CoutStatement

CoutStatementNode::CoutStatementNode() {
    MSG("CoutStatementNode - Init")
}

CoutStatementNode::~CoutStatementNode() {
    MSG("CoutStatementNode - Delete Begin")
    for (ExpressionNode *expressionNode : mExpressionNodes) {
        if (expressionNode != NULL) {
            delete expressionNode;
        }
    }
    MSG("CoutStatementNode - Delete End")
}

void CoutStatementNode::AddStatement(ExpressionNode *expressionNode) {
    mExpressionNodes.push_back(expressionNode);
}

void CoutStatementNode::Interpret() {
    for (ExpressionNode *expressionNode : mExpressionNodes) {
        if (expressionNode == NULL) {
            cout << endl;
        } else {
            cout << expressionNode->Evaluate() << " ";
        }
    }
}

void CoutStatementNode::Code(InstructionsClass &instructions) {
    for (ExpressionNode *expressionNode : mExpressionNodes) {
        if (expressionNode == NULL) {
            instructions.WriteEndl();
        } else {
            expressionNode->CodeEvaluate(instructions);
            instructions.PopAndWrite();
        }
    }
}

// MARK: - Integer

IntegerNode::IntegerNode(int integer)
: mInteger(integer) {
    MSG("IntegerNode - Init")
}

int IntegerNode::Evaluate() {
    return mInteger;
}

void IntegerNode::CodeEvaluate(InstructionsClass &instructions) {
    instructions.PushValue(mInteger);
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
    try {
        mSymbolTable->AddEntry(mLabel);
    } catch (...) {
        cerr << "Invalid redeclaration of variable name: " << mLabel << endl;
        exit(1);
    }
}

void IdentifierNode::SetValue(int value) {
    try {
        mSymbolTable->SetValue(mLabel, value);
    } catch (...) {
        cerr << "Variable needs to be initialized first: " << mLabel << endl;
        exit(1);
    }
}

int IdentifierNode::GetIndex() {
    int index = mSymbolTable->GetIndex(mLabel);
    if (index < 0) {
        cerr << "Unknown variable: " << mLabel << endl;
        exit(1);
    }
    return index;
}

int IdentifierNode::Evaluate() {
    int value;
    try {
        value = mSymbolTable->GetValue(mLabel);
    } catch (...) {
        cerr << "Variable name used before initialization: " << mLabel << endl;
        exit(1);
    }
    return value;
}

void IdentifierNode::CodeEvaluate(InstructionsClass &instructions) {
    instructions.PushVariable(GetIndex());
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

void OrNode::CodeEvaluate(InstructionsClass &instructions) {
    mLeftSide->CodeEvaluate(instructions);
    mRightSide->CodeEvaluate(instructions);
    instructions.PopPopOrPush();
}

// MARK: - And

AndNode::AndNode(ExpressionNode *leftSide, ExpressionNode *rightSide)
: BinaryOperatorNode(leftSide, rightSide) {

}

int AndNode::Evaluate() {
    return mLeftSide->Evaluate() && mRightSide->Evaluate();
}

void AndNode::CodeEvaluate(InstructionsClass &instructions) {
    mLeftSide->CodeEvaluate(instructions);
    mRightSide->CodeEvaluate(instructions);
    instructions.PopPopAndPush();
}

// MARK: - Plus

PlusNode::PlusNode(ExpressionNode *leftSide, ExpressionNode *rightSide)
: BinaryOperatorNode(leftSide, rightSide) {
    MSG("PlusNode - Init")
}

int PlusNode::Evaluate() {
    return mLeftSide->Evaluate() + mRightSide->Evaluate();
}

void PlusNode::CodeEvaluate(InstructionsClass &instructions) {
    mLeftSide->CodeEvaluate(instructions);
    mRightSide->CodeEvaluate(instructions);
    instructions.PopPopAddPush();
}

// MARK: - Minus

MinusNode::MinusNode(ExpressionNode *leftSide, ExpressionNode *rightSide)
: BinaryOperatorNode(leftSide, rightSide) {
    MSG("PlusNode - Init")
}

int MinusNode::Evaluate() {
    return mLeftSide->Evaluate() - mRightSide->Evaluate();
}

void MinusNode::CodeEvaluate(InstructionsClass &instructions) {
    mLeftSide->CodeEvaluate(instructions);
    mRightSide->CodeEvaluate(instructions);
    instructions.PopPopSubPush();
}

// MARK: - Times

TimesNode::TimesNode(ExpressionNode *leftSide, ExpressionNode *rightSide)
: BinaryOperatorNode(leftSide, rightSide) {
    MSG("PlusNode - Init")
}

int TimesNode::Evaluate() {
    return mLeftSide->Evaluate() * mRightSide->Evaluate();
}

void TimesNode::CodeEvaluate(InstructionsClass &instructions) {
    mLeftSide->CodeEvaluate(instructions);
    mRightSide->CodeEvaluate(instructions);
    instructions.PopPopMulPush();
}

// MARK: - Divide

DivideNode::DivideNode(ExpressionNode *leftSide, ExpressionNode *rightSide)
: BinaryOperatorNode(leftSide, rightSide) {
    MSG("PlusNode - Init")
}

int DivideNode::Evaluate() {
    return mLeftSide->Evaluate() / mRightSide->Evaluate();
}

void DivideNode::CodeEvaluate(InstructionsClass &instructions) {
    mLeftSide->CodeEvaluate(instructions);
    mRightSide->CodeEvaluate(instructions);
    instructions.PopPopDivPush();
}

// MARK: - Modulus

ModulusNode::ModulusNode(ExpressionNode *leftSide, ExpressionNode *rightSide)
: BinaryOperatorNode(leftSide, rightSide) {
    MSG("PlusNode - Init")
}

int ModulusNode::Evaluate() {
    return mLeftSide->Evaluate() % mRightSide->Evaluate();
}

void ModulusNode::CodeEvaluate(InstructionsClass &instructions) {
    mLeftSide->CodeEvaluate(instructions);
    mRightSide->CodeEvaluate(instructions);
    instructions.PopPopModPush();
}

// MARK: - Less

LessNode::LessNode(ExpressionNode *leftSide, ExpressionNode *rightSide)
: BinaryOperatorNode(leftSide, rightSide) {
    MSG("LessNode - Init")
}

int LessNode::Evaluate() {
    return mLeftSide->Evaluate() < mRightSide->Evaluate();
}

void LessNode::CodeEvaluate(InstructionsClass &instructions) {
    mLeftSide->CodeEvaluate(instructions);
    mRightSide->CodeEvaluate(instructions);
    instructions.PopPopLessPush();
}

// MARK: - LessEqual

LessEqualNode::LessEqualNode(ExpressionNode *leftSide, ExpressionNode *rightSide)
: BinaryOperatorNode(leftSide, rightSide) {
    MSG("LessEqualNode - Init")
}

int LessEqualNode::Evaluate() {
    return mLeftSide->Evaluate() <= mRightSide->Evaluate();
}

void LessEqualNode::CodeEvaluate(InstructionsClass &instructions) {
    mLeftSide->CodeEvaluate(instructions);
    mRightSide->CodeEvaluate(instructions);
    instructions.PopPopLessEqualPush();
}

// MARK: - Greater

GreaterNode::GreaterNode(ExpressionNode *leftSide, ExpressionNode *rightSide)
: BinaryOperatorNode(leftSide, rightSide) {
    MSG("GreaterNode - Init")
}

int GreaterNode::Evaluate() {
    return mLeftSide->Evaluate() > mRightSide->Evaluate();
}

void GreaterNode::CodeEvaluate(InstructionsClass &instructions) {
    mLeftSide->CodeEvaluate(instructions);
    mRightSide->CodeEvaluate(instructions);
    instructions.PopPopGreaterPush();
}

// MARK: - GreaterEqual

GreaterEqualNode::GreaterEqualNode(ExpressionNode *leftSide, ExpressionNode *rightSide)
: BinaryOperatorNode(leftSide, rightSide) {
    MSG("GreaterEqualNode - Init")
}

int GreaterEqualNode::Evaluate() {
    return mLeftSide->Evaluate() >= mRightSide->Evaluate();
}

void GreaterEqualNode::CodeEvaluate(InstructionsClass &instructions) {
    mLeftSide->CodeEvaluate(instructions);
    mRightSide->CodeEvaluate(instructions);
    instructions.PopPopGreaterEqualPush();
}

// MARK: - Equal

EqualNode::EqualNode(ExpressionNode *leftSide, ExpressionNode *rightSide)
: BinaryOperatorNode(leftSide, rightSide) {
    MSG("EqualNode - Init")
}

int EqualNode::Evaluate() {
    return mLeftSide->Evaluate() == mRightSide->Evaluate();
}

void EqualNode::CodeEvaluate(InstructionsClass &instructions) {
    mLeftSide->CodeEvaluate(instructions);
    mRightSide->CodeEvaluate(instructions);
    instructions.PopPopEqualPush();
}

// MARK: - NotEqual

NotEqualNode::NotEqualNode(ExpressionNode *leftSide, ExpressionNode *rightSide)
: BinaryOperatorNode(leftSide, rightSide) {
    MSG("NotEqualNode - Init")
}

int NotEqualNode::Evaluate() {
    return mLeftSide->Evaluate() != mRightSide->Evaluate();
}

void NotEqualNode::CodeEvaluate(InstructionsClass &instructions) {
    mLeftSide->CodeEvaluate(instructions);
    mRightSide->CodeEvaluate(instructions);
    instructions.PopPopNotEqualPush();
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

void NotNode::CodeEvaluate(InstructionsClass &instructions) {
    mExpression->CodeEvaluate(instructions);
    instructions.PopNotPush();
}

// MARK: - Not

NegativeNode::NegativeNode(ExpressionNode *expression)
: UnaryOperatorNode(expression) {
    MSG("NegativeNode - Init")
}

int NegativeNode::Evaluate() {
    return -mExpression->Evaluate();
}

void NegativeNode::CodeEvaluate(InstructionsClass &instructions) {
    mExpression->CodeEvaluate(instructions);
    instructions.PopNegatePush();
}






