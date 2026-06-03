#include "Disassembler.h"

#include <iostream>

const char* Disassembler::opcodeName(
    OpCode op
) {
    switch(op) {

        case OpCode::PUSH:
            return "PUSH";

        case OpCode::LOAD:
            return "LOAD";

        case OpCode::STORE:
            return "STORE";

        case OpCode::ADD:
            return "ADD";

        case OpCode::SUB:
            return "SUB";

        case OpCode::MUL:
            return "MUL";

        case OpCode::DIV:
            return "DIV";

        case OpCode::GT:
            return "GT";

        case OpCode::LT:
            return "LT";

        case OpCode::GTE:
            return "GTE";

        case OpCode::LTE:
            return "LTE";

        case OpCode::EQ:
            return "EQ";

        case OpCode::NEQ:
            return "NEQ";

        case OpCode::JMP:
            return "JMP";

        case OpCode::JMP_IF_FALSE:
            return "JMP_IF_FALSE";

        case OpCode::PRINT:
            return "PRINT";

        default:
            return "UNKNOWN";
    }
}

void Disassembler::print(
    const std::vector<Instruction>& bytecode
) {

    std::cout
        << "===== BYTECODE ====="
        << std::endl;

    for(size_t i = 0;
        i < bytecode.size();
        i++)
    {
        const auto& inst =
            bytecode[i];

        std::cout
            << i
            << " "
            << opcodeName(inst.op);

        switch(inst.op) {

            case OpCode::PUSH:

                std::cout
                    << " "
                    << inst.operand;
                break;

            case OpCode::LOAD:

                std::cout
                    << " "
                    << inst.name;
                break;

            case OpCode::STORE:

                std::cout
                    << " "
                    << inst.name;
                break;

            case OpCode::JMP:

                std::cout
                    << " "
                    << inst.operand;
                break;

            case OpCode::JMP_IF_FALSE:

                std::cout
                    << " "
                    << inst.operand;
                break;

            default:
                break;
        }

        std::cout
            << std::endl;
    }
}