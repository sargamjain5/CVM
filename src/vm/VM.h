#pragma once

#include <vector>
#include <unordered_map>

#include "../compiler/Bytecode.h"

class VM {

private:

    std::vector<int> stack;

    std::unordered_map<
        std::string,
        int
    > variables;

public:

    int execute(
        const std::vector<Instruction>& bytecode
    );
};