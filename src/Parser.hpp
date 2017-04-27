//
//  Parser.hpp
//  SimpleCompiler
//
//  Created by Kaden Wilkinson on 2/22/17.
//  Copyright © 2017 Kaden Wilkinson. All rights reserved.
//

#ifndef Parser_hpp
#define Parser_hpp

#include "Token.hpp"
#include "Node.hpp"
#include "Scanner.hpp"
#include "Symbol.hpp"

class ParserClass {
    ScannerClass *mScanner;
    SymbolTableClass *mSymbolTable;
    FRIEND_TEST(ParserClassTests, Init);

    virtual TokenClass Match(TokenType expectedType);
    FRIEND_TEST(ParserClassTests, Match_Valid);
    FRIEND_TEST(ParserClassTests, Match_Invalid);

    virtual ProgramNode *Program();
    FRIEND_TEST(ParserClassTests, Program);
    virtual BlockNode *Block();
    FRIEND_TEST(ParserClassTests, Block);
    virtual StatementGroupNode *StatementGroup();
    FRIEND_TEST(ParserClassTests, StatementGroup);
    virtual StatementNode *Statement();
    FRIEND_TEST(ParserClassTests, Statement_DeclarationStatement);
    FRIEND_TEST(ParserClassTests, Statement_IfStatement);
    FRIEND_TEST(ParserClassTests, Statement_WhileStatement);
    FRIEND_TEST(ParserClassTests, Statement_AssignmentStatement);
    FRIEND_TEST(ParserClassTests, Statement_CoutStatement);
    FRIEND_TEST(ParserClassTests, Statement_Block);
    FRIEND_TEST(ParserClassTests, Statement_Null);
    virtual IfStatementNode *IfStatement();
    FRIEND_TEST(ParserClassTests, IfStatement);
    virtual WhileStatementNode *WhileStatement();
    FRIEND_TEST(ParserClassTests, WhileStatement);
    virtual DoWhileStatementNode *DoWhileStatement();
    virtual RepeatStatementNode *RepeatStatement();

    virtual DeclarationStatementNode *DeclarationStatement();
    FRIEND_TEST(ParserClassTests, DeclarationStatement);
    virtual AssignmentNode *AssignmentStatement();
    FRIEND_TEST(ParserClassTests, AssignmentStatement);
    virtual CoutStatementNode *CoutStatement();
    FRIEND_TEST(ParserClassTests, CoutStatement);

    virtual ExpressionNode *Expression();
    FRIEND_TEST(ParserClassTests, Expression);
    virtual ExpressionNode *Or();
    FRIEND_TEST(ParserClassTests, Or);
    virtual ExpressionNode *And();
    FRIEND_TEST(ParserClassTests, And);
    virtual ExpressionNode *Relationals();
    FRIEND_TEST(ParserClassTests, Relationals);
    virtual ExpressionNode *PlusMinus();
    FRIEND_TEST(ParserClassTests, PlusMinus);
    virtual ExpressionNode *TimesDivide();
    FRIEND_TEST(ParserClassTests, TimesDivide);
    virtual ExpressionNode *Unaries();
    FRIEND_TEST(ParserClassTests, Unaries);
    virtual ExpressionNode *Factor();
    FRIEND_TEST(ParserClassTests, Factor);

    virtual IdentifierNode *Identifier();
    FRIEND_TEST(ParserClassTests, Identifier);
    virtual IntegerNode *Integer();
    FRIEND_TEST(ParserClassTests, Integer);

public:
    ParserClass(ScannerClass *scanner, SymbolTableClass *symbolTable);
    virtual ~ParserClass();
    StartNode *Start();
};

#endif /* Parser_hpp */
