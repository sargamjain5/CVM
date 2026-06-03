# AST Example

This document demonstrates how CVM++ source code is represented as an Abstract Syntax Tree (AST).

## Source Code

```c
x = 10;

if(x >= 5){
    print(100);
}
else{
    print(200);
}
```

## Generated AST

```text
Program
├── Assignment(x)
│   └── Number(10)
│
└── If
    ├── Condition
    │   └── BinaryOp(>=)
    │       ├── Variable(x)
    │       └── Number(5)
    │
    ├── Then
    │   └── Print
    │       └── Number(100)
    │
    └── Else
        └── Print
            └── Number(200)
```

## AST Node Types

### NumberNode

Represents numeric literals.

```text
Number(10)
```

### VariableNode

Represents variable references.

```text
Variable(x)
```

### BinaryOpNode

Represents arithmetic or comparison expressions.

```text
BinaryOp(+)
BinaryOp(>=)
BinaryOp(==)
```

### AssignmentNode

Represents variable assignment.

```text
Assignment(x)
```

### PrintNode

Represents print statements.

```text
Print
```

### IfNode

Represents conditional execution.

```text
If
```

### WhileNode

Represents loops.

```text
While
```