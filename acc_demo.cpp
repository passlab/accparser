#include "OpenACCASTConstructor.h"
#include "acclexer.h"
#include "accparser.h"
#include <antlr4-runtime.h>
#include <iostream>
#include <regex>

extern OpenACCDirective *current_directive;

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
    printf("%s : \"%s\"\n",
           lexer.getVocabulary().getSymbolicName(t->getType()).c_str(),
           t->getText().c_str());
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
  int result;
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
  std::map<std::string, std::string> processed_data;
  int total_amount = 0;
  int line_no = 0;
  int current_pragma_line_no = 1;

  char current_char = input_file.peek();
  std::string current_line;
  std::regex fortran_regex("[!c][$][Aa][Cc][Cc]");
  bool is_fortran = false;

  std::string filename_string = std::string(filename);
  filename_string = filename_string.substr(filename_string.rfind("/") + 1);

  while (!input_file.eof()) {
    line_no += 1;
    switch (current_char) {
    case '\n':
      input_file.seekg(1, std::ios_base::cur);
      break;
    default:
      std::getline(input_file, current_line);
      current_line = std::regex_replace(current_line, std::regex("^\\s+"),
                                        std::string(""));
      if (std::regex_match(current_line.substr(0, 5), fortran_regex)) {
        is_fortran = true;
      };
      if (current_line.substr(0, 7) == "#pragma" || is_fortran) {
        total_amount += 1;
        current_pragma_line_no = line_no;
        input_pragma = current_line;
        auto search_pragma = processed_data.find(input_pragma);
        if (search_pragma != processed_data.end()) {
          output_pragma = processed_data[input_pragma];
          break;
        };

        std::cout << "======================================\n";
        std::cout << "Line: " << current_pragma_line_no << "\n";
        std::cout << "GIVEN INPUT: " << input_pragma << "\n";

        OpenACCDirective *openACCAST = generateOpenACCIR(current_line);
        output_pragma = openACCAST->generatePragmaString();
        assert(output_pragma.size() != 0);

        std::cout << "GENERATED OUTPUT: " << output_pragma << "\n";
        std::cout << "======================================\n";
        processed_data[input_pragma] = output_pragma;
        is_fortran = false;
        input_pragma.clear();
        output_pragma.clear();
      }
    };
    current_char = input_file.peek();
  };

  input_file.close();

  return 0;
}
