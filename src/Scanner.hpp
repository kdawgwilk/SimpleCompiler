//
//  Scanner.hpp
//  SimpleCompiler
//
//  Created by Kaden Wilkinson on 1/30/17.
//  Copyright © 2017 Kaden Wilkinson. All rights reserved.
//

#ifndef Scanner_hpp
#define Scanner_hpp

#include "Token.hpp"


class ScannerClass {
    string mFilename;
    ifstream mFin;
    int mLineNumber;
    int mColumnNumber;

public:
    ScannerClass(string filename);
    virtual ~ScannerClass();

    virtual TokenClass GetNextToken();
    virtual TokenClass PeekNextToken();

    int GetLineNumber();
    int GetColumnNumber();
};


#endif /* Scanner_hpp */
