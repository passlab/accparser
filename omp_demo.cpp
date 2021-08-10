#include "OpenMPIR.h"
#include <iostream>

extern OpenMPDirective *parseOpenACCtoOpenMP(std::string);

int main(int argc, char **argv) {

  std::string input = "#pragma acc parallel loop num_workers(6) collapse(2) "
                      "copyin(a[0:N], b[0:N]) copyout(c[0:N])";
  OpenMPDirective *result = parseOpenACCtoOpenMP(input.c_str());
  std::cout << result->generatePragmaString() << "\n";

  return 0;
}
