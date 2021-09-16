#include "OpenMPTranslator.h"
#include <iostream>

std::vector<OpenMPDirective *> *convertParallelLoop(OpenACCDirective *acc_directive) {

  std::vector<OpenMPDirective *> *current_directives = new std::vector<OpenMPDirective *>(); 
  OpenMPDirective *result = new OpenMPDirective(OMPD_target_parallel_for);
  
  current_directives->push_back(result);
  
  convertOpenACCClauses(acc_directive, current_directives);

  return current_directives;
}

void convertOpenACCClauses(OpenACCDirective *acc_directive,
                           std::vector<OpenMPDirective *> *current_directives) {
  OpenMPClause *omp_clause = NULL;
  OpenACCClauseKind clause_kind;
  std::vector<OpenACCClause *> *all_clauses =
      acc_directive->getClausesInOriginalOrder();
  std::vector<OpenACCClause *>::iterator clause_iter;
  for (clause_iter = all_clauses->begin(); clause_iter != all_clauses->end();
       clause_iter++) {
    clause_kind = (*clause_iter)->getKind();
    switch (clause_kind) {
    case ACCC_collapse: {
      omp_clause = current_directives->at(0)->addOpenMPClause(OMPC_collapse);
      std::string collapse = (*clause_iter)->expressionToString();
      char *omp_collapse = (char *)malloc(collapse.size() * sizeof(char) + 1);
      strcpy(omp_collapse, collapse.c_str());
      omp_collapse[collapse.size()] = '\0';
      omp_clause->addLangExpr(omp_collapse);
      break;
    }
    case ACCC_copyin: {
      omp_clause = current_directives->at(0)->addOpenMPClause(
          OMPC_map, OMPC_MAP_MODIFIER_unspecified,
          OMPC_MAP_MODIFIER_unspecified, OMPC_MAP_MODIFIER_unspecified,
          OMPC_MAP_TYPE_to, "");
      std::vector<std::string> *expressions = (*clause_iter)->getExpressions();
      for (unsigned int i = 0; i < expressions->size(); i++) {
        std::string expression = expressions->at(i);
        char *omp_expression =
            (char *)malloc(expression.size() * sizeof(char) + 1);
        strcpy(omp_expression, expression.c_str());
        omp_expression[expression.size()] = '\0';
        omp_clause->addLangExpr(omp_expression);
      };
      break;
    }
    case ACCC_copyout: {
      omp_clause = current_directives->at(0)->addOpenMPClause(
          OMPC_map, OMPC_MAP_MODIFIER_unspecified,
          OMPC_MAP_MODIFIER_unspecified, OMPC_MAP_MODIFIER_unspecified,
          OMPC_MAP_TYPE_from, "");
      std::vector<std::string> *expressions = (*clause_iter)->getExpressions();
      for (unsigned int i = 0; i < expressions->size(); i++) {
        std::string expression = expressions->at(i);
        char *omp_expression =
            (char *)malloc(expression.size() * sizeof(char) + 1);
        strcpy(omp_expression, expression.c_str());
        omp_expression[expression.size()] = '\0';
        omp_clause->addLangExpr(omp_expression);
      };
      break;
    }
    case ACCC_num_workers: {
      omp_clause = current_directives->at(0)->addOpenMPClause(OMPC_num_threads);
      std::string num_workers = (*clause_iter)->expressionToString();
      char *num_threads = (char *)malloc(num_workers.size() * sizeof(char) + 1);
      strcpy(num_threads, num_workers.c_str());
      num_threads[num_workers.size()] = '\0';
      omp_clause->addLangExpr(num_threads);
      break;
    }
    default:;
    }
  }
}

std::vector<OpenMPDirective *> *generateOpenMP(OpenACCDirective *acc_directive) {

  OpenACCDirectiveKind kind = acc_directive->getKind();
  std::vector<OpenMPDirective *> * result = new std::vector<OpenMPDirective *>();
  switch (kind) {
  case ACCD_parallel_loop:
    result = convertParallelLoop(acc_directive);
    break;
  default:
    std::cout << "Unsupported OpenACC directive!\n";
    assert(0);
  }

  assert(result != NULL);

  return result;
}
