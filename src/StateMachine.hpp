//
//  StateMachine.hpp
//  SimpleCompiler
//
//  Created by Kaden Wilkinson on 1/30/17.
//  Copyright © 2017 Kaden Wilkinson. All rights reserved.
//

#ifndef StateMachine_hpp
#define StateMachine_hpp

#include "Token.hpp"
#include "MachineStates.hpp"
#include "CharacterTypes.hpp"


class StateMachineClass {
    MachineState mCurrentState;

    // The matrix of legal moves:
    MachineState mLegalMoves[LAST_STATE][LAST_CHAR];

    // Which end-machine-states correspond to which token types.
    // (non end states correspond to the BAD_TOKEN token type)
    TokenType mCorrespondingTokenTypes[LAST_STATE];

public:
    StateMachineClass();
    virtual ~StateMachineClass();

    MachineState GetCurrentState();
    MachineState UpdateState(const char currentCharacter, TokenType &correspondingTokenType);
    
};


#endif /* StateMachine_hpp */
