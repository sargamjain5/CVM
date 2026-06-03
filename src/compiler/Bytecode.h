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

    GT,
    LT,
    GTE,
    LTE,

    EQ,
    NEQ,

    JMP,
    JMP_IF_FALSE,

    PRINT
};

struct Instruction {

    OpCode op;

    int operand;
    std::string name;

    Instruction(OpCode opcode, int value = 0)
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
};