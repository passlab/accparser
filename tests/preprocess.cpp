#include <fstream>
#include <iostream>
#include <regex>

std::vector<std::pair<std::string, int>> *preProcess(std::ifstream &);

std::vector<std::pair<std::string, int>> *
preProcess(std::ifstream &input_file) {

  std::string input_pragma;
  int total_amount = 0;
  int line_no = 0;
  std::vector<std::pair<std::string, int>> *acc_pragmas =
      new std::vector<std::pair<std::string, int>>();

  char current_char = input_file.peek();
  std::string current_line;
  std::regex c_regex(
      "^([[:blank:]]*#pragma)([[:blank:]]+)(acc)[[:blank:]]+(.*)");
  std::regex fortran_regex(
      "^([[:blank:]]*[!c*][$][Aa][Cc][Cc])[[:blank:]]+(.*)");
  std::regex comment_regex("[/][*]([^*]|[*][^/])*[*][/]");
  std::regex continue_regex("([\\\\]+[[:blank:]]*$)");

  while (!input_file.eof()) {
    line_no += 1;
    int step = 0;
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
          step += 1;
        };
        input_pragma += current_line;
        total_amount += 1;
        if (std::regex_match(current_line, fortran_regex) == true) {
          std::locale loc;
          for (unsigned int i = 0; i < input_pragma.size(); i++) {
            std::tolower(input_pragma[i], loc);
          }
        }
        acc_pragmas->push_back(std::make_pair(input_pragma, line_no));
        line_no += step;
        step = 0;
      }
    };
    current_char = input_file.peek();
  };

  return acc_pragmas;
}
