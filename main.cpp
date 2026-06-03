#include <iostream>
#include <fstream>
#include <sstream>

#include "Lexer.h"
#include "Parser.h"
#include "Compiler.h"
#include "VM.h"

using namespace std;

int main(int argc, char* argv[]) {

    if(argc != 2) {

        cout
            << "Usage: ./cvm <file.cvm>"
            << endl;

        return 1;
    }

    ifstream file(argv[1]);

    if(!file) {

        cout
            << "Cannot open file: "
            << argv[1]
            << endl;

        return 1;
    }

    stringstream buffer;
    buffer << file.rdbuf();

    string code = buffer.str();

    try {

        Lexer lexer(code);

        auto tokens =
            lexer.tokenize();

        Parser parser(tokens);

        auto ast =
            parser.parse();

        Compiler compiler;

        auto bytecode =
            compiler.compile(ast.get());

        VM vm;

        vm.execute(bytecode);
    }
    catch(const exception& e) {

        cerr
            << "Runtime Error: "
            << e.what()
            << endl;

        return 1;
    }

    return 0;
}