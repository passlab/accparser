#include "OpenACCASTConstructor.h"
#include "acclexer.h"
#include "accparser.h"
#include <antlr4-runtime.h>
#include <iostream>
#include <regex>

extern OpenACCDirective *current_directive;

extern std::vector<std::pair<std::string, int>> *
preProcess(std::ifstream &input_file);

static OpenACCDirective *generateOpenACCIR(std::string source) {

  antlr4::ANTLRInputStream input(source);
  acclexer lexer(&input);
  antlr4::CommonTokenStream tokens(&lexer);
  tokens.fill();
  accparser parser(&tokens);
  parser.setBuildParseTree(true);

  current_directive = NULL;
  antlr4::tree::ParseTree *tree = parser.acc();

  std::vector<antlr4::Token *> ts = tokens.getTokens();
  std::cout << "======================================\n";
  printf("TOKEN : TOKEN_STRING\n");
  for (antlr4::Token *t : ts) {
    std::cout << lexer.getVocabulary().getSymbolicName(t->getType()) << " : \""
              << t->getText() << "\"\n";
  }

  std::cout << "======================================\n";
  printf("PARSE TREE:\n");
  std::cout << tree->toStringTree(true) << std::endl;
  std::cout << "======================================\n";

  antlr4::tree::ParseTreeWalker *walker = new antlr4::tree::ParseTreeWalker();
  walker->walk(new OpenACCIRConstructor(), tree);
  assert(current_directive != NULL);

  return current_directive;
}

int openFile(std::ifstream &file, const char *filename) {
  file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
  try {
    file.open(filename);
  } catch (std::ifstream::failure const &) {
    std::cerr << "Exception caused by opening the given file\n";
    return -1;
  }

  return 0;
}

int main(int argc, char **argv) {

  const char *filename = NULL;
  int result = -1;
  if (argc > 1) {
    filename = argv[1];
  };
  std::ifstream input_file;

  if (filename != NULL) {
    result = openFile(input_file, filename);
  };
  if (result) {
    std::cout << "No testing file is available.\n";
    return -1;
  };

  std::string input_pragma;
  std::string output_pragma;

  std::string filename_string = std::string(filename);
  filename_string = filename_string.substr(filename_string.rfind("/") + 1);

  if (result) {
    std::cout << "No output file is available.\n";
    return -1;
  };

  std::vector<std::pair<std::string, int>> *acc_pragmas =
      preProcess(input_file);

  // parse the preprocessed inputs
  for (unsigned int i = 0; i < acc_pragmas->size(); i++) {
    input_pragma = acc_pragmas->at(i).first;
    std::cout << "======================================\n";
    std::cout << "Line: " << acc_pragmas->at(i).second << "\n";
    std::cout << "GIVEN INPUT: " << input_pragma << "\n";

    OpenACCDirective *openACCAST = generateOpenACCIR(input_pragma);
    output_pragma = openACCAST->generatePragmaString();
    assert(output_pragma.size() != 0);

    std::cout << "GENERATED OUTPUT: " << output_pragma << "\n";
    std::cout << "======================================\n";
    input_pragma.clear();
    output_pragma.clear();
  };

  input_file.close();

  return 0;
}
