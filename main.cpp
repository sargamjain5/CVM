#include <iostream>

#include "Lexer.h"
#include "Parser.h"
#include "Compiler.h"
#include "VM.h"

using namespace std;

int main() {

    string code =
        "x=10;"
        "y=20;"
        "print(x+y);"
        "print(x*y);";

    try {

        Lexer lexer(code);

        auto tokens = lexer.tokenize();

        Parser parser(tokens);

        auto ast = parser.parse();

        Compiler compiler;

        auto bytecode = compiler.compile(ast.get());

        VM vm;

        int result = vm.execute(bytecode);

        cout << "Result = "
             << result
             << endl;
    }
    catch(const exception& e) {

        cout << "Error: "
             << e.what()
             << endl;
    }

    return 0;
}