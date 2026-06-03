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

    if(auto program = dynamic_cast<ProgramNode*>(node)) {

        for(auto& stmt : program->statements) {
            generate(stmt.get());
        }

        return;
    }

    if(auto num = dynamic_cast<NumberNode*>(node)) {

        instructions.push_back(
            Instruction(OpCode::PUSH, num->value)
        );

        return;
    }

    if(auto var = dynamic_cast<VariableNode*>(node)) {

        instructions.push_back(
            Instruction(OpCode::LOAD, var->name)
        );

        return;
    }

    if(auto printNode =
        dynamic_cast<PrintNode*>(node))
    {
        generate(printNode->expr.get());

        instructions.push_back(
            Instruction(OpCode::PRINT)
        );

        return;
    }

    if(auto assign =
        dynamic_cast<AssignmentNode*>(node))
    {
        generate(assign->value.get());

        instructions.push_back(
            Instruction(
                OpCode::STORE,
                assign->name
            )
        );

        return;
    }

    // IF SUPPORT
    if(auto ifNode =
        dynamic_cast<IfNode*>(node))
    {
        generate(
            ifNode->condition.get()
        );

        int jumpIndex =
            instructions.size();

        instructions.push_back(
            Instruction(
                OpCode::JMP_IF_FALSE,
                0
            )
        );

        for(auto& stmt : ifNode->body) {
            generate(stmt.get());
        }

        instructions[jumpIndex].operand =
            instructions.size();

        return;
    }

    // WHILE SUPPORT
    if(auto whileNode =
        dynamic_cast<WhileNode*>(node))
    {
        int loopStart =
            instructions.size();

        generate(
            whileNode->condition.get()
        );

        int jumpFalse =
            instructions.size();

        instructions.push_back(
            Instruction(
                OpCode::JMP_IF_FALSE,
                0
            )
        );

        for(auto& stmt :
            whileNode->body)
        {
            generate(stmt.get());
        }

        instructions.push_back(
            Instruction(
                OpCode::JMP,
                loopStart
            )
        );

        instructions[jumpFalse].operand =
            instructions.size();

        return;
    }

    if(auto bin =
        dynamic_cast<BinaryOpNode*>(node))
    {
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

            case '>':
                instructions.push_back(
                    Instruction(OpCode::GT)
                );
                break;

            case '<':
                instructions.push_back(
                    Instruction(OpCode::LT)
                );
                break;

            case '=':
                instructions.push_back(
                    Instruction(OpCode::EQ)
                );
                break;
        }

        return;
    }
}