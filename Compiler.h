#pragma once

#include <vector>

#include "AST.h"
#include "Bytecode.h"

class Compiler {
private:
    std::vector<Instruction> instructions;

    void generate(ASTNode* node);

public:
    std::vector<Instruction> compile(ASTNode* root);
};