#pragma once

#include <string>

enum class TokenType {

    NUMBER,

    IDENTIFIER,
    PRINT,
    IF,
    WHILE,
    ELSE,

    ASSIGN,

    EQUAL_EQUAL,
    NOT_EQUAL,

    GREATER,
    LESS,

    GREATER_EQUAL,
    LESS_EQUAL,

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