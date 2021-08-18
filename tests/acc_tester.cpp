#include "OpenACCASTConstructor.h"
#include <iostream>
#include <regex>

extern OpenACCDirective *current_directive;
extern OpenACCDirective *parseOpenACC(std::string);
extern std::vector<std::string> *preProcess(std::ifstream &input_file);

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

void savePragmaList(std::vector<OpenACCDirective *> *acc_ast_list,
                    std::string filename) {

  std::string output_filename = filename + ".output";
  std::ofstream output_file(output_filename.c_str(), std::ofstream::trunc);

  if (acc_ast_list != NULL) {
    for (unsigned int i = 0; i < acc_ast_list->size(); i++) {
      if (acc_ast_list->at(i) != NULL) {
        output_file << acc_ast_list->at(i)->generatePragmaString() << std::endl;
      } else {
        output_file << "NULL" << std::endl;
      };
    };
  };

  output_file.close();
}

int main(int argc, char **argv) {

  const char *filename = NULL;
  int result = 0;
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

  std::vector<OpenACCDirective *> *acc_ast_list =
      new std::vector<OpenACCDirective *>();
  OpenACCDirective *acc_ast = NULL;

  std::string filename_string = std::string(filename);
  filename_string = filename_string.substr(filename_string.rfind("/") + 1);

  if (result) {
    std::cout << "No output file is available.\n";
    return -1;
  };

  std::vector<std::string> *acc_pragmas = preProcess(input_file);

  // parse the preprocessed inputs
  for (unsigned int i = 0; i < acc_pragmas->size(); i++) {
    acc_ast = parseOpenACC(acc_pragmas->at(i));
    acc_ast_list->push_back(acc_ast);
  };

  savePragmaList(acc_ast_list, filename_string);

  input_file.close();

  return 0;
}
