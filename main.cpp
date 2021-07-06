#include <iostream>
#include <antlr4-runtime.h>
#include "acclexer.h"
#include "accparser.h"
#include "accir_constructor.h"

int main(int argc, char** argv) {

    std::ifstream stream;
    if (argc > 1) {
        stream.open(argv[1]);
    } else {
        std::cout << "Usage: main.out <path/filename>\n";
        return 0;
    }

    antlr4::ANTLRInputStream input(stream);
    acclexer lexer(&input);
    antlr4::CommonTokenStream tokens(&lexer);
    tokens.fill();
    accparser parser(&tokens);
    parser.setBuildParseTree(true);

    antlr4::tree::ParseTree* tree = parser.acc();

    std::cout << tree->toStringTree(true) << std::endl;

    antlr4::tree::ParseTreeWalker* walker = new antlr4::tree::ParseTreeWalker();
    walker->walk(new OpenACCIRConstructor(), tree);

    return 0;
}
