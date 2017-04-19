//
//  SymbolTests.cpp
//  SimpleCompiler
//
//  Created by Kaden Wilkinson on 2/22/17.
//  Copyright © 2017 Kaden Wilkinson. All rights reserved.
//

#include "Symbol.hpp"

class SymbolTableClassTests : public Test {
protected:
    SymbolTableClass symbolTable;


    static void SetUpTestCase() {

    }

    static void TearDownTestCase() {

    }

    virtual void SetUp() {
        symbolTable.AddEntry("Kaden");

        EXPECT_EQ(symbolTable.GetCount(), 1);
    }

    virtual void TearDown() {

    }
};

TEST_F(SymbolTableClassTests, Exists) {
    EXPECT_EQ(symbolTable.Exists("Kaden"), true);
    EXPECT_EQ(symbolTable.Exists("Blah"), false);
}

TEST_F(SymbolTableClassTests, AddEntry) {
    SymbolTableClass symbolTable;

    symbolTable.AddEntry("Kaden");

    EXPECT_EXIT(symbolTable.AddEntry("Kaden");, ExitedWithCode(1), "Entry already exists in the SymbolTable: Kaden");
    EXPECT_EQ(symbolTable.GetCount(), 1);
}

TEST_F(SymbolTableClassTests, SetValue) {
    symbolTable.SetValue("Kaden", 24);

    EXPECT_EXIT(symbolTable.SetValue("Blah", 3), ExitedWithCode(1), "Entry doesn't exist in the SymbolTable: Blah");
}

TEST_F(SymbolTableClassTests, GetValue) {
    symbolTable.SetValue("Kaden", 24);

    EXPECT_EQ(symbolTable.GetValue("Kaden"), 24);
    EXPECT_EXIT(symbolTable.GetValue("Blah"), ExitedWithCode(1), "Entry doesn't exist in the SymbolTable: Blah");
}

TEST_F(SymbolTableClassTests, GetIndex) {
    EXPECT_EQ(symbolTable.GetIndex("Kaden"), 0);
    EXPECT_EQ(symbolTable.GetIndex("Blah"), -1);
}

TEST_F(SymbolTableClassTests, GetCount) {
    EXPECT_EQ(symbolTable.GetCount(), 1);
}




