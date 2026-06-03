#pragma once

#include <string>

enum class TokenType {

    NUMBER,

    IDENTIFIER,
    PRINT,

    ASSIGN,

    PLUS,
    MINUS,
    STAR,
    SLASH,

    LPAREN,
    RPAREN,

    SEMICOLON,

    END
};

struct Token {

    TokenType type;
    std::string value;

    Token(TokenType t, std::string v = "")
        : type(t), value(v) {}
};