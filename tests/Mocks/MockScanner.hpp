//
//  MockScanner.hpp
//  SimpleCompiler
//
//  Created by Kaden Wilkinson on 3/22/17.
//  Copyright © 2017 Kaden Wilkinson. All rights reserved.
//

#ifndef MockScanner_hpp
#define MockScanner_hpp

#include "Scanner.hpp"

class MockScannerClass: public ScannerClass {
public:
    MockScannerClass(string filename): ScannerClass(filename) {}

    MOCK_METHOD0(GetNextToken, TokenClass());
    MOCK_METHOD0(PeekNextToken, TokenClass());
    MOCK_METHOD0(GetLineNumber, int());
    MOCK_METHOD0(GetColumnNumber, int());
};

#endif /* MockScanner_hpp */
