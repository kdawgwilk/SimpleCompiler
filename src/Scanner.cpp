//
//  Scanner.cpp
//  SimpleCompiler
//
//  Created by Kaden Wilkinson on 1/30/17.
//  Copyright © 2017 Kaden Wilkinson. All rights reserved.
//

#include "Scanner.hpp"
#include "StateMachine.hpp"


ScannerClass::ScannerClass(string filename, InterfaceInputStreamer *inputFileStream)
: mFilename(filename)
, mFin(inputFileStream)
, mLineNumber(1)
, mColumnNumber(0) {
    mFin->open(mFilename);
    if (!mFin->is_open()) {
        cerr << "File '" << filename << "' could not be opened.  Does it exist?" << endl;
        exit(1);
    }
}

ScannerClass::~ScannerClass() {
    mFin->close();
}

TokenClass ScannerClass::GetNextToken() {
    StateMachineClass stateMachine;
    TokenType correspondingTokenType;
    string lexeme;

    do {
//        string line;
//        getline(mFin, line);
        const char c = mFin->get();
        mColumnNumber++;
        auto state = stateMachine.UpdateState(c, correspondingTokenType);

        if (state == START_STATE) {
            lexeme = "";
        }
        if (c == '\n') {
            mColumnNumber = 1;
        }
        
        if (state == CANT_MOVE_STATE) {
            if (correspondingTokenType == BAD_TOKEN) {
                lexeme.append(1, c);
                cerr << "Scanner Error: " << mFilename << ": [" << mLineNumber << "," << mColumnNumber << "] Unrecognized token: '" << lexeme << "'" << endl;
                exit(1);
            }
            mFin->unget();
            mColumnNumber--;
            TokenClass token(correspondingTokenType, lexeme);
            token.CheckReserved();
            return token;
        }
        if (c == '\n') {
//            MSG("Line Number: " << mLineNumber)
            mLineNumber++;
            mColumnNumber = 1;
        }
        if (state != START_STATE) {

            lexeme.append(1, c);
//            MSG("Lexeme: `" << lexeme << "`")
        }
    } while (mFin);

    TokenClass token(ENDFILE_TOKEN, "EOF");
    return token;
}

TokenClass ScannerClass::PeekNextToken() {
    int line = mLineNumber;
    auto position = mFin->tellg();
    auto nextToken = GetNextToken();
    if (!mFin) { // if we triggered EOF, then seekg doesn't work,
        mFin->clear();
    }
    mLineNumber = line;
    mFin->seekg(position);
    return nextToken;
}

string ScannerClass::GetFilename() {
    return mFilename;
}

int ScannerClass::GetLineNumber() {
    return mLineNumber;
}

int ScannerClass::GetColumnNumber() {
    return mColumnNumber;
}
