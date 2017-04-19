//
//  MockStateMachine.hpp
//  SimpleCompiler
//
//  Created by Kaden Wilkinson on 3/22/17.
//  Copyright © 2017 Kaden Wilkinson. All rights reserved.
//

#ifndef MockStateMachine_hpp
#define MockStateMachine_hpp

#include "StateMachine.hpp"

class MockStateMachineClass: public StateMachineClass {
public:
    MOCK_METHOD0(GetCurrentState, MachineState());
    MOCK_METHOD2(UpdateState, MachineState(const char currentCharacter, TokenType &correspondingTokenType));
};

#endif /* MockStateMachine_hpp */
