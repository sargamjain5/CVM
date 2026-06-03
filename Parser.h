#pragma once

#include <vector>
#include <memory>
#include <stdexcept>

#include "Token.h"
#include "AST.h"

class Parser {

private:

    std::vector<Token> tokens;
    int current;

    Token peek();
    Token advance();

    void expect(TokenType type);

    std::unique_ptr<ASTNode> statement();

    std::unique_ptr<ASTNode> expression();
    std::unique_ptr<ASTNode> term();
    std::unique_ptr<ASTNode> factor();

public:

    Parser(std::vector<Token> tokenList);

    std::unique_ptr<ASTNode> parse();
};