//
//  Parser.cpp
//  SimpleCompiler
//
//  Created by Kaden Wilkinson on 2/22/17.
//  Copyright © 2017 Kaden Wilkinson. All rights reserved.
//

#include "Parser.hpp"


ParserClass::ParserClass(ScannerClass *scanner, SymbolTableClass *symbolTable)
: mScanner(scanner)
, mSymbolTable(symbolTable)
{ }

ParserClass::~ParserClass() {
//    delete mScanner;
//    delete mSymbolTable;
}

TokenClass ParserClass::Match(TokenType expectedType) {
    auto currentToken = mScanner->GetNextToken();
    if(currentToken.GetTokenType() != expectedType) {
//        cerr << "Error in ParserClass::Match. " << endl;
        cerr << "Parser Error: " << mScanner->GetFilename() << "[" << mScanner->GetLineNumber() << "," << mScanner->GetColumnNumber() << "]: ";
        cerr << "Expected token type " << TokenClass::GetTypeString(expectedType) << ", but got type " << currentToken.GetTokenTypeName() << endl;
        exit(1);
    }
//    MSG("\tSuccessfully matched Token Type: " << currentToken.GetTokenTypeName() << ". Lexeme: \"" << currentToken.GetLexeme() << "\"");
    return currentToken; // the one we just processed
}
StartNode *ParserClass::Start() {
    auto programNode = Program();
    Match(ENDFILE_TOKEN);
    auto startNode = new StartNode(programNode);
    return startNode;
}

ProgramNode *ParserClass::Program() {
    Match(VOID_TOKEN);
    Match(MAIN_TOKEN);
    Match(LPAREN_TOKEN);
    Match(RPAREN_TOKEN);
    auto blockNode = Block();
    auto programNode = new ProgramNode(blockNode);
    return programNode;
}

BlockNode *ParserClass::Block() {
    Match(LCURLY_TOKEN);
    auto statementGroup = StatementGroup();
    Match(RCURLY_TOKEN);
    auto blockNode = new BlockNode(mSymbolTable, statementGroup);
    return blockNode;
}

StatementGroupNode *ParserClass::StatementGroup() {
    auto statementGroupNode = new StatementGroupNode();

    while (true) {
        auto statement = Statement();
        if (!statement) { break; }
        statementGroupNode->AddStatement(statement);
    }
    return statementGroupNode;
}

StatementNode *ParserClass::Statement() {
    auto token = mScanner->PeekNextToken().GetTokenType();
    switch (token) {
        case INT_TOKEN:
            return DeclarationStatement();
        case IF_TOKEN:
            return IfStatement();
        case WHILE_TOKEN:
            return WhileStatement();
        case DO_TOKEN:
            return DoWhileStatement();
        case REPEAT_TOKEN:
            return RepeatStatement();
        case IDENTIFIER_TOKEN:
            return AssignmentStatement();
        case COUT_TOKEN:
            return CoutStatement();
        case LCURLY_TOKEN:
            return Block();
        default:
            return NULL;
    }
}

IfStatementNode *ParserClass::IfStatement() {
    Match(IF_TOKEN);
    Match(LPAREN_TOKEN);
    auto expressionNode = Expression();
    Match(RPAREN_TOKEN);
    auto statementNode = Statement();
    StatementNode *elseStatementNode = NULL;
    auto token = mScanner->PeekNextToken().GetTokenType();
    if (token == ELSE_TOKEN) {
        Match(ELSE_TOKEN);
        elseStatementNode = Statement();
    }
    auto ifStatementNode = new IfStatementNode(expressionNode, statementNode, elseStatementNode);
    return ifStatementNode;
}

WhileStatementNode *ParserClass::WhileStatement() {
    Match(WHILE_TOKEN);
    Match(LPAREN_TOKEN);
    auto expressionNode = Expression();
    Match(RPAREN_TOKEN);
    auto statementNode = Statement();
    auto whileStatementNode = new WhileStatementNode(expressionNode, statementNode);
    return whileStatementNode;
}

DoWhileStatementNode *ParserClass::DoWhileStatement() {
    Match(DO_TOKEN);
    auto statementNode = Statement();
    Match(WHILE_TOKEN);
    Match(LPAREN_TOKEN);
    auto expressionNode = Expression();
    Match(RPAREN_TOKEN);
    Match(SEMICOLON_TOKEN);
    auto doWhileStatementNode = new DoWhileStatementNode(expressionNode, statementNode);
    return doWhileStatementNode;
}

RepeatStatementNode *ParserClass::RepeatStatement() {
    Match(REPEAT_TOKEN);
    Match(LPAREN_TOKEN);
    auto expressionNode = Expression();
    Match(RPAREN_TOKEN);
    auto statementNode = Statement();
    auto repeatStatementNode = new RepeatStatementNode(expressionNode, statementNode);
    return repeatStatementNode;
}

DeclarationStatementNode *ParserClass::DeclarationStatement() {
    Match(INT_TOKEN);
    auto identifierNode = Identifier();
    ExpressionNode *expressionNode = NULL;
    auto token = mScanner->PeekNextToken().GetTokenType();
    if (token == ASSIGNMENT_TOKEN) {
        Match(token);
        expressionNode = Expression();
    }
    Match(SEMICOLON_TOKEN);
    auto declarationStatementNode = new DeclarationStatementNode(identifierNode, expressionNode);
    return declarationStatementNode;
}

AssignmentNode *ParserClass::AssignmentStatement() {
    auto identifierNode = Identifier();
    auto token = mScanner->PeekNextToken().GetTokenType();
    ExpressionNode *expressionNode;
    switch (token) {
        case PLUS_EQUAL_TOKEN:
            Match(token);
            expressionNode = Expression();
            Match(SEMICOLON_TOKEN);
            return new PlusEqualStatementNode(identifierNode, expressionNode);
        case MINUS_EQUAL_TOKEN:
            Match(token);
            expressionNode = Expression();
            Match(SEMICOLON_TOKEN);
            return new MinusEqualStatementNode(identifierNode, expressionNode);
        case TIMES_EQUAL_TOKEN:
            Match(token);
            expressionNode = Expression();
            Match(SEMICOLON_TOKEN);
            return new TimesEqualStatementNode(identifierNode, expressionNode);
        case DIVIDE_EQUAL_TOKEN:
            Match(token);
            expressionNode = Expression();
            Match(SEMICOLON_TOKEN);
            return new DivideEqualStatementNode(identifierNode, expressionNode);
        case INCREMENT_TOKEN:
            Match(token);
            expressionNode = new IntegerNode(1);
            Match(SEMICOLON_TOKEN);
            return new PlusEqualStatementNode(identifierNode, expressionNode);
        case DECREMENT_TOKEN:
            Match(token);
            expressionNode = new IntegerNode(1);
            Match(SEMICOLON_TOKEN);
            return new MinusEqualStatementNode(identifierNode, expressionNode);
        default:
            Match(ASSIGNMENT_TOKEN);
            expressionNode = Expression();
            Match(SEMICOLON_TOKEN);
            return new AssignmentStatementNode(identifierNode, expressionNode);
    }
}

CoutStatementNode *ParserClass::CoutStatement() {
    Match(COUT_TOKEN);
    auto coutStatementNode = new CoutStatementNode();
    while (true) {
        Match(INSERTION_TOKEN);
        auto token = mScanner->PeekNextToken().GetTokenType();
        if (token == ENDL_TOKEN) {
            Match(ENDL_TOKEN);
            coutStatementNode->AddStatement(NULL);
        }
        token = mScanner->PeekNextToken().GetTokenType();
        if (token == INSERTION_TOKEN) {
            continue;
        } else if (token == SEMICOLON_TOKEN) {
            Match(SEMICOLON_TOKEN);
            return coutStatementNode;
        }

        auto expressionNode = Expression();
        coutStatementNode->AddStatement(expressionNode);
    }
    cerr << "Unexpected end to cout statement" << endl;
    exit(1);
}

ExpressionNode *ParserClass::Expression() {
    return Or();
}

ExpressionNode *ParserClass::Or() {
    auto current = And();
    auto tokenType = mScanner->PeekNextToken().GetTokenType();
    if (tokenType == OR_TOKEN) {
        Match(tokenType);
        current = new OrNode(current, And());
    }
    return current;
}

ExpressionNode *ParserClass::And() {
    auto current = Relationals();
    auto tokenType = mScanner->PeekNextToken().GetTokenType();
    if (tokenType == AND_TOKEN) {
        Match(tokenType);
        current = new AndNode(current, Relationals());
    }
    return current;
}

ExpressionNode *ParserClass::Relationals() {
    auto current = PlusMinus();
    auto tokenType = mScanner->PeekNextToken().GetTokenType();

    switch (tokenType) {
        case LESS_THAN_TOKEN:
            Match(tokenType);
            return new LessNode(current, PlusMinus());
        case LESS_THAN_OR_EQUAL_TOKEN:
            Match(tokenType);
            return new LessEqualNode(current, PlusMinus());
        case GREATER_THAN_TOKEN:
            Match(tokenType);
            return new GreaterNode(current, PlusMinus());
        case GREATER_THAN_OR_EQUAL_TOKEN:
            Match(tokenType);
            return new GreaterEqualNode(current, PlusMinus());
        case EQUAL_TOKEN:
            Match(tokenType);
            return new EqualNode(current, PlusMinus());
        case NOT_EQUAL_TOKEN:
            Match(tokenType);
            return new NotEqualNode(current, PlusMinus());
        default:
            return current;
    }
}

ExpressionNode *ParserClass::PlusMinus() {
    auto current = TimesDivide();
    while (true) {
        auto token = mScanner->PeekNextToken().GetTokenType();
        switch (token) {
            case PLUS_TOKEN:
                Match(token);
                return new PlusNode(current, TimesDivide());
            case MINUS_TOKEN:
                Match(token);
                return new MinusNode(current, TimesDivide());
            default:
                return current;
        }
    }
}

ExpressionNode *ParserClass::TimesDivide() {
    auto current = Unaries();
    while (true) {
        auto token = mScanner->PeekNextToken().GetTokenType();
        switch (token) {
            case TIMES_TOKEN:
                Match(token);
                return new TimesNode(current, Unaries());
            case DIVIDE_TOKEN:
                Match(token);
                return new DivideNode(current, Unaries());
            case MODULO_TOKEN:
                Match(token);
                return new ModulusNode(current, Unaries());
            default:
                return current;
        }
    }
}

// FIXME: Not and Negative not working
ExpressionNode *ParserClass::Unaries() {
    while (true) {
        auto token = mScanner->PeekNextToken().GetTokenType();
        switch (token) {
            case NOT_TOKEN:
                Match(token);
                return new NotNode(Factor());
            case MINUS_TOKEN:
                Match(token);
                return new NegativeNode(Factor());
            default:
                return Factor();
        }
    }
}

/**
 The Factor() method is implemented by looking ahead one token.
 If the token type is IDENTIFIER or INTEGER, it recursively calls methods by those names, and returns whatever they return. 
 If the next token type is an LPAREN, the code should match the LPAREN, recursively call Expression, and then match the RPAREN. 
 It should return whatever the recursive call to Expression returns. 
 If the next token type is not an IDENTIFIER or INTEGER or LPAREN, the code should print an error message and quit.
 */
ExpressionNode *ParserClass::Factor() {
    auto token = mScanner->PeekNextToken();
    auto tokenType = token.GetTokenType();
    switch (tokenType) {
        case IDENTIFIER_TOKEN:
            return Identifier();
        case INTEGER_TOKEN:
            return Integer();
        case LPAREN_TOKEN: {
            Match(LPAREN_TOKEN);
            auto expressionNode = Expression();
            Match(RPAREN_TOKEN);
            return expressionNode;
        }
        default:
            cerr << "Parser Error: Unexpected token: " << mScanner->GetFilename() <<  " [" << mScanner->GetLineNumber() << "," << mScanner->GetColumnNumber() << "]" << "\n" << token << endl;
            exit(1);
    }
}

IdentifierNode *ParserClass::Identifier() {
    auto token = Match(IDENTIFIER_TOKEN);
    return new IdentifierNode(token.GetLexeme(), mSymbolTable);
}

IntegerNode *ParserClass::Integer() {
    auto token = Match(INTEGER_TOKEN);
    return new IntegerNode(atoi(token.GetLexeme().c_str()));
}



