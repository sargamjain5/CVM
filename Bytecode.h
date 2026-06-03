#pragma once

#include <string>

enum class OpCode {

    PUSH,

    LOAD,
    STORE,

    ADD,
    SUB,
    MUL,
    DIV,

    PRINT
};

struct Instruction {

    OpCode op;

    int operand;
    std::string name;

    Instruction(OpCode opcode, int value)
        : op(opcode),
          operand(value),
          name("") {}

    Instruction(
        OpCode opcode,
        const std::string& variableName
    )
        : op(opcode),
          operand(0),
          name(variableName) {}

    Instruction(OpCode opcode)
        : op(opcode),
          operand(0),
          name("") {}
};