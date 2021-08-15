#include <fstream>
#include <iostream>
#include <regex>

std::vector<std::string> *preProcess(std::ifstream &);

std::vector<std::string> *preProcess(std::ifstream &input_file) {

  std::string input_pragma;
  int total_amount = 0;
  int line_no = 0;
  std::vector<std::string> *acc_pragmas = new std::vector<std::string>();

  char current_char = input_file.peek();
  std::string current_line;
  std::regex c_regex(
      "^([[:blank:]]*#pragma)([[:blank:]]+)(acc)[[:blank:]]+(.*)");
  std::regex fortran_regex("^([[:blank:]]*[!c*][$][Aa][Cc][Cc])[[:blank:]]+(.*)");
  std::regex comment_regex("[/][*]([^*]|[*][^/])*[*][/]");
  std::regex continue_regex("([\\\\]+[[:blank:]]*$)");

  while (!input_file.eof()) {
    line_no += 1;
    switch (current_char) {
    case '\n':
      input_file.seekg(1, std::ios_base::cur);
      break;
    default:
      std::getline(input_file, current_line);
      // remove the inline comments
      current_line = std::regex_replace(current_line, comment_regex, "");
      input_pragma = "";
      if (std::regex_match(current_line, c_regex) ||
          std::regex_match(current_line, fortran_regex)) {
        // combine continuous lines if necessary
        while (std::regex_search(current_line, continue_regex)) {
          // remove the slash part at the end
          current_line = std::regex_replace(current_line, continue_regex, "");
          // add the current line to the pragma string
          input_pragma += current_line;
          // get the next line
          std::getline(input_file, current_line);
          // remove the inline comments of next line
          current_line = std::regex_replace(current_line, comment_regex, "");
        };
        input_pragma += current_line;
        total_amount += 1;
        acc_pragmas->push_back(input_pragma);
      }
    };
    current_char = input_file.peek();
  };

  return acc_pragmas;
}
