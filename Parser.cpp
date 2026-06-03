#include "Parser.h"

Parser::Parser(std::vector<Token> tokenList)
    : tokens(tokenList), current(0) {}

Token Parser::peek() {
    return tokens[current];
}

Token Parser::advance() {
    return tokens[current++];
}

void Parser::expect(TokenType type) {

    if(peek().type != type) {
        throw std::runtime_error("Unexpected token");
    }

    advance();
}

std::unique_ptr<ASTNode> Parser::parse() {

    auto program =
        std::make_unique<ProgramNode>();

    while(peek().type != TokenType::END) {

        program->statements.push_back(
            statement()
        );

        if(peek().type ==
           TokenType::SEMICOLON)
        {
            advance();
        }
    }

    return program;
}

std::unique_ptr<ASTNode> Parser::ifStatement() {

    advance(); // IF

    expect(TokenType::LPAREN);

    auto condition =
        comparison();

    expect(TokenType::RPAREN);

    expect(TokenType::LBRACE);

    auto ifNode =
        std::make_unique<IfNode>(
            std::move(condition)
        );

    while(peek().type !=
          TokenType::RBRACE)
    {
        ifNode->thenBody.push_back(
            statement()
        );

        if(peek().type ==
           TokenType::SEMICOLON)
        {
            advance();
        }
    }

    expect(TokenType::RBRACE);

    // ELSE PART
    if(peek().type ==
       TokenType::ELSE)
    {
        advance();

        expect(TokenType::LBRACE);

        while(peek().type !=
              TokenType::RBRACE)
        {
            ifNode->elseBody.push_back(
                statement()
            );

            if(peek().type ==
               TokenType::SEMICOLON)
            {
                advance();
            }
        }

        expect(TokenType::RBRACE);
    }

    return ifNode;
}

std::unique_ptr<ASTNode> Parser::whileStatement() {

    advance(); // consume WHILE

    expect(TokenType::LPAREN);

    auto condition = comparison();

    expect(TokenType::RPAREN);

    expect(TokenType::LBRACE);

    auto whileNode =
        std::make_unique<WhileNode>(
            std::move(condition)
        );

    while(peek().type != TokenType::RBRACE) {

        whileNode->body.push_back(
            statement()
        );

        if(peek().type == TokenType::SEMICOLON) {
            advance();
        }
    }

    expect(TokenType::RBRACE);

    return whileNode;
}

std::unique_ptr<ASTNode> Parser::statement() {

    // while(...)
    if(peek().type == TokenType::WHILE) {
        return whileStatement();
    }

    // if(...)
    if(peek().type == TokenType::IF) {
        return ifStatement();
    }

    // print(...)
    if(peek().type == TokenType::PRINT) {

        advance();

        expect(TokenType::LPAREN);

        auto expr = comparison();

        expect(TokenType::RPAREN);

        return std::make_unique<PrintNode>(
            std::move(expr)
        );
    }

    // x = ...
    if(peek().type == TokenType::IDENTIFIER &&
       current + 1 < tokens.size() &&
       tokens[current + 1].type == TokenType::ASSIGN)
    {
        std::string name = advance().value;

        advance(); // consume '='

        auto value = comparison();

        return std::make_unique<AssignmentNode>(
            name,
            std::move(value)
        );
    }

    return comparison();
}

std::unique_ptr<ASTNode> Parser::comparison() {

    auto left = expression();

    while(
        peek().type == TokenType::GREATER ||
        peek().type == TokenType::LESS ||
        peek().type == TokenType::GREATER_EQUAL ||
        peek().type == TokenType::LESS_EQUAL ||
        peek().type == TokenType::EQUAL_EQUAL ||
        peek().type == TokenType::NOT_EQUAL
    )
    {
        Token op = advance();

        auto right = expression();

        char operation;

        if(op.type == TokenType::GREATER)
            operation = '>';

        else if(op.type == TokenType::LESS)
            operation = '<';

        else if(op.type == TokenType::GREATER_EQUAL)
            operation = 'G';

        else if(op.type == TokenType::LESS_EQUAL)
            operation = 'L';

        else if(op.type == TokenType::NOT_EQUAL)
            operation = '!';

        else
            operation = '=';

        left = std::make_unique<BinaryOpNode>(
            operation,
            std::move(left),
            std::move(right)
        );
    }

    return left;
}

std::unique_ptr<ASTNode> Parser::expression() {

    auto left = term();

    while(peek().type == TokenType::PLUS ||
          peek().type == TokenType::MINUS)
    {
        Token op = advance();

        auto right = term();

        left = std::make_unique<BinaryOpNode>(
            op.type == TokenType::PLUS ? '+' : '-',
            std::move(left),
            std::move(right)
        );
    }

    return left;
}

std::unique_ptr<ASTNode> Parser::term() {

    auto left = factor();

    while(peek().type == TokenType::STAR ||
          peek().type == TokenType::SLASH)
    {
        Token op = advance();

        auto right = factor();

        left = std::make_unique<BinaryOpNode>(
            op.type == TokenType::STAR ? '*' : '/',
            std::move(left),
            std::move(right)
        );
    }

    return left;
}

std::unique_ptr<ASTNode> Parser::factor() {

    Token token = advance();

    if(token.type == TokenType::NUMBER) {

        return std::make_unique<NumberNode>(
            stoi(token.value)
        );
    }

    if(token.type == TokenType::IDENTIFIER) {

        return std::make_unique<VariableNode>(
            token.value
        );
    }

    if(token.type == TokenType::LPAREN) {

        auto expr = comparison();

        expect(TokenType::RPAREN);

        return expr;
    }

    throw std::runtime_error(
        "Expected number, variable or '('"
    );
}