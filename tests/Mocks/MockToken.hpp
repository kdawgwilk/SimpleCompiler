//
//  MockToken.hpp
//  SimpleCompiler
//
//  Created by Kaden Wilkinson on 3/22/17.
//  Copyright © 2017 Kaden Wilkinson. All rights reserved.
//

#ifndef MockToken_hpp
#define MockToken_hpp

#include "Token.hpp"

class MockTokenClass: public TokenClass {
public:
    MockTokenClass(): TokenClass() {}
    MockTokenClass(TokenType type, const string & lexeme): TokenClass(type, lexeme) {}

    MOCK_CONST_METHOD0(GetTokenType, TokenType());
    MOCK_CONST_METHOD0(GetTokenTypeName, string());
    MOCK_CONST_METHOD0(GetLexeme, string());
    MOCK_METHOD0(CheckReserved, void());
};


#endif /* MockToken_hpp */
