//
//  TokenTypes.h
//  SimpleCompiler
//
//  Created by Kaden Wilkinson on 2/22/17.
//  Copyright © 2017 Kaden Wilkinson. All rights reserved.
//

#ifndef TokenTypes_h
#define TokenTypes_h

#include <string>
using std::string;

enum TokenType {
    // Reserved Words:
    VOID_TOKEN,
    MAIN_TOKEN,
    INT_TOKEN,
    COUT_TOKEN,
    IF_TOKEN,
    WHILE_TOKEN,

    // Bool Operators:
    OR_TOKEN,
    AND_TOKEN,

    // Relational Operators:
    LESS_THAN_TOKEN,
    LESS_THAN_OR_EQUAL_TOKEN,
    GREATER_THAN_TOKEN,
    GREATER_THAN_OR_EQUAL_TOKEN,
    EQUAL_TOKEN,
    NOT_EQUAL_TOKEN,

    // Binary Operators:
    INSERTION_TOKEN,
    EXTRACTION_TOKEN,
    ASSIGNMENT_TOKEN,
    PLUS_TOKEN,
    PLUS_EQUAL_TOKEN,
    MINUS_TOKEN,
    MINUS_EQUAL_TOKEN,
    TIMES_TOKEN,
    TIMES_EQUAL_TOKEN,
    DIVIDE_TOKEN,
    DIVIDE_EQUAL_TOKEN,

    // Unary Operators:
    NOT_TOKEN,
    NEGATIVE_TOKEN,
    INCREMENT_TOKEN,
    DECREMENT_TOKEN,

    // Other Characters:
    SEMICOLON_TOKEN,
    LPAREN_TOKEN,
    RPAREN_TOKEN,
    LCURLY_TOKEN,
    RCURLY_TOKEN,
    LBRACKET_TOKEN,
    RBRACKET_TOKEN,

    // Other Token Types:
    IDENTIFIER_TOKEN,
    INTEGER_TOKEN,
    BAD_TOKEN,
    ENDFILE_TOKEN,
    LAST_TOKEN
};

const string gTokenTypeNames[LAST_TOKEN] = {
    // Reserved Words:
    "VOID",
    "MAIN",
    "INT",
    "COUT",
    "IF",
    "WHILE",

    // Bool Operators:
    "OR",
    "AND",

    // Relational Operators:
    "LESS_THAN",
    "LESS_THAN_OR_EQUAL",
    "GREATER_THAN",
    "GREATER_THAN_OR_EQUAL",
    "EQUAL",
    "NOT_EQUAL",

    // Binary Operators:
    "INSERTION",
    "EXTRACTION",
    "ASSIGNMENT",
    "PLUS",
    "PLUS_EQUAL",
    "MINUS",
    "MINUS_EQUAL",
    "TIMES",
    "TIMES_EQUAL",
    "DIVIDE",
    "DIVIDE_EQUAL",

    // Unary Operators:
    "NOT",
    "NEGATIVE",
    "INCREMENT",
    "DECREMENT",

    // Other Characters:
    "SEMICOLON",
    "LPAREN",
    "RPAREN",
    "LCURLY",
    "RCURLY",
    "LBRACKET",
    "RBRACKET",

    // Other Token Types:
    "IDENTIFIER",
    "INTEGER",
    "BAD",
    "ENDFILE"
};


#endif /* TokenTypes_h */
