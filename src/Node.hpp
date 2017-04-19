//
//  Node.hpp
//  SimpleCompiler
//
//  Created by Kaden Wilkinson on 2/22/17.
//  Copyright © 2017 Kaden Wilkinson. All rights reserved.
//

#ifndef Node_hpp
#define Node_hpp

#include "Symbol.hpp"


// forward declarations:
class Node;
class StartNode;
class ProgramNode;
class BlockNode;
class StatementGroupNode;
class StatementNode;
class DeclarationStatementNode;
class AssignmentStatementNode;
class CoutStatementNode;
class ExpressionNode;
class IntegerNode;
class IdentifierNode;
class BinaryOperatorNode;
class PlusNode;


// MARK: - Node

class Node {
public:
    virtual ~Node();
    virtual void Interpret() = 0;
};

// MARK: - Start

class StartNode : public Node {
    ProgramNode *mProgramNode;

public:
    StartNode(ProgramNode *programNode);
    ~StartNode();
    virtual void Interpret();
};

// MARK: - Program

class ProgramNode: public Node {
    BlockNode *mBlockNode;

public:
    ProgramNode(BlockNode *blockNode);
    ~ProgramNode();
    void Interpret();
};

// MARK: - Statement

class StatementNode : public Node {
    public:
    //    virtual ~StatementNode();
};

// MARK: - Block

class BlockNode : public StatementNode {
    StatementGroupNode *mStatementGroupNode;
    SymbolTableClass *mSymbolTable;
public:
    BlockNode(SymbolTableClass *symbolTable, StatementGroupNode *statmentGroupNode);
    ~BlockNode();
    void Interpret();
};

// MARK: - StatementGroup

class StatementGroupNode : public Node {
    vector<StatementNode *> mStatementNodes;
    
public:
    StatementGroupNode();
    ~StatementGroupNode();

    void AddStatement(StatementNode *statementNode);
    void Interpret();
};

// MARK: - IfStatement

class IfStatementNode : public StatementNode {
    ExpressionNode *mExpressionNode;
    StatementNode *mStatementNode;

public:
    IfStatementNode(ExpressionNode *expressionNode, StatementNode *statementNode);
    ~IfStatementNode();

    void Interpret();
};

// MARK: - WhileStatement

class WhileStatementNode : public StatementNode {
    ExpressionNode *mExpressionNode;
    StatementNode *mStatementNode;

public:
    WhileStatementNode(ExpressionNode *expressionNode, StatementNode *statementNode);
    ~WhileStatementNode();

    void Interpret();
};


// MARK: - DeclarationStatement

class DeclarationStatementNode : public StatementNode {
    IdentifierNode *mIdentifierNode;

public:
    DeclarationStatementNode(IdentifierNode *identifierNode);
    ~DeclarationStatementNode();
    void Interpret();
};

// MARK: - AssignmentStatement

class AssignmentStatementNode : public StatementNode {
    IdentifierNode *mIdentifierNode;
    ExpressionNode *mExpressionNode;

public:
    AssignmentStatementNode(IdentifierNode *identifierNode, ExpressionNode *expressionNode);
    ~AssignmentStatementNode();
    void Interpret();
};

// MARK: - PlusEqualStatement

class PlusEqualStatementNode : public StatementNode {
    IdentifierNode *mIdentifierNode;
    ExpressionNode *mExpressionNode;

public:
    PlusEqualStatementNode(IdentifierNode *identifierNode, ExpressionNode *expressionNode);
    ~PlusEqualStatementNode();
    void Interpret();
};

// MARK: - MinusEqualStatement

class MinusEqualStatementNode : public StatementNode {
    IdentifierNode *mIdentifierNode;
    ExpressionNode *mExpressionNode;

public:
    MinusEqualStatementNode(IdentifierNode *identifierNode, ExpressionNode *expressionNode);
    ~MinusEqualStatementNode();
    void Interpret();
};

// MARK: - TimesEqualStatement

class TimesEqualStatementNode : public StatementNode {
    IdentifierNode *mIdentifierNode;
    ExpressionNode *mExpressionNode;

public:
    TimesEqualStatementNode(IdentifierNode *identifierNode, ExpressionNode *expressionNode);
    ~TimesEqualStatementNode();
    void Interpret();
};

// MARK: - DivideEqualStatement

class DivideEqualStatementNode : public StatementNode {
    IdentifierNode *mIdentifierNode;
    ExpressionNode *mExpressionNode;

public:
    DivideEqualStatementNode(IdentifierNode *identifierNode, ExpressionNode *expressionNode);
    ~DivideEqualStatementNode();
    void Interpret();
};


// MARK: - CoutStatement

class CoutStatementNode : public StatementNode {
    ExpressionNode *mExpressionNode;

public:
    CoutStatementNode(ExpressionNode *expressionNode);
    ~CoutStatementNode();
    void Interpret();
};

// MARK: - Expression

class ExpressionNode {
public:
    virtual ~ExpressionNode();

    virtual int Evaluate() = 0;
};

// MARK: - Integer

class IntegerNode : public ExpressionNode {
    int mInteger;
public:
    IntegerNode(int integer);

    int Evaluate();
};

// MARK: - Identifier

class IdentifierNode : public ExpressionNode {
    string mLabel;
    SymbolTableClass *mSymbolTable;

public:
    IdentifierNode(string label, SymbolTableClass *symbolTable);
    ~IdentifierNode();

    void DeclareVariable();
    void SetValue(int value);
    int GetIndex();

    int Evaluate();
};

// MARK: - BinaryOperator

class BinaryOperatorNode : public ExpressionNode {
protected:
    ExpressionNode *mLeftSide;
    ExpressionNode *mRightSide;
public:
    BinaryOperatorNode(ExpressionNode *leftSide, ExpressionNode *rightSide);
    virtual ~BinaryOperatorNode();
};

// MARK: - Or

class OrNode : public BinaryOperatorNode {

public:
    OrNode(ExpressionNode *leftSide, ExpressionNode *rightSide);

    int Evaluate();
};

// MARK: - And

class AndNode : public BinaryOperatorNode {

public:
    AndNode(ExpressionNode *leftSide, ExpressionNode *rightSide);

    int Evaluate();
};


// MARK: - Plus

class PlusNode : public BinaryOperatorNode {

public:
    PlusNode(ExpressionNode *leftSide, ExpressionNode *rightSide);

    int Evaluate();
};

// MARK: - Minus

class MinusNode : public BinaryOperatorNode {

public:
    MinusNode(ExpressionNode *leftSide, ExpressionNode *rightSide);

    int Evaluate();
};

// MARK: - Times

class TimesNode : public BinaryOperatorNode {

public:
    TimesNode(ExpressionNode *leftSide, ExpressionNode *rightSide);

    int Evaluate();
};

// MARK: - Divide

class DivideNode : public BinaryOperatorNode {

public:
    DivideNode(ExpressionNode *leftSide, ExpressionNode *rightSide);

    int Evaluate();
};

// MARK: - Less

class LessNode : public BinaryOperatorNode {

public:
    LessNode(ExpressionNode *leftSide, ExpressionNode *rightSide);

    int Evaluate();
};

// MARK: - LessEqual

class LessEqualNode : public BinaryOperatorNode {

public:
    LessEqualNode(ExpressionNode *leftSide, ExpressionNode *rightSide);

    int Evaluate();
};

// MARK: - Greater

class GreaterNode : public BinaryOperatorNode {

public:
    GreaterNode(ExpressionNode *leftSide, ExpressionNode *rightSide);

    int Evaluate();
};

// MARK: - GreaterEqual

class GreaterEqualNode : public BinaryOperatorNode {

public:
    GreaterEqualNode(ExpressionNode *leftSide, ExpressionNode *rightSide);
    
    int Evaluate();
};

// MARK: - Equal

class EqualNode : public BinaryOperatorNode {

public:
    EqualNode(ExpressionNode *leftSide, ExpressionNode *rightSide);

    int Evaluate();
};

// MARK: - NotEqual

class NotEqualNode : public BinaryOperatorNode {

public:
    NotEqualNode(ExpressionNode *leftSide, ExpressionNode *rightSide);

    int Evaluate();
};


// Unary Operators:
//NOT_TOKEN,
//NEGATIVE_TOKEN,

// MARK: - UnaryOperator

class UnaryOperatorNode : public ExpressionNode {
protected:
    ExpressionNode *mExpression;
public:
    UnaryOperatorNode(ExpressionNode *expression);
    virtual ~UnaryOperatorNode();
};

// MARK: - Not

class NotNode : public UnaryOperatorNode {

public:
    NotNode(ExpressionNode *expression);

    int Evaluate();
};

// MARK: - Negative

class NegativeNode : public UnaryOperatorNode {

public:
    NegativeNode(ExpressionNode *expression);

    int Evaluate();
};



#endif /* Node_hpp */
