#include "OpenACCIR.h"
#include "OpenMPTranslator.h"
#include <iostream>

OpenMPDirective *convertParallelLoop(OpenACCDirective *openacc_directive) {

  OpenMPDirective *result =
      new OpenMPDirective(OMPD_target_parallel_for);

  //convertClauses(openacc_directive, result);

  return result;
}

/*
void *convertClauses(OpenACCDirective *openacc_directive, OpenMPDirective *openmp_directive) {

  OpenMPDirective *result =
      new OpenMPDirective(OMPD_target_parallel_for);
  std::vector<OpenMPClause*>* all_clauses = current_OpenMPIR_to_SageIII.second->getClausesInOriginalOrder();
  std::vector<OpenMPClause*>::iterator clause_iter;
  for (clause_iter = all_clauses->begin(); clause_iter != all_clauses->end(); clause_iter++) {
      clause_kind = (*clause_iter)->getKind();
      switch (clause_kind) {
          case ACCC_num_workers:


  return result;
}
*/

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
