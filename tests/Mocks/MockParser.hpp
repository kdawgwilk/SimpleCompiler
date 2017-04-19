//
//  MockParser.hpp
//  SimpleCompiler
//
//  Created by Kaden Wilkinson on 3/22/17.
//  Copyright © 2017 Kaden Wilkinson. All rights reserved.
//

#ifndef MockParser_hpp
#define MockParser_hpp

#include "Parser.hpp"

class MockParserClass: public ParserClass {
    MOCK_METHOD1(Match, TokenClass(TokenType expectedType));
    FRIEND_TEST(ParserClassTests, Match_Valid);
    FRIEND_TEST(ParserClassTests, Match_Invalid);



    MOCK_METHOD0(Program, ProgramNode *());
    FRIEND_TEST(ParserClassTests, Program);

    MOCK_METHOD0(Block, BlockNode *());
    FRIEND_TEST(ParserClassTests, Block);

    MOCK_METHOD0(StatementGroup, StatementGroupNode *());
    FRIEND_TEST(ParserClassTests, StatementGroup);

    MOCK_METHOD0(Statement, StatementNode *());
    FRIEND_TEST(ParserClassTests, Statement);

    MOCK_METHOD0(IfStatement, IfStatementNode *());
    FRIEND_TEST(ParserClassTests, IfStatement);



    MOCK_METHOD0(WhileStatement, WhileStatementNode *());
    FRIEND_TEST(ParserClassTests, WhileStatement);

    MOCK_METHOD0(DeclarationStatement, DeclarationStatementNode *());
    FRIEND_TEST(ParserClassTests, DeclarationStatement);

    MOCK_METHOD0(AssignmentStatement, AssignmentStatementNode *());
    FRIEND_TEST(ParserClassTests, AssignmentStatement);

    MOCK_METHOD0(CoutStatement, CoutStatementNode *());
    FRIEND_TEST(ParserClassTests, CoutStatement);

    MOCK_METHOD0(Expression, ExpressionNode *());
    FRIEND_TEST(ParserClassTests, Expression);

    MOCK_METHOD0(Or, ExpressionNode *());
    FRIEND_TEST(ParserClassTests, Or);

    MOCK_METHOD0(And, ExpressionNode *());
    FRIEND_TEST(ParserClassTests, And);

    MOCK_METHOD0(Relationals, ExpressionNode *());
    FRIEND_TEST(ParserClassTests, Relationals);

    MOCK_METHOD0(PlusMinus, ExpressionNode *());
    FRIEND_TEST(ParserClassTests, PlusMinus);

    MOCK_METHOD0(TimesDivide, ExpressionNode *());
    FRIEND_TEST(ParserClassTests, TimesDivide);

    MOCK_METHOD0(Unaries, ExpressionNode *());
    FRIEND_TEST(ParserClassTests, Unaries);

    MOCK_METHOD0(Factor, ExpressionNode *());
    FRIEND_TEST(ParserClassTests, Factor);


    
    MOCK_METHOD0(Identifier, IdentifierNode *());
    FRIEND_TEST(ParserClassTests, Identifier);

    MOCK_METHOD0(Integer, IntegerNode *());
    FRIEND_TEST(ParserClassTests, Integer);

public:
    MockParserClass(ScannerClass *scanner, SymbolTableClass *symbolTable): ParserClass(scanner, symbolTable) {}
    MOCK_METHOD0(Start, StartNode *());
};



#endif /* MockParser_hpp */
