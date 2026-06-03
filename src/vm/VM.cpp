#include "VM.h"

#include <iostream>
#include <stdexcept>

int VM::execute(
    const std::vector<Instruction>& bytecode)
{
    if(bytecode.empty()) {
        return 0;
    }

    size_t ip = 0;

    while(ip < bytecode.size()) {

        const auto& inst =
            bytecode[ip];

        switch(inst.op) {

            case OpCode::PUSH: {

                stack.push_back(
                    inst.operand
                );

                break;
            }

            case OpCode::STORE: {

                if(stack.empty()) {
                    throw std::runtime_error(
                        "STORE on empty stack"
                    );
                }

                int value =
                    stack.back();

                stack.pop_back();

                variables[inst.name] =
                    value;

                break;
            }

            case OpCode::LOAD: {

                if(variables.find(inst.name)
                   == variables.end())
                {
                    throw std::runtime_error(
                        "Undefined variable: "
                        + inst.name
                    );
                }

                stack.push_back(
                    variables[inst.name]
                );

                break;
            }

            case OpCode::ADD: {

                int b = stack.back();
                stack.pop_back();

                int a = stack.back();
                stack.pop_back();

                stack.push_back(a + b);

                break;
            }

            case OpCode::SUB: {

                int b = stack.back();
                stack.pop_back();

                int a = stack.back();
                stack.pop_back();

                stack.push_back(a - b);

                break;
            }

            case OpCode::MUL: {

                int b = stack.back();
                stack.pop_back();

                int a = stack.back();
                stack.pop_back();

                stack.push_back(a * b);

                break;
            }

            case OpCode::DIV: {

                int b = stack.back();
                stack.pop_back();

                if(b == 0) {
                    throw std::runtime_error(
                        "Division by zero"
                    );
                }

                int a = stack.back();
                stack.pop_back();

                stack.push_back(a / b);

                break;
            }

            case OpCode::GT: {

                int b = stack.back();
                stack.pop_back();

                int a = stack.back();
                stack.pop_back();

                stack.push_back(a > b);

                break;
            }

            case OpCode::LT: {

                int b = stack.back();
                stack.pop_back();

                int a = stack.back();
                stack.pop_back();

                stack.push_back(a < b);

                break;
            }

            case OpCode::GTE: {

                int b = stack.back();
                stack.pop_back();

                int a = stack.back();
                stack.pop_back();

                stack.push_back(a >= b);

                break;
            }

            case OpCode::LTE: {

                int b = stack.back();
                stack.pop_back();

                int a = stack.back();
                stack.pop_back();

                stack.push_back(a <= b);

                break;
            }

            case OpCode::EQ: {

                int b = stack.back();
                stack.pop_back();

                int a = stack.back();
                stack.pop_back();

                stack.push_back(a == b);

                break;
            }

            case OpCode::NEQ: {

                int b = stack.back();
                stack.pop_back();

                int a = stack.back();
                stack.pop_back();

                stack.push_back(a != b);

                break;
            }

            case OpCode::JMP: {

                ip = inst.operand;

                continue;
            }

            case OpCode::JMP_IF_FALSE: {

                if(stack.empty()) {
                    throw std::runtime_error(
                        "JMP_IF_FALSE on empty stack"
                    );
                }

                int condition =
                    stack.back();

                stack.pop_back();

                if(!condition) {

                    ip = inst.operand;

                    continue;
                }

                break;
            }

            case OpCode::PRINT: {

                if(stack.empty()) {
                    throw std::runtime_error(
                        "PRINT on empty stack"
                    );
                }

                std::cout
                    << stack.back()
                    << std::endl;

                break;
            }
        }

        ip++;
    }

    return 0;
}