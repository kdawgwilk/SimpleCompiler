//
//  testScanner.cpp
//  SimpleCompiler
//
//  Created by Kaden Wilkinson on 2/8/17.
//  Copyright © 2017 Kaden Wilkinson. All rights reserved.
//

#include "Scanner.hpp"

class ScannerClassTests : public Test {
protected:
//    ScannerClass scanner;
//    auto fileStreamer;


    static void SetUpTestCase() {

    }

    static void TearDownTestCase() {

    }

    virtual void SetUp() {
//        auto stringStream = new std::istringstream("");
//        fileStreamer = new FileStringStreamer(stringStream);
    }

    virtual void TearDown() {
//        delete fileStreamer;
    }
};

TEST_F(ScannerClassTests, Init_WithExistingFile) {
//    ScannerClass scanner("test_code_1.c");
}

TEST_F(ScannerClassTests, Init_WithNonExistentFile) {
    EXPECT_DEATH(ScannerClass scanner("blah.c"), "File 'blah.c' could not be opened.  Does it exist?");
}

TEST_F(ScannerClassTests, Destructor) {

}

TEST_F(ScannerClassTests, GetNextToken_SingleLineComments) {
    string testString =
"// Comment */\n \
\n               \
void\n";

    auto stringStream = new std::istringstream(testString);
    auto fileStreamer = new FileStringStreamer(stringStream);
    ScannerClass scanner("", fileStreamer);

    auto token = scanner.GetNextToken();

    EXPECT_EQ(token.GetTokenType(), VOID_TOKEN);
}

TEST_F(ScannerClassTests, GetNextToken_MultiLineComments) {
    string testString =
"/*\n           \
  Comment\n     \
  blah * main\n \
*/\n            \
void\n";

    auto stringStream = new std::istringstream(testString);
    auto fileStreamer = new FileStringStreamer(stringStream);
    ScannerClass scanner("", fileStreamer);

    auto token = scanner.GetNextToken();

    EXPECT_EQ(token.GetTokenType(), VOID_TOKEN);
}

TEST_F(ScannerClassTests, GetNextToken_Void) {
    auto stringStream = new std::istringstream("void");
    auto fileStreamer = new FileStringStreamer(stringStream);
    ScannerClass scanner("", fileStreamer);

    auto token = scanner.GetNextToken();

    EXPECT_EQ(token.GetTokenType(), VOID_TOKEN);
}

TEST_F(ScannerClassTests, GetNextToken_Integer) {
    auto stringStream = new std::istringstream("512");
    auto fileStreamer = new FileStringStreamer(stringStream);
    ScannerClass scanner("", fileStreamer);

    auto token = scanner.GetNextToken();

    EXPECT_EQ(token.GetTokenType(), INTEGER_TOKEN);
}

TEST_F(ScannerClassTests, GetNextToken_Identifier) {
    auto stringStream = new std::istringstream("myVariable");
    auto fileStreamer = new FileStringStreamer(stringStream);
    ScannerClass scanner("", fileStreamer);

    auto token = scanner.GetNextToken();

    EXPECT_EQ(token.GetTokenType(), IDENTIFIER_TOKEN);
}

TEST_F(ScannerClassTests, GetNextToken_RelationalOperator) {
    auto stringStream = new std::istringstream(">=");
    auto fileStreamer = new FileStringStreamer(stringStream);
    ScannerClass scanner("", fileStreamer);

    auto token = scanner.GetNextToken();

    EXPECT_EQ(token.GetTokenType(), GREATER_THAN_OR_EQUAL_TOKEN);
}

TEST_F(ScannerClassTests, GetNextToken_BinaryOperator) {
    auto stringStream = new std::istringstream("+=");
    auto fileStreamer = new FileStringStreamer(stringStream);
    ScannerClass scanner("", fileStreamer);

    auto token = scanner.GetNextToken();

    EXPECT_EQ(token.GetTokenType(), PLUS_EQUAL_TOKEN);
}

TEST_F(ScannerClassTests, GetNextToken_BooleanOperator) {
    auto stringStream = new std::istringstream("&&");
    auto fileStreamer = new FileStringStreamer(stringStream);
    ScannerClass scanner("", fileStreamer);

    auto token = scanner.GetNextToken();

    EXPECT_EQ(token.GetTokenType(), AND_TOKEN);
}

TEST_F(ScannerClassTests, GetNextToken_LineCount) {
    string testString =
"/*\n           \
  Comment\n     \
  blah * main\n \
*/\n            \
void\n          \
main() {\n      \
}";
    auto stringStream = new std::istringstream(testString);
    auto fileStreamer = new FileStringStreamer(stringStream);
    ScannerClass scanner("", fileStreamer);

    scanner.GetNextToken();
    EXPECT_EQ(scanner.GetLineNumber(), 5);
    scanner.GetNextToken();
    EXPECT_EQ(scanner.GetLineNumber(), 6);
}

TEST_F(ScannerClassTests, GetNextToken_ColumnCount) {
    auto stringStream = new std::istringstream("void main");
    auto fileStreamer = new FileStringStreamer(stringStream);
    ScannerClass scanner("", fileStreamer);

    scanner.GetNextToken();
    EXPECT_EQ(scanner.GetColumnNumber(), 4);
    scanner.GetNextToken();
    EXPECT_EQ(scanner.GetColumnNumber(), 9);
}

TEST_F(ScannerClassTests, GetNextToken_ColumnCount_MultiLine) {
    auto stringStream = new std::istringstream("\n\nvoid main");
    auto fileStreamer = new FileStringStreamer(stringStream);
    ScannerClass scanner("", fileStreamer);

    scanner.GetNextToken();
    EXPECT_EQ(scanner.GetColumnNumber(), 4);
    scanner.GetNextToken();
    EXPECT_EQ(scanner.GetColumnNumber(), 9);
}

TEST_F(ScannerClassTests, GetNextToken_BadToken) {
    string filename = "";
    auto stringStream = new std::istringstream("void @");
    auto fileStreamer = new FileStringStreamer(stringStream);
    ScannerClass scanner(filename, fileStreamer);

    scanner.GetNextToken();
    EXPECT_DEATH(scanner.GetNextToken(), "Error: : \\\[1,6] Unrecognized token: '@'");
}

TEST_F(ScannerClassTests, PeekNextToken) {
    auto stringStream = new std::istringstream("void");
    auto fileStreamer = new FileStringStreamer(stringStream);
    ScannerClass scanner("", fileStreamer);

    auto token = scanner.PeekNextToken();
    EXPECT_EQ(token.GetTokenType(), VOID_TOKEN);

//    token = scanner.GetNextToken();
//    EXPECT_EQ(token.GetTokenType(), VOID_TOKEN);
}

