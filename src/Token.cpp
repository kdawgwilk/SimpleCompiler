//
//  Token.cpp
//  SimpleCompiler
//
//  Created by Kaden Wilkinson on 1/11/17.
//  Copyright © 2017 Kaden Wilkinson. All rights reserved.
//

#include "Token.hpp"


TokenClass::TokenClass(): mType(BAD_TOKEN), mLexeme("") {}

TokenClass::TokenClass(TokenType type, const string &lexeme): mType(type), mLexeme(lexeme) {}

TokenClass::~TokenClass() {}

TokenType TokenClass::GetTokenType() const {
    return mType;
}

string TokenClass::GetTokenTypeName() const {
    return gTokenTypeNames[mType];
}

string TokenClass::GetLexeme() const {
    return mLexeme;
}

void TokenClass::CheckReserved() {
    if (mType == IDENTIFIER_TOKEN) {
        if (mLexeme == "void") {
            mType = VOID_TOKEN;
        } else if (mLexeme == "main") {
            mType = MAIN_TOKEN;
        } else if (mLexeme == "int") {
            mType = INT_TOKEN;
        } else if (mLexeme == "cout") {
            mType = COUT_TOKEN;
        } else if (mLexeme == "endl") {
            mType = ENDL_TOKEN;
        } else if (mLexeme == "if") {
            mType = IF_TOKEN;
        } else if (mLexeme == "else") {
            mType = ELSE_TOKEN;
        } else if (mLexeme == "while") {
            mType = WHILE_TOKEN;
        } else if (mLexeme == "do") {
            mType = DO_TOKEN;
        } else if (mLexeme == "repeat") {
            mType = REPEAT_TOKEN;
        } else if (mLexeme == "begin") {
            mType = LCURLY_TOKEN;
        } else if (mLexeme == "end") {
            mType = RCURLY_TOKEN;
        }
    }
}

string TokenClass::GetTypeString(TokenType type) {
    return gTokenTypeNames[type];
}

ostream &operator<<(ostream &out, const TokenClass &tc) {
    out << "Token Type:   "  << tc.GetTokenType()        << endl;
    out << "Token Name:   "  << tc.GetTokenTypeName()    << endl;
    out << "Token Lexeme: `" << tc.GetLexeme() << "`"    << endl;
    return out;
}

