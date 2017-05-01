//
//  StateMachine.cpp
//  SimpleCompiler
//
//  Created by Kaden Wilkinson on 1/30/17.
//  Copyright © 2017 Kaden Wilkinson. All rights reserved.
//

#include "StateMachine.hpp"

StateMachineClass::StateMachineClass()
: mCurrentState(START_STATE)
{
    // Set  all mLegalMove states initially to CANTMOVE so we don't forget any
    for (int i = 0; i < LAST_STATE; i++) {
        for (int j = 0; j < LAST_CHAR; j ++) {
            mLegalMoves[i][j] = CANT_MOVE_STATE;
        }
    }

    // Set legal moves for each state
    // START_STATE
    mLegalMoves[START_STATE][AND_CHAR]                    = AND_STATE;
    mLegalMoves[START_STATE][DIGIT_CHAR]                  = INTEGER_STATE;
    mLegalMoves[START_STATE][ENDFILE_CHAR]                = ENDFILE_STATE;
    mLegalMoves[START_STATE][EQUAL_CHAR]                  = EQUAL_STATE;
    mLegalMoves[START_STATE][EXCLAMATION_CHAR]            = NOT_STATE;
    mLegalMoves[START_STATE][FSLASH_CHAR]                 = DIVIDE_STATE;
    mLegalMoves[START_STATE][GREATER_THAN_CHAR]           = GREATER_THAN_STATE;
    mLegalMoves[START_STATE][LBRACKET_CHAR]               = LBRACKET_STATE;
    mLegalMoves[START_STATE][LCURLY_CHAR]                 = LCURLY_STATE;
    mLegalMoves[START_STATE][LESS_THAN_CHAR]              = LESS_THAN_STATE;
    mLegalMoves[START_STATE][LETTER_CHAR]                 = IDENTIFIER_STATE;
    mLegalMoves[START_STATE][LPAREN_CHAR]                 = LPAREN_STATE;
    mLegalMoves[START_STATE][MINUS_CHAR]                  = MINUS_STATE;
    mLegalMoves[START_STATE][NEWLINE_CHAR]                = START_STATE;
    mLegalMoves[START_STATE][PERCENT_CHAR]                = MODULO_STATE;
    mLegalMoves[START_STATE][PLUS_CHAR]                   = PLUS_STATE;
    mLegalMoves[START_STATE][RBRACKET_CHAR]               = RBRACKET_STATE;
    mLegalMoves[START_STATE][RCURLY_CHAR]                 = RCURLY_STATE;
    mLegalMoves[START_STATE][RPAREN_CHAR]                 = RPAREN_STATE;
    mLegalMoves[START_STATE][SEMICOLON_CHAR]              = SEMICOLON_STATE;
    mLegalMoves[START_STATE][STAR_CHAR]                   = TIMES_STATE;
    mLegalMoves[START_STATE][VBAR_CHAR]                   = VBAR_STATE;
    mLegalMoves[START_STATE][WHITESPACE_CHAR]             = START_STATE;

    mLegalMoves[AND_STATE][AND_CHAR]                      = AND_AND_STATE;
    mLegalMoves[DIVIDE_STATE][EQUAL_CHAR]                 = DIVIDE_EQUAL_STATE;
    mLegalMoves[DIVIDE_STATE][FSLASH_CHAR]                = LINE_COMMENT_STATE;
    mLegalMoves[DIVIDE_STATE][STAR_CHAR]                  = MULTILINE_COMMENT_START_STATE;
    mLegalMoves[EQUAL_STATE][EQUAL_CHAR]                  = EQUAL_TO_STATE;
    mLegalMoves[GREATER_THAN_STATE][EQUAL_CHAR]           = GREATER_THAN_OR_EQUAL_STATE;
    mLegalMoves[GREATER_THAN_STATE][GREATER_THAN_CHAR]    = EXTRACTION_STATE;
    mLegalMoves[IDENTIFIER_STATE][DIGIT_CHAR]             = IDENTIFIER_STATE;
    mLegalMoves[IDENTIFIER_STATE][LETTER_CHAR]            = IDENTIFIER_STATE;
    mLegalMoves[IDENTIFIER_STATE][UNDERSCORE_CHAR]        = IDENTIFIER_STATE;
    mLegalMoves[INTEGER_STATE][DIGIT_CHAR]                = INTEGER_STATE;
    mLegalMoves[LESS_THAN_STATE][EQUAL_CHAR]              = LESS_THAN_OR_EQUAL_STATE;
    mLegalMoves[LESS_THAN_STATE][LESS_THAN_CHAR]          = INSERTION_STATE;
    mLegalMoves[MINUS_STATE][EQUAL_CHAR]                  = MINUS_EQUAL_STATE;
    mLegalMoves[MINUS_STATE][MINUS_CHAR]                  = MINUS_MINUS_STATE;
    mLegalMoves[NOT_STATE][EQUAL_CHAR]                    = NOT_EQUAL_STATE;
    mLegalMoves[PLUS_STATE][EQUAL_CHAR]                   = PLUS_EQUAL_STATE;
    mLegalMoves[PLUS_STATE][PLUS_CHAR]                    = PLUS_PLUS_STATE;
    mLegalMoves[TIMES_STATE][EQUAL_CHAR]                  = TIMES_EQUAL_STATE;
    mLegalMoves[VBAR_STATE][VBAR_CHAR]                    = VBAR_VBAR_STATE;

    // Single line comment
    for (int j = 0; j < LAST_CHAR; j ++) {
        mLegalMoves[LINE_COMMENT_STATE][j]                = LINE_COMMENT_STATE;
    }
    mLegalMoves[LINE_COMMENT_STATE][NEWLINE_CHAR]         = START_STATE;

    // Multiline comments
    for (int j = 0; j < LAST_CHAR; j ++) {
        mLegalMoves[MULTILINE_COMMENT_START_STATE][j]     = MULTILINE_COMMENT_START_STATE;
    }
//    mLegalMoves[MULTILINE_COMMENT_START_STATE][ENDFILE_CHAR] = IDENTIFIER_STATE;
    mLegalMoves[MULTILINE_COMMENT_START_STATE][STAR_CHAR] = MULTILINE_COMMENT_END_STATE;

    for (int j = 0; j < LAST_CHAR; j ++) {
        mLegalMoves[MULTILINE_COMMENT_END_STATE][j]       = MULTILINE_COMMENT_START_STATE;
    }
//    mLegalMoves[MULITLINE_COMMENT_END][ENDFILE] = MULITLINE_COMMENT_END;
    mLegalMoves[MULTILINE_COMMENT_END_STATE][STAR_CHAR]   = MULTILINE_COMMENT_END_STATE;
    mLegalMoves[MULTILINE_COMMENT_END_STATE][FSLASH_CHAR] = START_STATE;

    // Set all correspondingTokenType types to invalid so we don't forget any
    for (int i = 0; i < LAST_STATE; i++) {
        mCorrespondingTokenTypes[i]                       = BAD_TOKEN;
    }

    // Set allowed tokenTypes for each MachineState
    mCorrespondingTokenTypes[AND_AND_STATE]               = AND_TOKEN;
    mCorrespondingTokenTypes[DIVIDE_EQUAL_STATE]          = DIVIDE_EQUAL_TOKEN;
    mCorrespondingTokenTypes[DIVIDE_STATE]                = DIVIDE_TOKEN;
    mCorrespondingTokenTypes[ENDFILE_STATE]               = ENDFILE_TOKEN;
    mCorrespondingTokenTypes[EQUAL_STATE]                 = ASSIGNMENT_TOKEN;
    mCorrespondingTokenTypes[EQUAL_TO_STATE]              = EQUAL_TOKEN;
    mCorrespondingTokenTypes[EXTRACTION_STATE]            = EXTRACTION_TOKEN;
    mCorrespondingTokenTypes[GREATER_THAN_OR_EQUAL_STATE] = GREATER_THAN_OR_EQUAL_TOKEN;
    mCorrespondingTokenTypes[GREATER_THAN_STATE]          = GREATER_THAN_TOKEN;
    mCorrespondingTokenTypes[IDENTIFIER_STATE]            = IDENTIFIER_TOKEN;
    mCorrespondingTokenTypes[INSERTION_STATE]             = INSERTION_TOKEN;
    mCorrespondingTokenTypes[INTEGER_STATE]               = INTEGER_TOKEN;
    mCorrespondingTokenTypes[LBRACKET_STATE]              = LBRACKET_TOKEN;
    mCorrespondingTokenTypes[LCURLY_STATE]                = LCURLY_TOKEN;
    mCorrespondingTokenTypes[LESS_THAN_OR_EQUAL_STATE]    = LESS_THAN_OR_EQUAL_TOKEN;
    mCorrespondingTokenTypes[LESS_THAN_STATE]             = LESS_THAN_TOKEN;
    mCorrespondingTokenTypes[LPAREN_STATE]                = LPAREN_TOKEN;
    mCorrespondingTokenTypes[MINUS_EQUAL_STATE]           = MINUS_EQUAL_TOKEN;
    mCorrespondingTokenTypes[MINUS_MINUS_STATE]           = DECREMENT_TOKEN;
    mCorrespondingTokenTypes[MINUS_STATE]                 = MINUS_TOKEN;
    mCorrespondingTokenTypes[MODULO_STATE]                = MODULO_TOKEN;
    mCorrespondingTokenTypes[NOT_EQUAL_STATE]             = NOT_EQUAL_TOKEN;
    mCorrespondingTokenTypes[NOT_STATE]                   = NOT_TOKEN;
    mCorrespondingTokenTypes[PLUS_EQUAL_STATE]            = PLUS_EQUAL_TOKEN;
    mCorrespondingTokenTypes[PLUS_PLUS_STATE]             = INCREMENT_TOKEN;
    mCorrespondingTokenTypes[PLUS_STATE]                  = PLUS_TOKEN;
    mCorrespondingTokenTypes[RBRACKET_STATE]              = RBRACKET_TOKEN;
    mCorrespondingTokenTypes[RCURLY_STATE]                = RCURLY_TOKEN;
    mCorrespondingTokenTypes[RPAREN_STATE]                = RPAREN_TOKEN;
    mCorrespondingTokenTypes[SEMICOLON_STATE]             = SEMICOLON_TOKEN;
    mCorrespondingTokenTypes[TIMES_EQUAL_STATE]           = TIMES_EQUAL_TOKEN;
    mCorrespondingTokenTypes[TIMES_STATE]                 = TIMES_TOKEN;
    mCorrespondingTokenTypes[VBAR_VBAR_STATE]             = OR_TOKEN;
}

StateMachineClass::~StateMachineClass() {}

MachineState StateMachineClass::GetCurrentState() {
    return mCurrentState;
}

MachineState StateMachineClass::UpdateState(const char currentCharacter, TokenType &correspondingTokenType) {
    // convert the input character into an input character type
    auto charType = BAD_CHAR;


    if (isdigit(currentCharacter)) {
        charType = DIGIT_CHAR;
    } else if (isalpha(currentCharacter)) {
        charType = LETTER_CHAR;
    } else if (isspace(currentCharacter)) {
        charType = WHITESPACE_CHAR;
    }

    switch (currentCharacter) {
        case '\n':
            charType = NEWLINE_CHAR;
            break;
        case '_':
            charType = UNDERSCORE_CHAR;
            break;
        case '+':
            charType = PLUS_CHAR;
            break;
        case '-':
            charType = MINUS_CHAR;
            break;
        case '*':
            charType = STAR_CHAR;
            break;
        case '/':
            charType = FSLASH_CHAR;
            break;
        case '%':
            charType = PERCENT_CHAR;
            break;
        case '\\':
            charType = BSLASH_CHAR;
            break;
        case '<':
            charType = LESS_THAN_CHAR;
            break;
        case '>':
            charType = GREATER_THAN_CHAR;
            break;
        case '=':
            charType = EQUAL_CHAR;
            break;
        case '&':
            charType = AND_CHAR;
            break;
        case '|':
            charType = VBAR_CHAR;
            break;
        case '(':
            charType = LPAREN_CHAR;
            break;
        case ')':
            charType = RPAREN_CHAR;
            break;
        case '{':
            charType = LCURLY_CHAR;
            break;
        case '}':
            charType = RCURLY_CHAR;
            break;
        case '[':
            charType = LBRACKET_CHAR;
            break;
        case ']':
            charType = RBRACKET_CHAR;
            break;
        case '!':
            charType = EXCLAMATION_CHAR;
            break;
        case ';':
            charType = SEMICOLON_CHAR;
            break;
        case EOF:
            charType = ENDFILE_CHAR;
            break;
    }
    
    // Then index the current state and character type into the mLegalMoves array to find the next state, which is the return value.
    // But a little bookkeeping is required.


    // Right before updating mCurrentState and then returning it,
    // set the correspondingTokenType reference parameter as follows
    correspondingTokenType = mCorrespondingTokenTypes[mCurrentState];
    mCurrentState = mLegalMoves[mCurrentState][charType];
    return mCurrentState;
}


