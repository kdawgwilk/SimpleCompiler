//
//  Symbol.cpp
//  SimpleCompiler
//
//  Created by Kaden Wilkinson on 2/22/17.
//  Copyright © 2017 Kaden Wilkinson. All rights reserved.
//

#include "Symbol.hpp"

SymbolTableClass::SymbolTableClass() {}

SymbolTableClass::~SymbolTableClass() {}

// returns true if <s> is already in the symbol table.
bool SymbolTableClass::Exists(string s) {
    for (size_t i = 0; i < mVariables.size(); i++) {
        if (mVariables[i].mLabel == s) {
            return true;
        }
    }
    return false;
}

// adds <s> to the symbol table,
// or quits if it was already there
void SymbolTableClass::AddEntry(string s) {
    if (Exists(s)) {
        cerr << "Entry already exists in the SymbolTable: " << s << endl;
        exit(1);
    }
    Variable var;
    var.mLabel = s;
    mVariables.push_back(var);
}

// returns the current value of variable <s>, when
// interpreting. Meaningless for Coding and Executing.
// Prints a message and quits if variable s does not exist.
int SymbolTableClass::GetValue(string s) {
    for (size_t i = 0; i < mVariables.size(); i++) {
        if (mVariables[i].mLabel == s) {
            int value = mVariables[i].mValue;
            return value;
        }
    }
    cerr << "Entry doesn't exist in the SymbolTable: " << s << endl;
    exit(1);
}

// sets variable <s> to the given value, when interpreting.
// Meaningless for Coding and Executing.
// Prints a message and quits if variable s does not exist.
void SymbolTableClass::SetValue(string s, int v) {
    for (size_t i = 0; i < mVariables.size(); i++) {
        if (mVariables[i].mLabel == s) {
            mVariables[i].mValue = v;
            return;
        }
    }
    cerr << "Entry doesn't exist in the SymbolTable: " << s << endl;
    exit(1);
}

// returns the index of where variable <s> is. // returns -1 if variable <s> is not there.
int SymbolTableClass::GetIndex(string s) {
    for (size_t i = 0; i < mVariables.size(); i++) {
        if (mVariables[i].mLabel == s) {
            return int(i);
        }
    }
    return -1;
}

// returns the current number of variables in the symbol // table.
int SymbolTableClass::GetCount() {
    return int(mVariables.size());
}

// TODO: Push the mVariables length to mScope list
void SymbolTableClass::PushScope() {

}

// TODO: Pop the top mVariables length from mScope and delelete variables
void SymbolTableClass::PopScope() {

}
