#include "Compiler.h"

std::vector<Instruction> Compiler::compile(ASTNode* root) {

    instructions.clear();

    generate(root);

    return instructions;
}

void Compiler::generate(ASTNode* node) {

    if(node == nullptr) {
        return;
    }

    // Program
    if(auto program = dynamic_cast<ProgramNode*>(node)) {

        for(auto& stmt : program->statements) {
            generate(stmt.get());
        }

        return;
    }

    // Number
    if(auto num = dynamic_cast<NumberNode*>(node)) {

        instructions.push_back(
            Instruction(OpCode::PUSH, num->value)
        );

        return;
    }

    // Variable
    if(auto var = dynamic_cast<VariableNode*>(node)) {

        instructions.push_back(
            Instruction(OpCode::LOAD, var->name)
        );

        return;
    }

    if(auto printNode =
        dynamic_cast<PrintNode*>(node))
    {
        generate(
            printNode->expr.get()
        );

        instructions.push_back(
            Instruction(OpCode::PRINT)
        );

        return;
    }

    // Assignment
    if(auto assign = dynamic_cast<AssignmentNode*>(node)) {

        generate(assign->value.get());

        instructions.push_back(
            Instruction(
                OpCode::STORE,
                assign->name
            )
        );

        return;
    }

    // Binary Operation
    if(auto bin = dynamic_cast<BinaryOpNode*>(node)) {

        generate(bin->left.get());
        generate(bin->right.get());

        switch(bin->op) {

            case '+':
                instructions.push_back(
                    Instruction(OpCode::ADD)
                );
                break;

            case '-':
                instructions.push_back(
                    Instruction(OpCode::SUB)
                );
                break;

            case '*':
                instructions.push_back(
                    Instruction(OpCode::MUL)
                );
                break;

            case '/':
                instructions.push_back(
                    Instruction(OpCode::DIV)
                );
                break;
        }

        return;
    }
}