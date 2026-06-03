CXX = g++
CXXFLAGS = -std=c++17

SRC = \
src/main.cpp \
src/lexer/Lexer.cpp \
src/parser/Parser.cpp \
src/compiler/Compiler.cpp \
src/vm/VM.cpp \
src/tools/ASTPrinter.cpp \
src/tools/Disassembler.cpp

cvm:
	$(CXX) $(SRC) $(CXXFLAGS) -o cvm