#include "VM.h"

#include <iostream>
#include <stdexcept>

int VM::execute(const std::vector<Instruction>& bytecode) {

    stack.clear();

    for(const auto& inst : bytecode) {

        switch(inst.op) {

            case OpCode::PUSH:

                stack.push_back(inst.operand);
                break;

            case OpCode::STORE: {

                if(stack.empty()) {
                    throw std::runtime_error(
                        "STORE on empty stack"
                    );
                }

                int value = stack.back();
                stack.pop_back();

                variables[inst.name] = value;

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

                int a = stack.back();
                stack.pop_back();

                stack.push_back(a / b);

                break;
            }
        }
    }

    if(stack.empty()) {
        return 0;
    }

    return stack.back();
}