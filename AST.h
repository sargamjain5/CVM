#pragma once

#include <memory>
#include <vector>
#include <string>

class ASTNode {
public:
    virtual ~ASTNode() = default;
};

class NumberNode : public ASTNode {
public:
    int value;

    NumberNode(int v)
        : value(v) {}
};

class VariableNode : public ASTNode {
public:
    std::string name;

    VariableNode(const std::string& n)
        : name(n) {}
};

class AssignmentNode : public ASTNode {
public:
    std::string name;

    std::unique_ptr<ASTNode> value;

    AssignmentNode(
        const std::string& n,
        std::unique_ptr<ASTNode> val
    )
        : name(n),
          value(std::move(val)) {}
};

class BinaryOpNode : public ASTNode {
public:
    char op;

    std::unique_ptr<ASTNode> left;
    std::unique_ptr<ASTNode> right;

    BinaryOpNode(
        char operation,
        std::unique_ptr<ASTNode> l,
        std::unique_ptr<ASTNode> r
    )
        : op(operation),
          left(std::move(l)),
          right(std::move(r)) {}
};

class PrintNode : public ASTNode {
public:

    std::unique_ptr<ASTNode> expr;

    PrintNode(
        std::unique_ptr<ASTNode> e
    )
        : expr(std::move(e)) {}
};

class IfNode : public ASTNode {
public:

    std::unique_ptr<ASTNode> condition;

    std::vector<std::unique_ptr<ASTNode>> thenBody;

    std::vector<std::unique_ptr<ASTNode>> elseBody;

    IfNode(
        std::unique_ptr<ASTNode> cond
    )
        : condition(std::move(cond)) {}
};

class WhileNode : public ASTNode {
public:

    std::unique_ptr<ASTNode> condition;

    std::vector<std::unique_ptr<ASTNode>> body;

    WhileNode(
        std::unique_ptr<ASTNode> cond
    )
        : condition(std::move(cond)) {}
};
class ProgramNode : public ASTNode {
public:
    std::vector<std::unique_ptr<ASTNode>> statements;
};