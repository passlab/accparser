#include "OpenACCIR.h"
#include "OpenMPTranslator.h"
#include <iostream>

OpenMPDirective *convertParallelLoop(OpenACCDirective *openacc_directive) {

  OpenMPDirective *result =
      new OpenMPDirective(OMPD_target_parallel_for);

  return result;
}

OpenMPDirective * generateOpenMP(OpenACCDirective *openacc_directive) {

  OpenACCDirectiveKind kind = openacc_directive->getKind();
  OpenMPDirective *result = NULL;
  switch (kind) {
  case ACCD_parallel_loop:
    result = convertParallelLoop(openacc_directive);
    break;
  default:
    std::cout << "Unsupported OpenACC directive!\n";
    assert(0);
  }

  assert(result != NULL);

  return result;
}
