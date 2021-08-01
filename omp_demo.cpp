#include "OpenMPIR.h"
#include <iostream>

extern OpenMPDirective *parseOpenACCtoOpenMP(std::string);

int main(int argc, char **argv) {

  std::string input = "#pragma acc parallel loop gang worker";
  OpenMPDirective *result = parseOpenACCtoOpenMP(input.c_str());
  std::cout << result->generatePragmaString() << "\n";

  return 0;
}
