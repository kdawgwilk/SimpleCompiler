//
//  StateMachineTests.cpp
//  SimpleCompiler
//
//  Created by Kaden Wilkinson on 2/8/17.
//  Copyright © 2017 Kaden Wilkinson. All rights reserved.
//


#include "StateMachine.hpp"


class StateMachineClassTests : public Test {
protected:
    StateMachineClass stateMachine;
    TokenType correspondingTokenType;

    void UpdateState(string characters) {
        for (char c : characters) {
            stateMachine.UpdateState(c, correspondingTokenType);
        }
    }

    MachineState GetCurrentState() {
        return stateMachine.GetCurrentState();
    }
};

TEST_F(StateMachineClassTests, Init) {
    EXPECT_EQ(GetCurrentState(), START_STATE);
}

// MARK: - Digit

TEST_F(StateMachineClassTests, UpdateState_Digit) {
    UpdateState("1");
    auto state = GetCurrentState();
    EXPECT_EQ(state, INTEGER_STATE);
//    EXPECT_EQ(correspondingTokenType, BAD_TOKEN);
}

TEST_F(StateMachineClassTests, UpdateState_Digit_Digit) {
    UpdateState("12");
    auto state = GetCurrentState();
    EXPECT_EQ(state, INTEGER_STATE);
//    EXPECT_EQ(correspondingTokenType, INTEGER_TOKEN);
}

TEST_F(StateMachineClassTests, UpdateState_Digit_NotDigit) {
    UpdateState("1A");
    auto state = GetCurrentState();
    EXPECT_EQ(state, CANT_MOVE_STATE);
//    EXPECT_EQ(correspondingTokenType, BAD_TOKEN);
}

// MARK: - Letter

TEST_F(StateMachineClassTests, UpdateState_Letter) {
    UpdateState("A");
    auto state = GetCurrentState();
    EXPECT_EQ(state, IDENTIFIER_STATE);
//    EXPECT_EQ(correspondingTokenType, INTEGER_TOKEN);
}

TEST_F(StateMachineClassTests, UpdateState_Letter_Letter) {
    UpdateState("AB");
    auto state = GetCurrentState();
    EXPECT_EQ(state, IDENTIFIER_STATE);
//    EXPECT_EQ(correspondingTokenType, INTEGER_TOKEN);
}

TEST_F(StateMachineClassTests, UpdateState_Letter_Digit) {
    UpdateState("A1");
    auto state = GetCurrentState();
    EXPECT_EQ(state, IDENTIFIER_STATE);
//    EXPECT_EQ(correspondingTokenType, INTEGER_TOKEN);
}

TEST_F(StateMachineClassTests, UpdateState_Letter_Digit_Other) {
    UpdateState("A1 ");
    auto state = GetCurrentState();
    EXPECT_EQ(state, CANT_MOVE_STATE);
    //    EXPECT_EQ(correspondingTokenType, INTEGER_TOKEN);
}

TEST_F(StateMachineClassTests, UpdateState_Letter_Underscore) {
    UpdateState("A_");
    auto state = GetCurrentState();
    EXPECT_EQ(state, IDENTIFIER_STATE);
//    EXPECT_EQ(correspondingTokenType, INTEGER_TOKEN);
}

TEST_F(StateMachineClassTests, UpdateState_Letter_Underscore_Other) {
    UpdateState("A_ ");
    auto state = GetCurrentState();
    EXPECT_EQ(state, CANT_MOVE_STATE);
    //    EXPECT_EQ(correspondingTokenType, INTEGER_TOKEN);
}

TEST_F(StateMachineClassTests, UpdateState_Letter_Other) {
    UpdateState("A ");
    auto state = GetCurrentState();
    EXPECT_EQ(state, CANT_MOVE_STATE);
//    EXPECT_EQ(correspondingTokenType, INTEGER_TOKEN);
}

// MARK: - Whitespace

TEST_F(StateMachineClassTests, UpdateState_Space) {
    UpdateState(" ");
    auto state = GetCurrentState();
    EXPECT_EQ(state, START_STATE);
//    EXPECT_EQ(correspondingTokenType, INTEGER_TOKEN);
}

TEST_F(StateMachineClassTests, UpdateState_Space_Newline) {
    UpdateState(" \n");
    auto state = GetCurrentState();
    EXPECT_EQ(state, START_STATE);
//    EXPECT_EQ(correspondingTokenType, INTEGER_TOKEN);
}

TEST_F(StateMachineClassTests, UpdateState_Space_Letter) {
    UpdateState(" A");
    auto state = GetCurrentState();
    EXPECT_EQ(state, IDENTIFIER_STATE);
//    EXPECT_EQ(correspondingTokenType, INTEGER_TOKEN);
}

// MARK: - Plus

TEST_F(StateMachineClassTests, UpdateState_Plus) {
    UpdateState("+");
    auto state = GetCurrentState();
    EXPECT_EQ(state, PLUS_STATE);
//    EXPECT_EQ(correspondingTokenType, INTEGER_TOKEN);
}

TEST_F(StateMachineClassTests, UpdateState_Plus_Plus) {
    UpdateState("++");
    auto state = GetCurrentState();
    EXPECT_EQ(state, PLUS_PLUS_STATE);
//    EXPECT_EQ(correspondingTokenType, INTEGER_TOKEN);
}

TEST_F(StateMachineClassTests, UpdateState_Plus_Plus_Other) {
    UpdateState("++ ");
    auto state = GetCurrentState();
    EXPECT_EQ(state, CANT_MOVE_STATE);
    //    EXPECT_EQ(correspondingTokenType, INTEGER_TOKEN);
}

TEST_F(StateMachineClassTests, UpdateState_Plus_Equal) {
    UpdateState("+=");
    auto state = GetCurrentState();
    EXPECT_EQ(state, PLUS_EQUAL_STATE);
//    EXPECT_EQ(correspondingTokenType, INTEGER_TOKEN);
}

TEST_F(StateMachineClassTests, UpdateState_Plus_Equal_Other) {
    UpdateState("+= ");
    auto state = GetCurrentState();
    EXPECT_EQ(state, CANT_MOVE_STATE);
    //    EXPECT_EQ(correspondingTokenType, INTEGER_TOKEN);
}

TEST_F(StateMachineClassTests, UpdateState_Plus_Other) {
    UpdateState("+ ");
    auto state = GetCurrentState();
    EXPECT_EQ(state, CANT_MOVE_STATE);
//    EXPECT_EQ(correspondingTokenType, INTEGER_TOKEN);
}

// MARK: - Minus

TEST_F(StateMachineClassTests, UpdateState_Minus) {
    UpdateState("-");
    auto state = GetCurrentState();
    EXPECT_EQ(state, MINUS_STATE);
//    EXPECT_EQ(correspondingTokenType, INTEGER_TOKEN);
}

TEST_F(StateMachineClassTests, UpdateState_Minus_Minus) {
    UpdateState("--");
    auto state = GetCurrentState();
    EXPECT_EQ(state, MINUS_MINUS_STATE);
//    EXPECT_EQ(correspondingTokenType, INTEGER_TOKEN);
}

TEST_F(StateMachineClassTests, UpdateState_Minus_Minus_Other) {
    UpdateState("-- ");
    auto state = GetCurrentState();
    EXPECT_EQ(state, CANT_MOVE_STATE);
    //    EXPECT_EQ(correspondingTokenType, INTEGER_TOKEN);
}

TEST_F(StateMachineClassTests, UpdateState_Minus_Equal) {
    UpdateState("-=");
    auto state = GetCurrentState();
    EXPECT_EQ(state, MINUS_EQUAL_STATE);
//    EXPECT_EQ(correspondingTokenType, INTEGER_TOKEN);
}

TEST_F(StateMachineClassTests, UpdateState_Minus_Equal_Other) {
    UpdateState("-= ");
    auto state = GetCurrentState();
    EXPECT_EQ(state, CANT_MOVE_STATE);
    //    EXPECT_EQ(correspondingTokenType, INTEGER_TOKEN);
}

TEST_F(StateMachineClassTests, UpdateState_Minus_Other) {
    UpdateState("- ");
    auto state = GetCurrentState();
    EXPECT_EQ(state, CANT_MOVE_STATE);
//    EXPECT_EQ(correspondingTokenType, INTEGER_TOKEN);
}

// MARK: - Star

TEST_F(StateMachineClassTests, UpdateState_Star) {
    UpdateState("*");
    auto state = GetCurrentState();
    EXPECT_EQ(state, TIMES_STATE);
//    EXPECT_EQ(correspondingTokenType, INTEGER_TOKEN);
}

TEST_F(StateMachineClassTests, UpdateState_Star_Equal) {
    UpdateState("*=");
    auto state = GetCurrentState();
    EXPECT_EQ(state, TIMES_EQUAL_STATE);
//    EXPECT_EQ(correspondingTokenType, INTEGER_TOKEN);
}

TEST_F(StateMachineClassTests, UpdateState_Star_Equal_Other) {
    UpdateState("*= ");
    auto state = GetCurrentState();
    EXPECT_EQ(state, CANT_MOVE_STATE);
    //    EXPECT_EQ(correspondingTokenType, INTEGER_TOKEN);
}

TEST_F(StateMachineClassTests, UpdateState_Star_Other) {
    UpdateState("* ");
    auto state = GetCurrentState();
    EXPECT_EQ(state, CANT_MOVE_STATE);
//    EXPECT_EQ(correspondingTokenType, INTEGER_TOKEN);
}

// MARK: - ForwardSlash

TEST_F(StateMachineClassTests, UpdateState_ForwardSlash) {
    UpdateState("/");
    auto state = GetCurrentState();
    EXPECT_EQ(state, DIVIDE_STATE);
//    EXPECT_EQ(correspondingTokenType, INTEGER_TOKEN);
}

TEST_F(StateMachineClassTests, UpdateState_ForwardSlash_Equal) {
    UpdateState("/=");
    auto state = GetCurrentState();
    EXPECT_EQ(state, DIVIDE_EQUAL_STATE);
//    EXPECT_EQ(correspondingTokenType, INTEGER_TOKEN);
}

TEST_F(StateMachineClassTests, UpdateState_ForwardSlash_Equal_Other) {
    UpdateState("/= ");
    auto state = GetCurrentState();
    EXPECT_EQ(state, CANT_MOVE_STATE);
    //    EXPECT_EQ(correspondingTokenType, INTEGER_TOKEN);
}

TEST_F(StateMachineClassTests, UpdateState_ForwardSlash_Star) {
    UpdateState("/*");
    auto state = GetCurrentState();
    EXPECT_EQ(state, MULTILINE_COMMENT_START_STATE);
//    EXPECT_EQ(correspondingTokenType, INTEGER_TOKEN);
}

TEST_F(StateMachineClassTests, UpdateState_ForwardSlash_Star_Star) {
    UpdateState("/**");
    auto state = GetCurrentState();
    EXPECT_EQ(state, MULTILINE_COMMENT_END_STATE);
    //    EXPECT_EQ(correspondingTokenType, INTEGER_TOKEN);
}

TEST_F(StateMachineClassTests, UpdateState_ForwardSlash_Star_Other) {
    UpdateState("/* ");
    auto state = GetCurrentState();
    EXPECT_EQ(state, MULTILINE_COMMENT_START_STATE);
    //    EXPECT_EQ(correspondingTokenType, INTEGER_TOKEN);
}

TEST_F(StateMachineClassTests, UpdateState_ForwardSlash_Star_Other_Star) {
    UpdateState("/* *");
    auto state = GetCurrentState();
    EXPECT_EQ(state, MULTILINE_COMMENT_END_STATE);
    //    EXPECT_EQ(correspondingTokenType, INTEGER_TOKEN);
}

TEST_F(StateMachineClassTests, UpdateState_ForwardSlash_Star_Other_Star_Star) {
    UpdateState("/* **");
    auto state = GetCurrentState();
    EXPECT_EQ(state, MULTILINE_COMMENT_END_STATE);
    //    EXPECT_EQ(correspondingTokenType, INTEGER_TOKEN);
}

TEST_F(StateMachineClassTests, UpdateState_ForwardSlash_Star_Other_Star_ForwardSlash) {
    UpdateState("/* */");
    auto state = GetCurrentState();
    EXPECT_EQ(state, START_STATE);
    //    EXPECT_EQ(correspondingTokenType, INTEGER_TOKEN);
}

TEST_F(StateMachineClassTests, UpdateState_ForwardSlash_ForwardSlash) {
    UpdateState("//");
    auto state = GetCurrentState();
    EXPECT_EQ(state, LINE_COMMENT_STATE);
//    EXPECT_EQ(correspondingTokenType, INTEGER_TOKEN);
}

TEST_F(StateMachineClassTests, UpdateState_ForwardSlash_Other) {
    UpdateState("/ ");
    auto state = GetCurrentState();
    EXPECT_EQ(state, CANT_MOVE_STATE);
//    EXPECT_EQ(correspondingTokenType, INTEGER_TOKEN);
}

// MARK: - BackSlash
// TODO: Not implemented yet
TEST_F(StateMachineClassTests, UpdateState_BackSlash) {
    UpdateState("\\");
    auto state = GetCurrentState();
    EXPECT_EQ(state, CANT_MOVE_STATE);
//    EXPECT_EQ(correspondingTokenType, INTEGER_TOKEN);
}

// MARK: - LessThan

TEST_F(StateMachineClassTests, UpdateState_LessThan) {
    UpdateState("<");
    auto state = GetCurrentState();
    EXPECT_EQ(state, LESS_THAN_STATE);
//    EXPECT_EQ(correspondingTokenType, INTEGER_TOKEN);
}

TEST_F(StateMachineClassTests, UpdateState_LessThan_Other) {
    UpdateState("< ");
    auto state = GetCurrentState();
    EXPECT_EQ(state, CANT_MOVE_STATE);
    //    EXPECT_EQ(correspondingTokenType, INTEGER_TOKEN);
}

TEST_F(StateMachineClassTests, UpdateState_LessThan_Equal) {
    UpdateState("<=");
    auto state = GetCurrentState();
    EXPECT_EQ(state, LESS_THAN_OR_EQUAL_STATE);
    //    EXPECT_EQ(correspondingTokenType, INTEGER_TOKEN);
}

TEST_F(StateMachineClassTests, UpdateState_LessThan_Equal_Other) {
    UpdateState("<= ");
    auto state = GetCurrentState();
    EXPECT_EQ(state, CANT_MOVE_STATE);
    //    EXPECT_EQ(correspondingTokenType, INTEGER_TOKEN);
}

TEST_F(StateMachineClassTests, UpdateState_LessThan_LessThan) {
    UpdateState("<<");
    auto state = GetCurrentState();
    EXPECT_EQ(state, INSERTION_STATE);
    //    EXPECT_EQ(correspondingTokenType, INTEGER_TOKEN);
}

TEST_F(StateMachineClassTests, UpdateState_LessThan_LessThan_Other) {
    UpdateState("<< ");
    auto state = GetCurrentState();
    EXPECT_EQ(state, CANT_MOVE_STATE);
    //    EXPECT_EQ(correspondingTokenType, INTEGER_TOKEN);
}

// MARK: - GreaterThan

TEST_F(StateMachineClassTests, UpdateState_GreaterThan) {
    UpdateState(">");
    auto state = GetCurrentState();
    EXPECT_EQ(state, GREATER_THAN_STATE);
//    EXPECT_EQ(correspondingTokenType, INTEGER_TOKEN);
}

TEST_F(StateMachineClassTests, UpdateState_GreaterThan_Other) {
    UpdateState("> ");
    auto state = GetCurrentState();
    EXPECT_EQ(state, CANT_MOVE_STATE);
    //    EXPECT_EQ(correspondingTokenType, INTEGER_TOKEN);
}

TEST_F(StateMachineClassTests, UpdateState_GreaterThan_Equal) {
    UpdateState(">=");
    auto state = GetCurrentState();
    EXPECT_EQ(state, GREATER_THAN_OR_EQUAL_STATE);
    //    EXPECT_EQ(correspondingTokenType, INTEGER_TOKEN);
}

TEST_F(StateMachineClassTests, UpdateState_GreaterThan_Equal_Other) {
    UpdateState(">= ");
    auto state = GetCurrentState();
    EXPECT_EQ(state, CANT_MOVE_STATE);
    //    EXPECT_EQ(correspondingTokenType, INTEGER_TOKEN);
}

TEST_F(StateMachineClassTests, UpdateState_GreaterThan_GreaterThan) {
    UpdateState(">>");
    auto state = GetCurrentState();
    EXPECT_EQ(state, EXTRACTION_STATE);
    //    EXPECT_EQ(correspondingTokenType, INTEGER_TOKEN);
}

TEST_F(StateMachineClassTests, UpdateState_GreaterThan_GreaterThan_Other) {
    UpdateState(">> ");
    auto state = GetCurrentState();
    EXPECT_EQ(state, CANT_MOVE_STATE);
    //    EXPECT_EQ(correspondingTokenType, INTEGER_TOKEN);
}

// MARK: - Equal

TEST_F(StateMachineClassTests, UpdateState_Equal) {
    UpdateState("=");
    auto state = GetCurrentState();
    EXPECT_EQ(state, EQUAL_STATE);
//    EXPECT_EQ(correspondingTokenType, INTEGER_TOKEN);
}

TEST_F(StateMachineClassTests, UpdateState_Equal_Other) {
    UpdateState("= ");
    auto state = GetCurrentState();
    EXPECT_EQ(state, CANT_MOVE_STATE);
    //    EXPECT_EQ(correspondingTokenType, INTEGER_TOKEN);
}

TEST_F(StateMachineClassTests, UpdateState_Equal_Equal) {
    UpdateState("==");
    auto state = GetCurrentState();
    EXPECT_EQ(state, EQUAL_TO_STATE);
    //    EXPECT_EQ(correspondingTokenType, INTEGER_TOKEN);
}

TEST_F(StateMachineClassTests, UpdateState_Equal_Equal_Other) {
    UpdateState("== ");
    auto state = GetCurrentState();
    EXPECT_EQ(state, CANT_MOVE_STATE);
    //    EXPECT_EQ(correspondingTokenType, INTEGER_TOKEN);
}

// MARK: - Parens

TEST_F(StateMachineClassTests, UpdateState_LeftParen) {
    UpdateState("(");
    auto state = GetCurrentState();
    EXPECT_EQ(state, LPAREN_STATE);
//    EXPECT_EQ(correspondingTokenType, INTEGER_TOKEN);
}

TEST_F(StateMachineClassTests, UpdateState_LeftParen_Other) {
    UpdateState("( ");
    auto state = GetCurrentState();
    EXPECT_EQ(state, CANT_MOVE_STATE);
    //    EXPECT_EQ(correspondingTokenType, INTEGER_TOKEN);
}

// FIXME: Failing
//TEST_F(StateMachineClassTests, UpdateState_LeftParen_RightParen) {
//    UpdateState("()");
//    auto state = GetCurrentState();
//    EXPECT_EQ(state, RPAREN_STATE);
////      EXPECT_EQ(correspondingTokenType, INTEGER_TOKEN);
//}

//TEST_F(StateMachineClassTests, UpdateState_LeftParen_RightParen_Other) {
//    UpdateState("() ");
//    auto state = GetCurrentState();
//    EXPECT_EQ(state, CANT_MOVE_STATE);
////    EXPECT_EQ(correspondingTokenType, INTEGER_TOKEN);
//}

TEST_F(StateMachineClassTests, UpdateState_RightParen) {
    UpdateState(")");
    auto state = GetCurrentState();
    EXPECT_EQ(state, RPAREN_STATE);
//    EXPECT_EQ(correspondingTokenType, INTEGER_TOKEN);
}

TEST_F(StateMachineClassTests, UpdateState_RightParen_Other) {
    UpdateState(") ");
    auto state = GetCurrentState();
    EXPECT_EQ(state, CANT_MOVE_STATE);
//    EXPECT_EQ(correspondingTokenType, INTEGER_TOKEN);
}

// MARK: - CurlyBraces

TEST_F(StateMachineClassTests, UpdateState_LeftCurly) {
    UpdateState("{");
    auto state = GetCurrentState();
    EXPECT_EQ(state, LCURLY_STATE);
//    EXPECT_EQ(correspondingTokenType, INTEGER_TOKEN);
}

TEST_F(StateMachineClassTests, UpdateState_LeftCurly_Other) {
    UpdateState("{ ");
    auto state = GetCurrentState();
    EXPECT_EQ(state, CANT_MOVE_STATE);
//    EXPECT_EQ(correspondingTokenType, INTEGER_TOKEN);
}

TEST_F(StateMachineClassTests, UpdateState_RightCurly) {
    UpdateState("}");
    auto state = GetCurrentState();
    EXPECT_EQ(state, RCURLY_STATE);
//    EXPECT_EQ(correspondingTokenType, INTEGER_TOKEN);
}

TEST_F(StateMachineClassTests, UpdateState_RightCurly_Other) {
    UpdateState("} ");
    auto state = GetCurrentState();
    EXPECT_EQ(state, CANT_MOVE_STATE);
//    EXPECT_EQ(correspondingTokenType, INTEGER_TOKEN);
}

// MARK: - Brackets

TEST_F(StateMachineClassTests, UpdateState_LeftBracket) {
    UpdateState("[");
    auto state = GetCurrentState();
    EXPECT_EQ(state, LBRACKET_STATE);
//    EXPECT_EQ(correspondingTokenType, INTEGER_TOKEN);
}

TEST_F(StateMachineClassTests, UpdateState_LeftBracket_Other) {
    UpdateState("[ ");
    auto state = GetCurrentState();
    EXPECT_EQ(state, CANT_MOVE_STATE);
    //    EXPECT_EQ(correspondingTokenType, INTEGER_TOKEN);
}

TEST_F(StateMachineClassTests, UpdateState_RightBracket) {
    UpdateState("]");
    auto state = GetCurrentState();
    EXPECT_EQ(state, RBRACKET_STATE);
//    EXPECT_EQ(correspondingTokenType, INTEGER_TOKEN);
}

TEST_F(StateMachineClassTests, UpdateState_RightBracket_Other) {
    UpdateState("] ");
    auto state = GetCurrentState();
    EXPECT_EQ(state, CANT_MOVE_STATE);
    //    EXPECT_EQ(correspondingTokenType, INTEGER_TOKEN);
}

// MARK: - And

TEST_F(StateMachineClassTests, UpdateState_And) {
    UpdateState("&");
    auto state = GetCurrentState();
    EXPECT_EQ(state, AND_STATE);
    //    EXPECT_EQ(correspondingTokenType, INTEGER_TOKEN);
}

TEST_F(StateMachineClassTests, UpdateState_And_Other) {
    UpdateState("& ");
    auto state = GetCurrentState();
    EXPECT_EQ(state, CANT_MOVE_STATE);
    //    EXPECT_EQ(correspondingTokenType, INTEGER_TOKEN);
}

TEST_F(StateMachineClassTests, UpdateState_And_And) {
    UpdateState("&&");
    auto state = GetCurrentState();
    EXPECT_EQ(state, AND_AND_STATE);
    //    EXPECT_EQ(correspondingTokenType, INTEGER_TOKEN);
}

TEST_F(StateMachineClassTests, UpdateState_And_And_Other) {
    UpdateState("&& ");
    auto state = GetCurrentState();
    EXPECT_EQ(state, CANT_MOVE_STATE);
    //    EXPECT_EQ(correspondingTokenType, INTEGER_TOKEN);
}

// MARK: - Vertical Bar

TEST_F(StateMachineClassTests, UpdateState_VerticalBar) {
    UpdateState("|");
    auto state = GetCurrentState();
    EXPECT_EQ(state, VBAR_STATE);
    //    EXPECT_EQ(correspondingTokenType, INTEGER_TOKEN);
}

TEST_F(StateMachineClassTests, UpdateState_VerticalBar_Other) {
    UpdateState("| ");
    auto state = GetCurrentState();
    EXPECT_EQ(state, CANT_MOVE_STATE);
    //    EXPECT_EQ(correspondingTokenType, INTEGER_TOKEN);
}

TEST_F(StateMachineClassTests, UpdateState_VerticalBar_VerticalBar) {
    UpdateState("||");
    auto state = GetCurrentState();
    EXPECT_EQ(state, VBAR_VBAR_STATE);
    //    EXPECT_EQ(correspondingTokenType, INTEGER_TOKEN);
}

TEST_F(StateMachineClassTests, UpdateState_VerticalBar_VerticalBar_Other) {
    UpdateState("|| ");
    auto state = GetCurrentState();
    EXPECT_EQ(state, CANT_MOVE_STATE);
    //    EXPECT_EQ(correspondingTokenType, INTEGER_TOKEN);
}

// MARK: - Exclamation

TEST_F(StateMachineClassTests, UpdateState_Exclamation) {
    UpdateState("!");
    auto state = GetCurrentState();
    EXPECT_EQ(state, NOT_STATE);
//    EXPECT_EQ(correspondingTokenType, INTEGER_TOKEN);
}

TEST_F(StateMachineClassTests, UpdateState_Exclamation_Other) {
    UpdateState("! ");
    auto state = GetCurrentState();
    EXPECT_EQ(state, CANT_MOVE_STATE);
    //    EXPECT_EQ(correspondingTokenType, INTEGER_TOKEN);
}

TEST_F(StateMachineClassTests, UpdateState_Exclamation_Equal) {
    UpdateState("!=");
    auto state = GetCurrentState();
    EXPECT_EQ(state, NOT_EQUAL_STATE);
    //    EXPECT_EQ(correspondingTokenType, INTEGER_TOKEN);
}

TEST_F(StateMachineClassTests, UpdateState_Exclamation_Equal_Other) {
    UpdateState("!= ");
    auto state = GetCurrentState();
    EXPECT_EQ(state, CANT_MOVE_STATE);
    //    EXPECT_EQ(correspondingTokenType, INTEGER_TOKEN);
}

// MARK: - Semicolon

TEST_F(StateMachineClassTests, UpdateState_Semicolon) {
    UpdateState(";");
    auto state = GetCurrentState();
    EXPECT_EQ(state, SEMICOLON_STATE);
//    EXPECT_EQ(correspondingTokenType, INTEGER_TOKEN);
}

TEST_F(StateMachineClassTests, UpdateState_Semicolon_Other) {
    UpdateState("; ");
    auto state = GetCurrentState();
    EXPECT_EQ(state, CANT_MOVE_STATE);
    //    EXPECT_EQ(correspondingTokenType, INTEGER_TOKEN);
}

// MARK: - Endfile

TEST_F(StateMachineClassTests, UpdateState_Endfile) {
    string endFile;
    endFile.push_back(EOF);
    UpdateState(endFile);
    auto state = GetCurrentState();
    EXPECT_EQ(state, ENDFILE_STATE);
//    EXPECT_EQ(correspondingTokenType, INTEGER_TOKEN);
}


