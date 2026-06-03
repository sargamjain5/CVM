# CVM++ Architecture

## Overview

CVM++ is a custom programming language and virtual machine built in C++. The project demonstrates the complete compilation and execution pipeline from source code to runtime execution.

```text
Source Code
    ↓
Lexer
    ↓
Tokens
    ↓
Parser
    ↓
Abstract Syntax Tree (AST)
    ↓
Compiler
    ↓
Bytecode
    ↓
Virtual Machine
    ↓
Execution
```

## Components

### Lexer

The lexer converts raw source code into a stream of tokens.

Example:

```c
x = 10 + 20;
```

Produces:

```text
IDENTIFIER(x)
ASSIGN
NUMBER(10)
PLUS
NUMBER(20)
SEMICOLON
```

### Parser

The parser uses recursive descent parsing to build an Abstract Syntax Tree (AST).

Example:

```c
print(10 + 20);
```

Produces:

```text
Print
 └── BinaryOp(+)
     ├── Number(10)
     └── Number(20)
```

### Compiler

The compiler traverses the AST and generates stack-based bytecode instructions.

Example:

```text
PUSH 10
PUSH 20
ADD
PRINT
```

### Virtual Machine

The VM executes bytecode instructions using:

- Operand Stack
- Variable Table
- Instruction Pointer

The VM supports:

- Arithmetic Operations
- Comparisons
- Conditional Execution
- Loops
- Variables

## Current Language Features

- Variables
- Arithmetic Expressions
- Comparisons
- print()
- if
- if-else
- while

## Future Enhancements

- Functions
- Return Statements
- Boolean Operators
- Strings
- Arrays
- For Loops
- Optimizations