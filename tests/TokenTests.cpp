//
//  testToken.cpp
//  SimpleCompiler
//
//  Created by Kaden Wilkinson on 2/8/17.
//  Copyright © 2017 Kaden Wilkinson. All rights reserved.
//

#include "Token.hpp"


TEST(TokenClassTests, output_stream_operator) {
    TokenType tokenType = VOID_TOKEN;
    string lexeme = "void";
    TokenClass voidToken(tokenType, lexeme);

    stringstream os;
    os << voidToken;

    EXPECT_EQ(os.str(), "Token Type:   0\nToken Name:   VOID\nToken Lexeme: `void`\n");
}

TEST(TokenClassTests, Init) {
    TokenClass token;
    EXPECT_EQ(token.GetLexeme(), "");
    EXPECT_EQ(token.GetTokenType(), BAD_TOKEN);
}

TEST(TokenClassTests, Init_WithTypeAndLexeme) {
    TokenClass token(VOID_TOKEN, "void");
    EXPECT_EQ(token.GetLexeme(), "void");
    EXPECT_EQ(token.GetTokenType(), VOID_TOKEN);
}

TEST(TokenClassTests, GetTokenType) {
    TokenClass token(VOID_TOKEN, "void");
    EXPECT_EQ(token.GetTokenType(), VOID_TOKEN);
}

TEST(TokenClassTests, GetTokenTypeName) {
    TokenClass token(VOID_TOKEN, "void");
    EXPECT_EQ(token.GetTokenTypeName(), "VOID");
}

TEST(TokenClassTests, GetLexeme) {
    TokenClass token(VOID_TOKEN, "void");
    EXPECT_EQ(token.GetLexeme(), "void");
}

TEST(TokenClassTests, CheckReserved_Void) {
    TokenClass token(IDENTIFIER_TOKEN, "void");
    token.CheckReserved();
    EXPECT_EQ(token.GetTokenType(), VOID_TOKEN);
}

TEST(TokenClassTests, CheckReserved_Main) {
    TokenClass token(IDENTIFIER_TOKEN, "main");
    token.CheckReserved();
    EXPECT_EQ(token.GetTokenType(), MAIN_TOKEN);
}

TEST(TokenClassTests, CheckReserved_Int) {
    TokenClass token(IDENTIFIER_TOKEN, "int");
    token.CheckReserved();
    EXPECT_EQ(token.GetTokenType(), INT_TOKEN);
}

TEST(TokenClassTests, CheckReserved_Cout) {
    TokenClass token(IDENTIFIER_TOKEN, "cout");
    token.CheckReserved();
    EXPECT_EQ(token.GetTokenType(), COUT_TOKEN);
}

TEST(TokenClassTests, CheckReserved_If) {
    TokenClass token(IDENTIFIER_TOKEN, "if");
    token.CheckReserved();
    EXPECT_EQ(token.GetTokenType(), IF_TOKEN);
}

TEST(TokenClassTests, CheckReserved_While) {
    TokenClass token(IDENTIFIER_TOKEN, "while");
    token.CheckReserved();
    EXPECT_EQ(token.GetTokenType(), WHILE_TOKEN);
}

// Is this shortcut okay?
TEST(TokenClassTests, CheckReserved_Begin) {
    TokenClass token(IDENTIFIER_TOKEN, "begin");
    token.CheckReserved();
    EXPECT_EQ(token.GetTokenType(), LCURLY_TOKEN);
}

TEST(TokenClassTests, CheckReserved_End) {
    TokenClass token(IDENTIFIER_TOKEN, "end");
    token.CheckReserved();
    EXPECT_EQ(token.GetTokenType(), RCURLY_TOKEN);
}


TEST(TokenClassTests, GetTypeString) {
    EXPECT_EQ(TokenClass::GetTypeString(VOID_TOKEN), "VOID");
}
