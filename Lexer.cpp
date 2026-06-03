#include "Lexer.h"
#include <cctype>

Lexer::Lexer(std::string src)
    : source(src), pos(0) {}

std::vector<Token> Lexer::tokenize() {

    std::vector<Token> tokens;

    while(pos < source.size()) {

        char current = source[pos];

        // Skip spaces
        if(std::isspace(current)) {
            pos++;
            continue;
        }

        // Identifiers (x, y, total, count1)
        if(std::isalpha(current)) {

            std::string identifier;

            while(pos < source.size() &&
                std::isalnum(source[pos])) {

                identifier += source[pos];
                pos++;
            }

            if(identifier == "print") {

                tokens.push_back(
                    Token(TokenType::PRINT)
                );
            }
            else {

                tokens.push_back(
                    Token(
                        TokenType::IDENTIFIER,
                        identifier
                    )
                );
            }

            continue;
        }

        // Numbers
        if(std::isdigit(current)) {

            std::string number;

            while(pos < source.size() &&
                  std::isdigit(source[pos])) {

                number += source[pos];
                pos++;
            }

            tokens.push_back(
                Token(
                    TokenType::NUMBER,
                    number
                )
            );

            continue;
        }

        switch(current) {

            case '+':
                tokens.push_back(
                    Token(TokenType::PLUS)
                );
                break;

            case '-':
                tokens.push_back(
                    Token(TokenType::MINUS)
                );
                break;

            case '*':
                tokens.push_back(
                    Token(TokenType::STAR)
                );
                break;

            case '/':
                tokens.push_back(
                    Token(TokenType::SLASH)
                );
                break;

            case '(':
                tokens.push_back(
                    Token(TokenType::LPAREN)
                );
                break;

            case ')':
                tokens.push_back(
                    Token(TokenType::RPAREN)
                );
                break;

            case '=':
                tokens.push_back(
                    Token(TokenType::ASSIGN)
                );
                break;

            case ';':
                tokens.push_back(
                    Token(TokenType::SEMICOLON)
                );
                break;

            default:
                break;
        }

        pos++;
    }

    tokens.push_back(
        Token(TokenType::END)
    );

    return tokens;
}