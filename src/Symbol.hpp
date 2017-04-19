//
//  Symbol.hpp
//  SimpleCompiler
//
//  Created by Kaden Wilkinson on 2/22/17.
//  Copyright © 2017 Kaden Wilkinson. All rights reserved.
//

#ifndef Symbol_hpp
#define Symbol_hpp

class SymbolTableClass {

    struct Variable {
        string mLabel;
        int mValue;
    };

    vector<Variable> mVariables;
    vector<int> mScope;

public:
    SymbolTableClass();
    virtual ~SymbolTableClass();

    // returns true if <s> is already in the symbol table.
    bool Exists(string s);

    // adds <s> to the symbol table,
    // or quits if it was already there
    void AddEntry(string s);

    // returns the current value of variable <s>, when
    // interpreting. Meaningless for Coding and Executing.
    // Prints a message and quits if variable s does not exist.
    int GetValue(string s);

    // sets variable <s> to the given value, when interpreting.
    // Meaningless for Coding and Executing.
    // Prints a message and quits if variable s does not exist.
    void SetValue(string s, int v);

    // returns the index of where variable <s> is. // returns -1 if variable <s> is not there.
    int GetIndex(string s);

    // returns the current number of variables in the symbol // table.
    int GetCount();

    void PushScope();
    void PopScope();
};

#endif /* Symbol_hpp */
