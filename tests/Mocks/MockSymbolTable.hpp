//
//  MockSymbolTable.hpp
//  SimpleCompiler
//
//  Created by Kaden Wilkinson on 3/22/17.
//  Copyright © 2017 Kaden Wilkinson. All rights reserved.
//

#ifndef MockSymbolTable_hpp
#define MockSymbolTable_hpp

#include "Symbol.hpp"

class MockSymbolTableClass: public SymbolTableClass {
public:
    MOCK_METHOD1(Exists, bool(string s));
    MOCK_METHOD1(AddEntry, void(string s));
    MOCK_METHOD1(GetValue, int(string s));
    MOCK_METHOD2(SetValue, void(string s, int v));
    MOCK_METHOD1(GetIndex, int(string s));
    MOCK_METHOD0(GetCount, int());
};

#endif /* MockSymbolTable_hpp */
