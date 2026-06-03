#include <iostream>

#include "Lexer.h"
#include "Parser.h"
#include "Compiler.h"
#include "VM.h"

using namespace std;

int main() {


    string code =
        "x=0;"
        "while(x<5){"
        "print(x);"
        "x=x+1;"
        "}";

    try {

        Lexer lexer(code);

        auto tokens = lexer.tokenize();

        Parser parser(tokens);

        auto ast = parser.parse();

        Compiler compiler;

        auto bytecode = compiler.compile(ast.get());

        VM vm;

        vm.execute(bytecode);
    }
    catch(const exception& e) {

        cout << "Error: "
             << e.what()
             << endl;
    }

    return 0;
}