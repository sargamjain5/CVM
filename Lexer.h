#pragma once

#include <string>
#include <vector>
#include "Token.h"

class Lexer {
private:
    std::string source;
    int pos;

public:
    Lexer(std::string src);

    std::vector<Token> tokenize();
};