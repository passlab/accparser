#include "OpenACCASTConstructor.h"
#include "OpenMPIR.h"
#include "OpenMPTranslator.h"
#include "acclexer.h"
#include "accparser.h"
#include <antlr4-runtime.h>

extern OpenACCDirective *current_directive;

OpenMPDirective *parseOpenACCtoOpenMP(std::string source) {

  antlr4::ANTLRInputStream input(source);
  acclexer lexer(&input);
  antlr4::CommonTokenStream tokens(&lexer);
  tokens.fill();
  accparser parser(&tokens);
  parser.setBuildParseTree(true);

  current_directive = NULL;
  antlr4::tree::ParseTree *tree = parser.acc();

  std::cout << tree->toStringTree(true) << std::endl;

  antlr4::tree::ParseTreeWalker *walker = new antlr4::tree::ParseTreeWalker();
  walker->walk(new OpenACCIRConstructor(), tree);

  std::cout << current_directive->generatePragmaString() << "\n";

  OpenMPDirective *omp_directive = generateOpenMP(current_directive);
  assert(omp_directive != NULL);
  std::cout << omp_directive->generatePragmaString() << "\n";

  return omp_directive;
}
