//
//  ParserTests.cpp
//  SimpleCompiler
//
//  Created by Kaden Wilkinson on 2/22/17.
//  Copyright © 2017 Kaden Wilkinson. All rights reserved.
//

#include "MockScanner.hpp"
#include "MockSymbolTable.hpp"
#include "MockParser.hpp"

#include "Node.hpp"

string FILENAME = "test_code_1.c";

class ParserClassTests : public Test {
protected:
//    MockScannerClass *scanner;
//    MockSymbolTableClass *symbolTable;
//    ParserClass *parser;


    static void SetUpTestCase() {

    }

    static void TearDownTestCase() {

    }

    virtual void SetUp() {
//        scanner = new MockScannerClass;
//        symbolTable = new MockSymbolTableClass();

//        MockScannerClass *scanner = new MockScannerClass("test_code_1.c");
//        MockSymbolTableClass *symbolTable = new MockSymbolTableClass();
//
//        parser = new ParserClass(scanner, symbolTable);
    }

    virtual void TearDown() {
//        delete parser;
    }
};


TEST_F(ParserClassTests, ParseFile) {
//    MockScannerClass sc("test_code_1.c");
//    MockSymbolTableClass stc;
//
//    ParserClass parser(&sc, &stc);
//
//    StartNode *st = parser.Start();
//
//    delete st;
//
//    EXPECT_EQ(0, 0);
}

TEST_F(ParserClassTests, ParseMidterm1) {
//    ScannerClass scanner("test_code_midterm1.c");
//    SymbolTableClass symbolTable;
//    ParserClass parser(&scanner, &symbolTable);
//
//    StartNode *startNode = parser.Start();
//
//    cout << "########## Interpret Start ##########" << endl;
//    startNode->Interpret();
//    cout << "########## Interpret End ##########" << endl;
//
//    delete startNode;
    EXPECT_EQ(0, 0);
}

TEST_F(ParserClassTests, ParseMidterm2) {
//    ScannerClass scanner("test_code_midterm2.c");
//    SymbolTableClass symbolTable;
//    ParserClass parser(&scanner, &symbolTable);
//
//    StartNode *startNode = parser.Start();
//
//    cout << "########## Interpret Start ##########" << endl;
//    startNode->Interpret();
//    cout << "########## Interpret End ##########" << endl;
//
//    delete startNode;
    EXPECT_EQ(0, 0);
}


// MARK: - Public


// MARK: Init

TEST_F(ParserClassTests, Init) {
    MockScannerClass scanner;
    MockSymbolTableClass symbolTable;
    ParserClass parser(&scanner, &symbolTable);

    EXPECT_NE(parser.mScanner, nullptr);
    EXPECT_NE(parser.mSymbolTable, nullptr);
}

// MARK: Start

class MockForStartParserClass: public ParserClass {
    MOCK_METHOD1(Match, TokenClass(TokenType expectedType));
    MOCK_METHOD0(Program, ProgramNode *());
    FRIEND_TEST(ParserClassTests, Start);
public:
    MockForStartParserClass(ScannerClass *scanner, SymbolTableClass *symbolTable):
        ParserClass(scanner, symbolTable) {}
};

TEST_F(ParserClassTests, Start) {
    MockScannerClass scanner;
    MockSymbolTableClass symbolTable;
    MockForStartParserClass parser(&scanner, &symbolTable);
    string endFile;
    endFile.push_back(EOF);

    ON_CALL(parser, Program()).WillByDefault(Return(new ProgramNode(nullptr)));
    ON_CALL(parser, Match(ENDFILE_TOKEN)).WillByDefault(Return(TokenClass(ENDFILE_TOKEN, endFile)));
    EXPECT_CALL(parser, Program()).Times(1);
    EXPECT_CALL(parser, Match(ENDFILE_TOKEN)).Times(1);
    auto startNode = parser.Start();
    EXPECT_NE(startNode, nullptr);
}

// MARK: - Private

TEST_F(ParserClassTests, Match_Valid) {
    MockScannerClass scanner;
    MockSymbolTableClass symbolTable;
    ParserClass parser(&scanner, &symbolTable);

    ON_CALL(scanner, GetNextToken()).WillByDefault(Return(TokenClass(VOID_TOKEN, "void")));
    EXPECT_CALL(scanner, GetNextToken()).Times(1);
    auto token = parser.Match(VOID_TOKEN);
    EXPECT_EQ(token.GetTokenType(), VOID_TOKEN);
}

TEST_F(ParserClassTests, Match_Invalid) {
    MockScannerClass scanner;
    MockSymbolTableClass symbolTable;
    ParserClass parser(&scanner, &symbolTable);

    ON_CALL(scanner, GetNextToken()).WillByDefault(Return(TokenClass(VOID_TOKEN, "void")));
    // WTF: Call goes undetected in when ran inside a EXPECT_EXIT
//    EXPECT_CALL(scanner, GetNextToken()).Times(1);
    EXPECT_DEATH(parser.Match(INT_TOKEN), "Expected token type INTEGER, but got type VOID");
}

// MARK: Program

class MockForProgramTestParserClass: public ParserClass {
    MOCK_METHOD1(Match, TokenClass(TokenType expectedType));
    MOCK_METHOD0(Block, BlockNode *());
    FRIEND_TEST(ParserClassTests, Program);
public:
    MockForProgramTestParserClass(ScannerClass *scanner, SymbolTableClass *symbolTable):
        ParserClass(scanner, symbolTable) {}
};

TEST_F(ParserClassTests, Program) {
    MockScannerClass scanner;
    MockSymbolTableClass symbolTable;
    MockForProgramTestParserClass parser(&scanner, &symbolTable);

    ON_CALL(parser, Block()).WillByDefault(Return(new BlockNode(nullptr, nullptr)));
    ON_CALL(parser, Match(_)).WillByDefault(Return(TokenClass(BAD_TOKEN, "")));
    EXPECT_CALL(parser, Match(VOID_TOKEN)).Times(1);
    EXPECT_CALL(parser, Match(MAIN_TOKEN)).Times(1);
    EXPECT_CALL(parser, Match(LPAREN_TOKEN)).Times(1);
    EXPECT_CALL(parser, Match(RPAREN_TOKEN)).Times(1);
    EXPECT_CALL(parser, Block()).Times(1);
    auto programNode = parser.Program();
    EXPECT_NE(programNode, nullptr);
}

// MARK: Block

class MockForBlockTestParserClass: public ParserClass {
    MOCK_METHOD1(Match, TokenClass(TokenType expectedType));
    MOCK_METHOD0(StatementGroup, StatementGroupNode *());
    FRIEND_TEST(ParserClassTests, Block);
public:
    MockForBlockTestParserClass(ScannerClass *scanner, SymbolTableClass *symbolTable):
        ParserClass(scanner, symbolTable) {}
};


TEST_F(ParserClassTests, Block) {
    MockScannerClass scanner;
    MockSymbolTableClass symbolTable;
    MockForBlockTestParserClass parser(&scanner, &symbolTable);

    ON_CALL(parser, StatementGroup()).WillByDefault(Return(new StatementGroupNode()));
    ON_CALL(parser, Match(_)).WillByDefault(Return(TokenClass(BAD_TOKEN, "")));
    EXPECT_CALL(parser, Match(LCURLY_TOKEN)).Times(1);
    EXPECT_CALL(parser, StatementGroup()).Times(1);
    EXPECT_CALL(parser, Match(RCURLY_TOKEN)).Times(1);
    auto blockNode = parser.Block();
    EXPECT_NE(blockNode, nullptr);
}

// MARK: StatementGroup

class MockForStatementGroupTestParserClass: public ParserClass {
    MOCK_METHOD0(Statement, StatementNode *());
    FRIEND_TEST(ParserClassTests, StatementGroup);

public:
    MockForStatementGroupTestParserClass(ScannerClass *scanner, SymbolTableClass *symbolTable):
        ParserClass(scanner, symbolTable) {}
};

//TEST_F(ParserClassTests, StatementGroup) {
//    MockScannerClass scanner;
//    MockSymbolTableClass symbolTable;
//    MockForStatementGroupTestParserClass parser(&scanner, &symbolTable);
//
//    ON_CALL(parser, Statement()).WillByDefault(Return(new DeclarationStatementNode(nullptr)));
//    EXPECT_CALL(parser, Statement()).Times(1);
//    auto statementGroupNode = parser.StatementGroup();
//    EXPECT_NE(statementGroupNode, nullptr);
//}

// MARK: Statement

class MockStatementsParserClass: public ParserClass {
    MOCK_METHOD0(Block, BlockNode *());
    MOCK_METHOD0(IfStatement, IfStatementNode *());
    MOCK_METHOD0(WhileStatement, WhileStatementNode *());
    MOCK_METHOD0(DeclarationStatement, DeclarationStatementNode *());
    MOCK_METHOD0(AssignmentStatement, AssignmentStatementNode *());
    MOCK_METHOD0(CoutStatement, CoutStatementNode *());
    FRIEND_TEST(ParserClassTests, Statement_DeclarationStatement);
    FRIEND_TEST(ParserClassTests, Statement_IfStatement);
    FRIEND_TEST(ParserClassTests, Statement_WhileStatement);
    FRIEND_TEST(ParserClassTests, Statement_AssignmentStatement);
    FRIEND_TEST(ParserClassTests, Statement_CoutStatement);
    FRIEND_TEST(ParserClassTests, Statement_Block);
    FRIEND_TEST(ParserClassTests, Statement_Null);
public:
    MockStatementsParserClass(ScannerClass *scanner, SymbolTableClass *symbolTable):
        ParserClass(scanner, symbolTable) {}
};

TEST_F(ParserClassTests, Statement_DeclarationStatement) {
    MockScannerClass scanner;
    MockSymbolTableClass symbolTable;
    MockStatementsParserClass parser(&scanner, &symbolTable);

    ON_CALL(scanner, PeekNextToken()).WillByDefault(Return(TokenClass(INT_TOKEN, "int")));
    ON_CALL(parser, DeclarationStatement()).WillByDefault(Return(new DeclarationStatementNode(nullptr, nullptr)));
    EXPECT_CALL(scanner, PeekNextToken()).Times(1);
    EXPECT_CALL(parser, DeclarationStatement()).Times(1);
    auto statementNode = parser.Statement();
    EXPECT_NE(statementNode, nullptr);
}

TEST_F(ParserClassTests, Statement_IfStatement) {
    MockScannerClass scanner;
    MockSymbolTableClass symbolTable;
    MockStatementsParserClass parser(&scanner, &symbolTable);

    ON_CALL(scanner, PeekNextToken()).WillByDefault(Return(TokenClass(IF_TOKEN, "if")));
    ON_CALL(parser, IfStatement()).WillByDefault(Return(new IfStatementNode(nullptr, nullptr, nullptr)));
    EXPECT_CALL(scanner, PeekNextToken()).Times(1);
    EXPECT_CALL(parser, IfStatement()).Times(1);
    auto statementNode = parser.Statement();
    EXPECT_NE(statementNode, nullptr);
}

TEST_F(ParserClassTests, Statement_WhileStatement) {
    MockScannerClass scanner;
    MockSymbolTableClass symbolTable;
    MockStatementsParserClass parser(&scanner, &symbolTable);

    ON_CALL(scanner, PeekNextToken()).WillByDefault(Return(TokenClass(WHILE_TOKEN, "while")));
    ON_CALL(parser, WhileStatement()).WillByDefault(Return(new WhileStatementNode(nullptr, nullptr)));
    EXPECT_CALL(scanner, PeekNextToken()).Times(1);
    EXPECT_CALL(parser, WhileStatement()).Times(1);
    auto statementNode = parser.Statement();
    EXPECT_NE(statementNode, nullptr);
}


TEST_F(ParserClassTests, Statement_AssignmentStatement) {
    MockScannerClass scanner;
    MockSymbolTableClass symbolTable;
    MockStatementsParserClass parser(&scanner, &symbolTable);

    ON_CALL(scanner, PeekNextToken()).WillByDefault(Return(TokenClass(IDENTIFIER_TOKEN, "num")));
    ON_CALL(parser, AssignmentStatement()).WillByDefault(Return(new AssignmentStatementNode(nullptr, nullptr)));
    EXPECT_CALL(scanner, PeekNextToken()).Times(1);
    EXPECT_CALL(parser, AssignmentStatement()).Times(1);
    auto statementNode = parser.Statement();
    EXPECT_NE(statementNode, nullptr);
}

TEST_F(ParserClassTests, Statement_CoutStatement) {
    MockScannerClass scanner;
    MockSymbolTableClass symbolTable;
    MockStatementsParserClass parser(&scanner, &symbolTable);

    ON_CALL(scanner, PeekNextToken()).WillByDefault(Return(TokenClass(COUT_TOKEN, "cout")));
    ON_CALL(parser, CoutStatement()).WillByDefault(Return(new CoutStatementNode()));
    EXPECT_CALL(scanner, PeekNextToken()).Times(1);
    EXPECT_CALL(parser, CoutStatement()).Times(1);
    auto statementNode = parser.Statement();
    EXPECT_NE(statementNode, nullptr);
}

TEST_F(ParserClassTests, Statement_Block) {
    MockScannerClass scanner;
    MockSymbolTableClass symbolTable;
    MockStatementsParserClass parser(&scanner, &symbolTable);

    ON_CALL(scanner, PeekNextToken()).WillByDefault(Return(TokenClass(LCURLY_TOKEN, "{")));
    ON_CALL(parser, Block()).WillByDefault(Return(new BlockNode(nullptr, nullptr)));
    EXPECT_CALL(scanner, PeekNextToken()).Times(1);
    EXPECT_CALL(parser, Block()).Times(1);
    auto statementNode = parser.Statement();
    EXPECT_NE(statementNode, nullptr);
}

TEST_F(ParserClassTests, Statement_Null) {
    MockScannerClass scanner;
    MockSymbolTableClass symbolTable;
    MockStatementsParserClass parser(&scanner, &symbolTable);

    ON_CALL(scanner, PeekNextToken()).WillByDefault(Return(TokenClass(VOID_TOKEN, "void")));
    EXPECT_CALL(scanner, PeekNextToken()).Times(1);
    auto statementNode = parser.Statement();
    EXPECT_EQ(statementNode, nullptr);
}


// MARK: - StatementTests

class MockForStatementTestsParserClass: public ParserClass {
    MOCK_METHOD1(Match, TokenClass(TokenType expectedType));
    MOCK_METHOD0(Statement, StatementNode *());
    MOCK_METHOD0(Expression, ExpressionNode *());
    MOCK_METHOD0(Identifier, IdentifierNode *());
    FRIEND_TEST(ParserClassTests, IfStatement);
    FRIEND_TEST(ParserClassTests, WhileStatement);
    FRIEND_TEST(ParserClassTests, DeclarationStatement);
    FRIEND_TEST(ParserClassTests, AssignmentStatement);
    FRIEND_TEST(ParserClassTests, CoutStatement);

public:
    MockForStatementTestsParserClass(ScannerClass *scanner, SymbolTableClass *symbolTable):
    ParserClass(scanner, symbolTable) {}
};

// MARK: IfStatement

TEST_F(ParserClassTests, IfStatement) {

}

// MARK: WhileStatement

TEST_F(ParserClassTests, WhileStatement) {

}

// MARK: DeclarationStatement

TEST_F(ParserClassTests, DeclarationStatement) {

}

// MARK: AssignmentStatement

TEST_F(ParserClassTests, AssignmentStatement) {

}

// MARK: CoutStatement

TEST_F(ParserClassTests, CoutStatement) {

}

// MARK: Expression

TEST_F(ParserClassTests, Expression) {

}

// MARK: Or

TEST_F(ParserClassTests, Or) {

}

// MARK: And

TEST_F(ParserClassTests, And) {

}

// MARK: Relationals

TEST_F(ParserClassTests, Relationals) {

}

// MARK: PlusMinus

TEST_F(ParserClassTests, PlusMinus) {

}

// MARK: TimesDivide

TEST_F(ParserClassTests, TimesDivide) {

}

// MARK: Unaries

TEST_F(ParserClassTests, Unaries) {

}

// MARK: Factor

TEST_F(ParserClassTests, Factor) {

}

// MARK: Identifier

TEST_F(ParserClassTests, Identifier) {

}

// MARK: Integer

TEST_F(ParserClassTests, Integer) {

}
