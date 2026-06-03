#pragma once

#include <vector>

#include "../compiler/Bytecode.h"

class Disassembler {

public:

    static void print(
        const std::vector<Instruction>& bytecode
    );

private:

    static const char* opcodeName(
        OpCode op
    );
};