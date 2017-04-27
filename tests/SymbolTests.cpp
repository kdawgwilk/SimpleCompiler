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

TEST_F(SymbolTableClassTests, Exists_True) {
    EXPECT_EQ(symbolTable.Exists("Kaden"), true);
}

TEST_F(SymbolTableClassTests, Exists_False) {
    EXPECT_EQ(symbolTable.Exists("Blah"), false);
}

TEST_F(SymbolTableClassTests, Exists_InNestedScopes) {
    symbolTable.AddEntry("Blah");
    symbolTable.PushScope();
    EXPECT_EQ(symbolTable.Exists("Blah"), true);
    symbolTable.PopScope();
    EXPECT_EQ(symbolTable.Exists("Blah"), true);
}

TEST_F(SymbolTableClassTests, Exists_OnlyInNewScope) {
    EXPECT_EQ(symbolTable.Exists("Blah"), false);
    symbolTable.PushScope();
    symbolTable.AddEntry("Blah");
    EXPECT_EQ(symbolTable.Exists("Blah"), true);
    symbolTable.PopScope();
    EXPECT_EQ(symbolTable.Exists("Blah"), false);
}

TEST_F(SymbolTableClassTests, ExistsInCurrentScope_EntryAddedInNewScope) {
    EXPECT_EQ(symbolTable.ExistsInCurrentScope("Blah"), false);
    symbolTable.PushScope();
    symbolTable.AddEntry("Blah");
    EXPECT_EQ(symbolTable.GetCount(), 2);
    EXPECT_EQ(symbolTable.ExistsInCurrentScope("Blah"), true);
    symbolTable.PopScope();
    EXPECT_EQ(symbolTable.ExistsInCurrentScope("Blah"), false);
}

TEST_F(SymbolTableClassTests, ExistsInCurrentScope_EntryInOuterScope) {
    EXPECT_EQ(symbolTable.ExistsInCurrentScope("Kaden"), true);
    symbolTable.PushScope();
    EXPECT_EQ(symbolTable.ExistsInCurrentScope("Kaden"), false);
    symbolTable.PopScope();
    EXPECT_EQ(symbolTable.ExistsInCurrentScope("Kaden"), true);
}

TEST_F(SymbolTableClassTests, AddEntry_Success) {
    symbolTable.AddEntry("NewEntry");
    EXPECT_EQ(symbolTable.GetCount(), 2);
}

TEST_F(SymbolTableClassTests, AddEntry_DuplicateInCurrentScope_ShouldThrow) {
    EXPECT_THROW(symbolTable.AddEntry("Kaden"), std::invalid_argument);
    EXPECT_EQ(symbolTable.GetCount(), 1);
}

TEST_F(SymbolTableClassTests, AddEntry_NewEntryInNewScope_ShouldSucceed) {
    symbolTable.PushScope();
    symbolTable.AddEntry("NewEntry");
    EXPECT_EQ(symbolTable.GetCount(), 2);
    symbolTable.PopScope();
    EXPECT_EQ(symbolTable.GetCount(), 1);
}

TEST_F(SymbolTableClassTests, AddEntry_DuplicateInOuterScope_ShouldSucceed) {
    symbolTable.SetValue("Kaden", 0);
    symbolTable.PushScope();
    symbolTable.AddEntry("Kaden");
    symbolTable.SetValue("Kaden", 24);
    EXPECT_EQ(symbolTable.GetValue("Kaden"), 24);
    symbolTable.PopScope();
    EXPECT_EQ(symbolTable.GetValue("Kaden"), 0);
}

TEST_F(SymbolTableClassTests, SetValue_Success) {
    string entryLabel = "Kaden";
    symbolTable.SetValue(entryLabel, 3);
    EXPECT_EQ(symbolTable.GetCount(), 1);
    EXPECT_EQ(symbolTable.GetValue(entryLabel), 3);
}

TEST_F(SymbolTableClassTests, SetValue_Fail) {
    EXPECT_THROW(symbolTable.SetValue("Blah", 3), std::invalid_argument);
    EXPECT_EQ(symbolTable.GetCount(), 1);
}

TEST_F(SymbolTableClassTests, GetValue_Success) {
    symbolTable.SetValue("Kaden", 24);
    EXPECT_EQ(symbolTable.GetValue("Kaden"), 24);
}


TEST_F(SymbolTableClassTests, GetValue_Fail) {
    EXPECT_THROW(symbolTable.GetValue("Blah"), std::invalid_argument);
}

TEST_F(SymbolTableClassTests, GetIndex_Success) {
    EXPECT_EQ(symbolTable.GetIndex("Kaden"), 0);
}

TEST_F(SymbolTableClassTests, GetIndex_Fail) {
    EXPECT_EQ(symbolTable.GetIndex("Blah"), -1);
}

TEST_F(SymbolTableClassTests, GetCount) {
    EXPECT_EQ(symbolTable.GetCount(), 1);
}

TEST_F(SymbolTableClassTests, PushScope) {
    symbolTable.PushScope();
    EXPECT_EQ(symbolTable.mScope.size(), 1);
}

TEST_F(SymbolTableClassTests, PopScope) {
    symbolTable.PushScope();
    EXPECT_EQ(symbolTable.mScope.size(), 1);
    symbolTable.PopScope();
    EXPECT_EQ(symbolTable.mScope.size(), 0);
}




