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

  std::vector<OpenMPDirective *> *current_directives =
      generateOpenMP(current_directive);

  assert(current_directives != NULL);
  for (size_t i = 0; i < current_directives->size(); i++)
    std::cout << current_directives->at(i)->generatePragmaString() << "\n";

  return current_directives->at(0);
}
