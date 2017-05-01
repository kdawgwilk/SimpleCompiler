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
bool SymbolTableClass::Exists(string label) {
    for (auto i = GetCount() - 1; i >= 0; i--) {
        if (mVariables[i].mLabel == label) {
            return true;
        }
    }
    return false;
}

bool SymbolTableClass::ExistsInCurrentScope(string label) {
    if (mScope.size() > 0) {
        int currentVariableCount = GetCount() - 1;
        int lastScopeVariableCount = mScope[mScope.size() - 1];
        for (auto i = currentVariableCount; i >= lastScopeVariableCount; i--) {
            if (mVariables[i].mLabel == label) {
                return true;
            }
        }
        return false;
    }
    return Exists(label);
}

// adds <s> to the symbol table,
// or quits if it was already there
void SymbolTableClass::AddEntry(string label) {
    if (ExistsInCurrentScope(label)) {
        throw std::invalid_argument("Entry already exists in the SymbolTable");
    }
    Variable var;
    var.mLabel = label;
    mVariables.push_back(var);
}

// returns the current value of variable <s>, when
// interpreting. Meaningless for Coding and Executing.
// Prints a message and quits if variable s does not exist.
int SymbolTableClass::GetValue(string label) {
    for (auto i = GetCount() - 1; i >= 0; i--) {
        if (mVariables[i].mLabel == label) {
            int value = mVariables[i].mValue;
            return value;
        }
    }
    throw std::invalid_argument("Entry doesn't exist in the SymbolTable");
}

// sets variable <s> to the given value, when interpreting.
// Meaningless for Coding and Executing.
// Prints a message and quits if variable s does not exist.
void SymbolTableClass::SetValue(string label, int value) {
    for (auto i = GetCount() - 1; i >= 0; i--) {
        if (mVariables[i].mLabel == label) {
            mVariables[i].mValue = value;
            return;
        }
    }
    throw std::invalid_argument("Entry doesn't exist in the SymbolTable");
}

// returns the index of where variable <s> is. // returns -1 if variable <s> is not there.
int SymbolTableClass::GetIndex(string label) {
    for (int i = GetCount() - 1; i >= 0; i--) {
        if (mVariables[i].mLabel == label) {
            return i;
        }
    }
    return -1;
}

// returns the current number of variables in the symbol // table.
int SymbolTableClass::GetCount() {
    return int(mVariables.size());
}

void SymbolTableClass::PushScope() {
    mScope.push_back((int)mVariables.size());
}

void SymbolTableClass::PopScope() {
    int currentVariableCount = GetCount();
    int lastScopeVariableCount = mScope[mScope.size() - 1];
    mScope.pop_back();
    for (auto i = currentVariableCount; i > lastScopeVariableCount; i--) {
        mVariables.pop_back();
    }
}
