//
//  Token.hpp
//  SimpleCompiler
//
//  Created by Kaden Wilkinson on 1/11/17.
//  Copyright © 2017 Kaden Wilkinson. All rights reserved.
//

#ifndef Token_hpp
#define Token_hpp

#include "TokenTypes.hpp"


class TokenClass {
private:
    TokenType mType;
    string mLexeme;
public:
    TokenClass();
    TokenClass(TokenType type, const string & lexeme);
    virtual ~TokenClass();

    TokenType GetTokenType() const;
    string GetTokenTypeName() const;
    string GetLexeme() const;
    void CheckReserved();

    static string GetTypeString(TokenType type);

    friend ostream &operator<<(ostream &out, const TokenClass &tc);
};



#endif /* Token_hpp */
