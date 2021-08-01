#include "OpenACCASTConstructor.h"
#include <iostream>
#include <regex>

extern OpenACCDirective *current_directive;
extern OpenACCDirective *parseOpenACC(std::string);

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
  std::ofstream output_file;

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
  // open the output file
  output_file.open(filename_string + ".output",
                   std::ios_base::out | std::ios_base::trunc);
  if (result) {
    std::cout << "No output file is available.\n";
    return -1;
  };

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

        OpenACCDirective *openACCAST = parseOpenACC(current_line);
        output_pragma = openACCAST->generatePragmaString();
        assert(output_pragma.size() != 0);

        std::cout << "GENERATED OUTPUT: " << output_pragma << "\n";
        std::cout << "======================================\n";
        output_file << output_pragma << "\n";
        processed_data[input_pragma] = output_pragma;
        is_fortran = false;
        input_pragma.clear();
        output_pragma.clear();
      }
    };
    current_char = input_file.peek();
  };

  std::cout << "=================== SUMMARY ===================\n";
  std::cout << "TOTAL TESTS  : " << total_amount << "\n";

  input_file.close();
  output_file.close();

  return 0;
}
