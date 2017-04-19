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
    TokenClass currentToken = mScanner->GetNextToken();
    if(currentToken.GetTokenType() != expectedType) {
//        cerr << "Error in ParserClass::Match. " << endl;
        cerr << "Expected token type " << TokenClass::GetTypeString(expectedType) << ", but got type " << currentToken.GetTokenTypeName() << endl;
        exit(1);
    }
//    MSG("\tSuccessfully matched Token Type: " << currentToken.GetTokenTypeName() << ". Lexeme: \"" << currentToken.GetLexeme() << "\"");
    return currentToken; // the one we just processed
}
StartNode *ParserClass::Start() {
    ProgramNode *programNode = Program();
    Match(ENDFILE_TOKEN);
    StartNode *startNode = new StartNode(programNode);
    return startNode;
}

ProgramNode *ParserClass::Program() {
    Match(VOID_TOKEN);
    Match(MAIN_TOKEN);
    Match(LPAREN_TOKEN);
    Match(RPAREN_TOKEN);
    BlockNode *blockNode = Block();
    ProgramNode *programNode = new ProgramNode(blockNode);
    return programNode;
}

BlockNode *ParserClass::Block() {
    Match(LCURLY_TOKEN);
    StatementGroupNode *statementGroup = StatementGroup();
    Match(RCURLY_TOKEN);
    BlockNode *blockNode = new BlockNode(mSymbolTable, statementGroup);
    return blockNode;
}

StatementGroupNode *ParserClass::StatementGroup() {
    StatementGroupNode *statementGroupNode = new StatementGroupNode();

    while (true) {
        StatementNode *statement = Statement();
        if (!statement) { break; }
        statementGroupNode->AddStatement(statement);
    }
    return statementGroupNode;
}

StatementNode *ParserClass::Statement() {
    TokenType tokenType = mScanner->PeekNextToken().GetTokenType();
    switch (tokenType) {
        case INT_TOKEN:
            return DeclarationStatement();
        case IF_TOKEN:
            return IfStatement();
        case WHILE_TOKEN:
            return WhileStatement();
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

// TODO: Test this code
IfStatementNode *ParserClass::IfStatement() {
    Match(IF_TOKEN);
    Match(LPAREN_TOKEN);
    ExpressionNode *expressionNode = Expression();
    Match(RPAREN_TOKEN);
    StatementNode *statementNode = Statement();
    IfStatementNode *ifStatementNode = new IfStatementNode(expressionNode, statementNode);
    return ifStatementNode;
}

// TODO: Test this code
WhileStatementNode *ParserClass::WhileStatement() {
    Match(WHILE_TOKEN);
    Match(LPAREN_TOKEN);
    ExpressionNode *expressionNode = Expression();
    Match(RPAREN_TOKEN);
    StatementNode *statementNode = Statement();
    WhileStatementNode *whileStatementNode = new WhileStatementNode(expressionNode, statementNode);
    return whileStatementNode;
}


DeclarationStatementNode *ParserClass::DeclarationStatement() {
    Match(INT_TOKEN);
    IdentifierNode *identifierNode = Identifier();
    Match(SEMICOLON_TOKEN);
    DeclarationStatementNode *declarationStatementNode = new DeclarationStatementNode(identifierNode);
    return declarationStatementNode;
}

AssignmentStatementNode *ParserClass::AssignmentStatement() {
    IdentifierNode *identifierNode = Identifier();
    Match(ASSIGNMENT_TOKEN);
    ExpressionNode *expressionNode = Expression();
    Match(SEMICOLON_TOKEN);
    AssignmentStatementNode *assignmentStatementNode = new AssignmentStatementNode(identifierNode, expressionNode);
    return assignmentStatementNode;
}

CoutStatementNode *ParserClass::CoutStatement() {
    Match(COUT_TOKEN);
    Match(INSERTION_TOKEN);

    ExpressionNode *expressionNode = Expression();
//    Match(INSERTION_TOKEN);
//    Match(ENDLINE_TOKEN);
    Match(SEMICOLON_TOKEN);
    CoutStatementNode *coutStatementNode = new CoutStatementNode(expressionNode);
    return coutStatementNode;
}

ExpressionNode *ParserClass::Expression() {
    return Or();
}

// TODO: Test me
ExpressionNode *ParserClass::Or() {
    ExpressionNode *current = And();
    TokenType tokenType = mScanner->PeekNextToken().GetTokenType();
    if (tokenType == OR_TOKEN) {
        Match(tokenType);

        current = new OrNode(current, And());
    }
    return current;
}

// TODO: Test me
ExpressionNode *ParserClass::And() {
    ExpressionNode *current = Relationals();
    TokenType tokenType = mScanner->PeekNextToken().GetTokenType();
    if (tokenType == AND_TOKEN) {
        Match(tokenType);

        current = new AndNode(current, Relationals());
    }
    return current;
}

ExpressionNode *ParserClass::Relationals() {
    ExpressionNode *current = PlusMinus();
    TokenType tokenType = mScanner->PeekNextToken().GetTokenType();
    if (tokenType == LESS_THAN_TOKEN ||
        tokenType == LESS_THAN_OR_EQUAL_TOKEN ||
        tokenType == GREATER_THAN_TOKEN ||
        tokenType == GREATER_THAN_OR_EQUAL_TOKEN ||
        tokenType == EQUAL_TOKEN ||
        tokenType == NOT_EQUAL_TOKEN)
    {
        Match(tokenType); // Match the relational operator

        switch (tokenType) {
            case LESS_THAN_TOKEN:
                current = new LessNode(current, PlusMinus());
                break;
            case LESS_THAN_OR_EQUAL_TOKEN:
                current = new LessEqualNode(current, PlusMinus());
                break;
            case GREATER_THAN_TOKEN:
                current = new GreaterNode(current, PlusMinus());
                break;
            case GREATER_THAN_OR_EQUAL_TOKEN:
                current = new GreaterEqualNode(current, PlusMinus());
                break;
            case EQUAL_TOKEN:
                current = new EqualNode(current, PlusMinus());
                break;
            case NOT_EQUAL_TOKEN:
                current = new NotEqualNode(current, PlusMinus());
                break;
            default:
                break;
        }
    }
    return current;
}

ExpressionNode *ParserClass::PlusMinus() {
    ExpressionNode *current = TimesDivide();
    while (true) {
        TokenType token = mScanner->PeekNextToken().GetTokenType();
        switch (token) {
            case PLUS_TOKEN:
                Match(token);
                current = new PlusNode(current, TimesDivide());
                break;
            case MINUS_TOKEN:
                Match(token);
                current = new MinusNode(current, TimesDivide());
                break;
            default:
                return current;
                break;
        }
    }
}

ExpressionNode *ParserClass::TimesDivide() {
    ExpressionNode *current = Unaries();
    while (true) {
        TokenType token = mScanner->PeekNextToken().GetTokenType();
        switch (token) {
            case TIMES_TOKEN:
                Match(token);
                current = new TimesNode(current, Unaries());
                break;
            case DIVIDE_TOKEN:
                Match(token);
                current = new DivideNode(current, Unaries());
                break;
            default:
                return current;
                break;
        }
    }
}

// TODO: Test this code
ExpressionNode *ParserClass::Unaries() {
    ExpressionNode *current = Factor();
    while (true) {
        TokenType token = mScanner->PeekNextToken().GetTokenType();
        switch (token) {
            case NOT_TOKEN:
                Match(token);
                current = new NotNode(Factor());
                break;
            case NEGATIVE_TOKEN:
                Match(token);
                current = new NegativeNode(Factor());
                break;
            default:
                return current;
                break;
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
    TokenType tokenType = mScanner->PeekNextToken().GetTokenType();
    switch (tokenType) {
        case IDENTIFIER_TOKEN:
            return Identifier();
            break;
        case INTEGER_TOKEN:
            return Integer();
            break;
        case LPAREN_TOKEN: {
            Match(LPAREN_TOKEN);
            ExpressionNode *expressionNode = Expression();
            Match(RPAREN_TOKEN);
            return expressionNode;
            break;
        }
        default:
            cerr << "Unexpected token: " << tokenType << endl;
            exit(1);
            break;
    }
}

IdentifierNode *ParserClass::Identifier() {
    TokenClass token = Match(IDENTIFIER_TOKEN);
    IdentifierNode *identifierNode = new IdentifierNode(token.GetLexeme(), mSymbolTable);
    return identifierNode;
}

IntegerNode *ParserClass::Integer() {
    TokenClass token = Match(INTEGER_TOKEN);
    IntegerNode *integerNode = new IntegerNode(atoi(token.GetLexeme().c_str()));
    return integerNode;
}



