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
#include "Instructions.hpp"


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
    virtual void Code(InstructionsClass &instructions) = 0;
};

// MARK: - Start

class StartNode : public Node {
    ProgramNode *mProgramNode;

public:
    StartNode(ProgramNode *programNode);
    ~StartNode();
    void Interpret();
    void Code(InstructionsClass &instructions);
};

// MARK: - Program

class ProgramNode: public Node {
    BlockNode *mBlockNode;

public:
    ProgramNode(BlockNode *blockNode);
    ~ProgramNode();
    void Interpret();
    void Code(InstructionsClass &instructions);
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
    void Code(InstructionsClass &instructions);
};

// MARK: - StatementGroup

class StatementGroupNode : public Node {
    vector<StatementNode *> mStatementNodes;
    
public:
    StatementGroupNode();
    ~StatementGroupNode();

    void AddStatement(StatementNode *statementNode);
    void Interpret();
    void Code(InstructionsClass &instructions);
};

// MARK: - IfStatement

class IfStatementNode : public StatementNode {
    ExpressionNode *mExpressionNode;
    StatementNode *mIfStatementNode;
    StatementNode *mElseStatementNode;

public:
    IfStatementNode(ExpressionNode *expressionNode, StatementNode *ifStatementNode, StatementNode *elseStatementNode);
    ~IfStatementNode();

    void Interpret();
    void Code(InstructionsClass &instructions);
};

// MARK: - WhileStatement

class WhileStatementNode : public StatementNode {
    ExpressionNode *mExpressionNode;
    StatementNode *mStatementNode;

public:
    WhileStatementNode(ExpressionNode *expressionNode, StatementNode *statementNode);
    ~WhileStatementNode();

    void Interpret();
    void Code(InstructionsClass &instructions);
};

// MARK: - DoWhileStatement

class DoWhileStatementNode : public StatementNode {
    ExpressionNode *mExpressionNode;
    StatementNode *mStatementNode;

public:
    DoWhileStatementNode(ExpressionNode *expressionNode, StatementNode *statementNode);
    ~DoWhileStatementNode();

    void Interpret();
    void Code(InstructionsClass &instructions);
};

// MARK: - DoWhileStatement

class RepeatStatementNode : public StatementNode {
    ExpressionNode *mExpressionNode;
    StatementNode *mStatementNode;

public:
    RepeatStatementNode(ExpressionNode *expressionNode, StatementNode *statementNode);
    ~RepeatStatementNode();

    void Interpret();
    void Code(InstructionsClass &instructions);
};


// MARK: - DeclarationStatement

class DeclarationStatementNode : public StatementNode {
    IdentifierNode *mIdentifierNode;
    ExpressionNode *mExpressionNode;
    
public:
    DeclarationStatementNode(IdentifierNode *identifierNode, ExpressionNode *expressionNode);
    ~DeclarationStatementNode();
    void Interpret();
    void Code(InstructionsClass &instructions);
};

// MARK: - Assignment

class AssignmentNode : public StatementNode {

protected:
    IdentifierNode *mIdentifierNode;
    ExpressionNode *mExpressionNode;
public:
    AssignmentNode(IdentifierNode *identifierNode, ExpressionNode *expressionNode);
    virtual ~AssignmentNode();
    virtual void Interpret() = 0;
    virtual void Code(InstructionsClass &instructions) = 0;
};

// MARK: - AssignmentStatement

class AssignmentStatementNode : public AssignmentNode {

public:
    AssignmentStatementNode(IdentifierNode *identifierNode, ExpressionNode *expressionNode);
    void Interpret();
    void Code(InstructionsClass &instructions);
};

// MARK: - PlusEqualStatement

class PlusEqualStatementNode : public AssignmentNode {

public:
    PlusEqualStatementNode(IdentifierNode *identifierNode, ExpressionNode *expressionNode);
    void Interpret();
    void Code(InstructionsClass &instructions);
};

// MARK: - MinusEqualStatement

class MinusEqualStatementNode : public AssignmentNode {
public:
    MinusEqualStatementNode(IdentifierNode *identifierNode, ExpressionNode *expressionNode);
    void Interpret();
    void Code(InstructionsClass &instructions);
};

// MARK: - TimesEqualStatement

class TimesEqualStatementNode : public AssignmentNode {
public:
    TimesEqualStatementNode(IdentifierNode *identifierNode, ExpressionNode *expressionNode);
    void Interpret();
    void Code(InstructionsClass &instructions);
};

// MARK: - DivideEqualStatement

class DivideEqualStatementNode : public AssignmentNode {
public:
    DivideEqualStatementNode(IdentifierNode *identifierNode, ExpressionNode *expressionNode);
    void Interpret();
    void Code(InstructionsClass &instructions);
};


// MARK: - CoutStatement

class CoutStatementNode : public StatementNode {
    vector<ExpressionNode *> mExpressionNodes;

public:
    CoutStatementNode();
    ~CoutStatementNode();

    void AddStatement(ExpressionNode *expressionNode);
    void Interpret();
    void Code(InstructionsClass &instructions);
};

// MARK: - Expression

class ExpressionNode {
public:
    virtual ~ExpressionNode();
    virtual int Evaluate() = 0;
    virtual void CodeEvaluate(InstructionsClass &instructions) = 0;
};

// MARK: - Integer

class IntegerNode : public ExpressionNode {
    int mInteger;
public:
    IntegerNode(int integer);

    int Evaluate();
    void CodeEvaluate(InstructionsClass &instructions);
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
    void CodeEvaluate(InstructionsClass &instructions);
};

// MARK: - BinaryOperator

class BinaryOperatorNode : public ExpressionNode {
protected:
    ExpressionNode *mLeftSide;
    ExpressionNode *mRightSide;
public:
    BinaryOperatorNode(ExpressionNode *leftSide, ExpressionNode *rightSide);
    virtual ~BinaryOperatorNode();
    virtual int Evaluate() = 0;
    virtual void CodeEvaluate(InstructionsClass &instructions) = 0;
};

// MARK: - Or

class OrNode : public BinaryOperatorNode {
public:
    OrNode(ExpressionNode *leftSide, ExpressionNode *rightSide);

    int Evaluate();
    void CodeEvaluate(InstructionsClass &instructions);
};

// MARK: - And

class AndNode : public BinaryOperatorNode {
public:
    AndNode(ExpressionNode *leftSide, ExpressionNode *rightSide);

    int Evaluate();
    void CodeEvaluate(InstructionsClass &instructions);
};


// MARK: - Plus

class PlusNode : public BinaryOperatorNode {
public:
    PlusNode(ExpressionNode *leftSide, ExpressionNode *rightSide);

    int Evaluate();
    void CodeEvaluate(InstructionsClass &instructions);
};

// MARK: - Minus

class MinusNode : public BinaryOperatorNode {
public:
    MinusNode(ExpressionNode *leftSide, ExpressionNode *rightSide);

    int Evaluate();
    void CodeEvaluate(InstructionsClass &instructions);
};

// MARK: - Times

class TimesNode : public BinaryOperatorNode {
public:
    TimesNode(ExpressionNode *leftSide, ExpressionNode *rightSide);

    int Evaluate();
    void CodeEvaluate(InstructionsClass &instructions);
};

// MARK: - Divide

class DivideNode : public BinaryOperatorNode {
public:
    DivideNode(ExpressionNode *leftSide, ExpressionNode *rightSide);

    int Evaluate();
    void CodeEvaluate(InstructionsClass &instructions);
};

// MARK: - Modulus

class ModulusNode : public BinaryOperatorNode {
public:
    ModulusNode(ExpressionNode *leftSide, ExpressionNode *rightSide);

    int Evaluate();
    void CodeEvaluate(InstructionsClass &instructions);
};

// MARK: - Less

class LessNode : public BinaryOperatorNode {
public:
    LessNode(ExpressionNode *leftSide, ExpressionNode *rightSide);

    int Evaluate();
    void CodeEvaluate(InstructionsClass &instructions);
};

// MARK: - LessEqual

class LessEqualNode : public BinaryOperatorNode {
public:
    LessEqualNode(ExpressionNode *leftSide, ExpressionNode *rightSide);

    int Evaluate();
    void CodeEvaluate(InstructionsClass &instructions);
};

// MARK: - Greater

class GreaterNode : public BinaryOperatorNode {
public:
    GreaterNode(ExpressionNode *leftSide, ExpressionNode *rightSide);

    int Evaluate();
    void CodeEvaluate(InstructionsClass &instructions);
};

// MARK: - GreaterEqual

class GreaterEqualNode : public BinaryOperatorNode {
public:
    GreaterEqualNode(ExpressionNode *leftSide, ExpressionNode *rightSide);
    
    int Evaluate();
    void CodeEvaluate(InstructionsClass &instructions);
};

// MARK: - Equal

class EqualNode : public BinaryOperatorNode {
public:
    EqualNode(ExpressionNode *leftSide, ExpressionNode *rightSide);

    int Evaluate();
    void CodeEvaluate(InstructionsClass &instructions);
};

// MARK: - NotEqual

class NotEqualNode : public BinaryOperatorNode {
public:
    NotEqualNode(ExpressionNode *leftSide, ExpressionNode *rightSide);

    int Evaluate();
    void CodeEvaluate(InstructionsClass &instructions);
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
    void CodeEvaluate(InstructionsClass &instructions);
};

// MARK: - Negative

class NegativeNode : public UnaryOperatorNode {
public:
    NegativeNode(ExpressionNode *expression);

    int Evaluate();
    void CodeEvaluate(InstructionsClass &instructions);
};



#endif /* Node_hpp */
