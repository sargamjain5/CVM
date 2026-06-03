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

    auto program = std::make_unique<ProgramNode>();

    while(peek().type != TokenType::END) {

        program->statements.push_back(
            statement()
        );

        // Semicolon is optional for last statement
        if(peek().type == TokenType::SEMICOLON) {
            advance();
        }
        else if(peek().type != TokenType::END) {
            throw std::runtime_error(
                "Expected ';'"
            );
        }
    }

    return program;
}

std::unique_ptr<ASTNode> Parser::statement() {

    if(peek().type == TokenType::PRINT) {

        advance();

        expect(TokenType::LPAREN);

        auto expr = expression();

        expect(TokenType::RPAREN);

        return std::make_unique<PrintNode>(
            std::move(expr)
        );
    }

    if(peek().type == TokenType::IDENTIFIER &&
       current + 1 < tokens.size() &&
       tokens[current + 1].type == TokenType::ASSIGN)
    {
        std::string name = advance().value;

        advance();

        auto value = expression();

        return std::make_unique<AssignmentNode>(
            name,
            std::move(value)
        );
    }

    return expression();
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

        auto expr = expression();

        expect(TokenType::RPAREN);

        return expr;
    }

    throw std::runtime_error(
        "Expected number, variable or '('"
    );
}