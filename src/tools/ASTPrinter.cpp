#include "ASTPrinter.h"

#include <iostream>

void ASTPrinter::printIndent(
    int indent
) {
    for(int i = 0; i < indent; i++) {
        std::cout << "  ";
    }
}

void ASTPrinter::print(
    ASTNode* node,
    int indent
) {

    if(node == nullptr)
        return;

    if(auto program =
        dynamic_cast<ProgramNode*>(node))
    {
        printIndent(indent);
        std::cout
            << "Program"
            << std::endl;

        for(auto& stmt :
            program->statements)
        {
            print(
                stmt.get(),
                indent + 1
            );
        }

        return;
    }

    if(auto num =
        dynamic_cast<NumberNode*>(node))
    {
        printIndent(indent);

        std::cout
            << "Number("
            << num->value
            << ")"
            << std::endl;

        return;
    }

    if(auto var =
        dynamic_cast<VariableNode*>(node))
    {
        printIndent(indent);

        std::cout
            << "Variable("
            << var->name
            << ")"
            << std::endl;

        return;
    }

    if(auto assign =
        dynamic_cast<AssignmentNode*>(node))
    {
        printIndent(indent);

        std::cout
            << "Assignment("
            << assign->name
            << ")"
            << std::endl;

        print(
            assign->value.get(),
            indent + 1
        );

        return;
    }

    if(auto printNode =
        dynamic_cast<PrintNode*>(node))
    {
        printIndent(indent);

        std::cout
            << "Print"
            << std::endl;

        print(
            printNode->expr.get(),
            indent + 1
        );

        return;
    }

    if(auto ifNode =
        dynamic_cast<IfNode*>(node))
    {
        printIndent(indent);

        std::cout
            << "If"
            << std::endl;

        printIndent(indent + 1);

        std::cout
            << "Condition"
            << std::endl;

        print(
            ifNode->condition.get(),
            indent + 2
        );

        printIndent(indent + 1);

        std::cout
            << "Then"
            << std::endl;

        for(auto& stmt :
            ifNode->thenBody)
        {
            print(
                stmt.get(),
                indent + 2
            );
        }

        if(!ifNode->elseBody.empty()) {

            printIndent(indent + 1);

            std::cout
                << "Else"
                << std::endl;

            for(auto& stmt :
                ifNode->elseBody)
            {
                print(
                    stmt.get(),
                    indent + 2
                );
            }
        }

        return;
    }

    if(auto whileNode =
        dynamic_cast<WhileNode*>(node))
    {
        printIndent(indent);

        std::cout
            << "While"
            << std::endl;

        print(
            whileNode->condition.get(),
            indent + 1
        );

        for(auto& stmt :
            whileNode->body)
        {
            print(
                stmt.get(),
                indent + 1
            );
        }

        return;
    }

    if(auto bin =
        dynamic_cast<BinaryOpNode*>(node))
    {
        printIndent(indent);

        std::cout
            << "BinaryOp("
            << bin->op
            << ")"
            << std::endl;

        print(
            bin->left.get(),
            indent + 1
        );

        print(
            bin->right.get(),
            indent + 1
        );

        return;
    }
}