//
//  TokenTypes.h
//  SimpleCompiler
//
//  Created by Kaden Wilkinson on 2/22/17.
//  Copyright © 2017 Kaden Wilkinson. All rights reserved.
//

#ifndef TokenTypes_h
#define TokenTypes_h

enum TokenType {
    AND_TOKEN,
    ASSIGNMENT_TOKEN,
    BAD_TOKEN,
    COUT_TOKEN,
    DECREMENT_TOKEN,
    DIVIDE_EQUAL_TOKEN,
    DIVIDE_TOKEN,
    DO_TOKEN,
    ENDFILE_TOKEN,
    ENDL_TOKEN,
    ELSE_TOKEN,
    EQUAL_TOKEN,
    EXTRACTION_TOKEN,
    GREATER_THAN_OR_EQUAL_TOKEN,
    GREATER_THAN_TOKEN,
    IDENTIFIER_TOKEN,
    IF_TOKEN,
    INCREMENT_TOKEN,
    INSERTION_TOKEN,
    INTEGER_TOKEN,
    INT_TOKEN,
    LBRACKET_TOKEN,
    LCURLY_TOKEN,
    LESS_THAN_OR_EQUAL_TOKEN,
    LESS_THAN_TOKEN,
    LPAREN_TOKEN,
    MAIN_TOKEN,
    MINUS_EQUAL_TOKEN,
    MINUS_TOKEN,
    MODULO_TOKEN,
    NEGATIVE_TOKEN,
    NOT_EQUAL_TOKEN,
    NOT_TOKEN,
    OR_TOKEN,
    PLUS_EQUAL_TOKEN,
    PLUS_TOKEN,
    RBRACKET_TOKEN,
    RCURLY_TOKEN,
    REPEAT_TOKEN,
    RPAREN_TOKEN,
    SEMICOLON_TOKEN,
    TIMES_EQUAL_TOKEN,
    TIMES_TOKEN,
    VOID_TOKEN,
    WHILE_TOKEN,

    LAST_TOKEN
};

const string gTokenTypeNames[LAST_TOKEN] = {
    "AND",
    "ASSIGNMENT",
    "BAD",
    "COUT",
    "DECREMENT",
    "DIVIDE",
    "DIVIDE_EQUAL",
    "DO",
    "ENDFILE",
    "ENDL",
    "ELSE",
    "EQUAL",
    "EXTRACTION",
    "GREATER_THAN",
    "GREATER_THAN_OR_EQUAL",
    "IDENTIFIER",
    "IF",
    "INCREMENT",
    "INSERTION",
    "INT",
    "INTEGER",
    "LBRACKET",
    "LCURLY",
    "LESS_THAN",
    "LESS_THAN_OR_EQUAL",
    "LPAREN",
    "MAIN",
    "MINUS",
    "MINUS_EQUAL",
    "MOLULO",
    "NEGATIVE",
    "NOT",
    "NOT_EQUAL",
    "OR",
    "PLUS",
    "PLUS_EQUAL",
    "RBRACKET",
    "RCURLY",
    "REPEAT",
    "RPAREN",
    "SEMICOLON",
    "TIMES",
    "TIMES_EQUAL",
    "VOID",
    "WHILE"
};


#endif /* TokenTypes_h */
