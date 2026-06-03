#pragma once

#include <string>

enum class TokenType {

    NUMBER,

    IDENTIFIER,
    PRINT,
    IF,
    WHILE,

    ASSIGN,
    EQUAL_EQUAL,

    GREATER,
    LESS,

    PLUS,
    MINUS,
    STAR,
    SLASH,

    LPAREN,
    RPAREN,

    LBRACE,
    RBRACE,

    SEMICOLON,

    END
};

struct Token {

    TokenType type;
    std::string value;

    Token(TokenType t, std::string v = "")
        : type(t), value(v) {}
};