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


    static void SetUpTestCase() {

    }

    static void TearDownTestCase() {

    }

    virtual void SetUp() {

    }

    virtual void TearDown() {
        
    }
};

TEST(ScannerClassTests, Init_WithExistingFile) {
    ScannerClass scanner("test_code_1.c");
}

TEST(ScannerClassTests, Init_WithNonExistentFile) {
    EXPECT_EXIT(ScannerClass scanner("blah.c"), ExitedWithCode(1), "File 'blah.c' could not be opened.  Does it exist?");
}

TEST(ScannerClassTests, Destructor) {

}

TEST(ScannerClassTests, GetNextToken_WithoutComments) {
    ScannerClass scanner("test_code_1.c");
    TokenClass token;

    do {
        token = scanner.GetNextToken();
//        MSG(token)
    } while (token.GetTokenType() != ENDFILE_TOKEN);

    EXPECT_EQ(0, 0);
}

TEST(ScannerClassTests, GetNextToken_WithComments) {
    ScannerClass scanner("test_code_2.c");
    TokenClass token;

    do {
        token = scanner.GetNextToken();
//        MSG(token)
    } while (token.GetTokenType() != ENDFILE_TOKEN);

    EXPECT_EQ(0, 0);
}

TEST(ScannerClassTests, PeekNextToken) {

}

TEST(ScannerClassTests, GetLineNumber) {

}

TEST(ScannerClassTests, GetColumnNumber) {

}

