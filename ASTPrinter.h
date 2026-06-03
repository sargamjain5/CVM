#pragma once

#include <string>
#include "AST.h"

class ASTPrinter {

public:

    static void print(
        ASTNode* node,
        int indent = 0
    );

private:

    static void printIndent(
        int indent
    );
};