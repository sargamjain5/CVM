#include <iostream>
#include <fstream>
#include <sstream>

#include "Lexer.h"
#include "Parser.h"
#include "Compiler.h"
#include "VM.h"
#include "ASTPrinter.h"
#include "Disassembler.h"

using namespace std;

int main(int argc, char* argv[]) {

    // REPL MODE
    if(argc == 1) {

        cout
            << "CVM++ REPL\n"
            << "Type 'exit' to quit.\n";

        VM vm;

        while(true) {

            cout << "\n>> ";

            string code;

            getline(cin, code);

            if(code == "exit") {
                break;
            }

            if(code.empty()) {
                continue;
            }

            try {

                Lexer lexer(code);

                auto tokens =
                    lexer.tokenize();

                Parser parser(tokens);

                auto ast =
                    parser.parse();

                Compiler compiler;

                auto bytecode =
                    compiler.compile(
                        ast.get()
                    );

                vm.execute(
                    bytecode
                );
            }
            catch(
                const exception& e
            )
            {
                cout
                    << "Error: "
                    << e.what()
                    << endl;
            }
        }

        return 0;
    }

    bool showAST = false;
    bool showBytecode = false;

    string filename;

    if(argc == 2) {

        filename = argv[1];
    }
    else if(argc == 3) {

        string option = argv[1];

        if(option == "--ast") {

            showAST = true;
        }
        else if(option == "--bytecode") {

            showBytecode = true;
        }
        else {

            cout
                << "Usage:\n"
                << "./cvm <file.cvm>\n"
                << "./cvm --ast <file.cvm>\n"
                << "./cvm --bytecode <file.cvm>"
                << endl;

            return 1;
        }

        filename = argv[2];
    }
    else {

        cout
            << "Usage:\n"
            << "./cvm <file.cvm>\n"
            << "./cvm --ast <file.cvm>\n"
            << "./cvm --bytecode <file.cvm>"
            << endl;

        return 1;
    }

    ifstream file(filename);

    if(!file) {

        cout
            << "Cannot open file: "
            << filename
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

        if(showAST) {

            ASTPrinter::print(
                ast.get()
            );

            return 0;
        }

        Compiler compiler;

        auto bytecode =
            compiler.compile(
                ast.get()
            );

        if(showBytecode) {

            Disassembler::print(
                bytecode
            );

            return 0;
        }

        VM vm;

        vm.execute(
            bytecode
        );
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