#include "OpenMPTranslator.h"
#include <iostream>

std::vector<OpenMPDirective *> *convertParallelLoop(OpenACCDirective *acc_directive) {

  std::vector<OpenMPDirective *> *current_directives = new std::vector<OpenMPDirective *>(); 
  OpenMPDirective *result = new OpenMPDirective(OMPD_target_parallel_for);
  current_directives->push_back(result);
  convertOpenACCClauses(acc_directive, current_directives);
  return current_directives;
}

std::vector<OpenMPDirective *> *convertParallel(OpenACCDirective *acc_directive) {
  std::vector<OpenMPDirective *> *current_directives = new std::vector<OpenMPDirective *>(); 
  OpenMPDirective *result = new OpenMPDirective(OMPD_target_parallel);
  current_directives->push_back(result);
  convertOpenACCClauses(acc_directive, current_directives);
  return current_directives;
}

std::vector<OpenMPDirective *> *convertLoop(OpenACCDirective *acc_directive) {

  std::vector<OpenMPDirective *> *current_directives = new std::vector<OpenMPDirective *>(); 
  OpenMPDirective *result = new OpenMPDirective(OMPD_target_parallel_loop);
  current_directives->push_back(result);
  convertOpenACCClauses(acc_directive, current_directives);
  return current_directives;
}

std::vector<OpenMPDirective *> *convertSerial(OpenACCDirective *acc_directive) {

  std::vector<OpenMPDirective *> *current_directives = new std::vector<OpenMPDirective *>(); 
  OpenMPDirective *result = new OpenMPDirective(OMPD_target);
  current_directives->push_back(result);
  convertOpenACCClauses(acc_directive, current_directives);
  return current_directives;
}

std::vector<OpenMPDirective *> *convertData(OpenACCDirective *acc_directive) {
  std::vector<OpenMPDirective *> *current_directives = new std::vector<OpenMPDirective *>();
  OpenMPDirective *result = new OpenMPDirective(OMPD_target_data);
  current_directives->push_back(result);
  convertOpenACCClauses(acc_directive, current_directives);
  return current_directives;
}

std::vector<OpenMPDirective *> *convertEnterData(OpenACCDirective *acc_directive) {
  std::vector<OpenMPDirective *> *current_directives = new std::vector<OpenMPDirective *>();
  OpenMPDirective *result = new OpenMPDirective(OMPD_target_enter_data);
  current_directives->push_back(result);
  convertOpenACCClauses(acc_directive, current_directives);
  return current_directives;
}

std::vector<OpenMPDirective *> *convertExitData(OpenACCDirective *acc_directive) {
  std::vector<OpenMPDirective *> *current_directives = new std::vector<OpenMPDirective *>();
  OpenMPDirective *result = new OpenMPDirective(OMPD_target_exit_data);
  current_directives->push_back(result);
  convertOpenACCClauses(acc_directive, current_directives);
  return current_directives;
}

std::vector<OpenMPDirective *> *convertKernels(OpenACCDirective *acc_directive) {

  std::vector<OpenMPDirective *> *current_directives = new std::vector<OpenMPDirective *>(); 
  OpenMPDirective *result = new OpenMPDirective(OMPD_target_teams);
  current_directives->push_back(result);
  OpenMPDirective *result1 = new OpenMPDirective(OMPD_parallel);
  current_directives->push_back(result1);
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
    case ACCC_async: {
      omp_clause = current_directives->at(0)->addOpenMPClause(OMPC_depend, OMPC_DEPEND_MODIFIER_unspecified, OMPC_DEPENDENCE_TYPE_unknown);
      std::string async = (*clause_iter)->expressionToString();
      char *omp_depend = (char *)malloc(async.size() * sizeof(char) + 1);
      strcpy(omp_depend, async.c_str());
      omp_depend[async.size()] = '\0';
      omp_clause->addLangExpr(omp_depend);

      omp_clause = current_directives->at(0)->addOpenMPClause(OMPC_nowait);
      break;
    }
    case ACCC_if: {
      omp_clause = current_directives->at(0)->addOpenMPClause(OMPC_if, OMPC_IF_MODIFIER_unspecified);
      std::string acc_if = (*clause_iter)->expressionToString();
      char *omp_if = (char *)malloc(acc_if.size() * sizeof(char) + 1);
      strcpy(omp_if, acc_if.c_str());
      omp_if[acc_if.size()] = '\0';
      omp_clause->addLangExpr(omp_if);
      break;
    }
    case ACCC_wait: {
      omp_clause = current_directives->at(0)->addOpenMPClause(OMPC_depend, OMPC_DEPEND_MODIFIER_unspecified, OMPC_DEPENDENCE_TYPE_in);
      std::vector<std::string> *expressions = (*clause_iter)->getExpressions();
      for (unsigned int i = 0; i < expressions->size(); i++) {
        std::string expression = expressions->at(i);
        char *omp_expression =
            (char *)malloc(expression.size() * sizeof(char) + 1);
        strcpy(omp_expression, expression.c_str());
        omp_expression[expression.size()] = '\0';
        omp_clause->addLangExpr(omp_expression);
      };
      //This one should be incorrect, but it is correct now. I don't know why
      /*std::string wait = (*clause_iter)->expressionToString();
      char *omp_depend = (char *)malloc(wait.size() * sizeof(char) + 1);
      strcpy(omp_depend, wait.c_str());
      omp_depend[wait.size()] = '\0';
      omp_clause->addLangExpr(omp_depend);*/
      break;
    }
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
    case ACCC_reduction: {
      OpenACCReductionClauseOperator reduction_operator = ((OpenACCReductionClause *)(*clause_iter))->getOperator();
      OpenMPReductionClauseIdentifier omp_identifier = OMPC_REDUCTION_IDENTIFIER_unknown;
      switch (reduction_operator) {
        case ACCC_REDUCTION_add:
          omp_identifier = OMPC_REDUCTION_IDENTIFIER_plus;
          break;
        case ACCC_REDUCTION_mul:
          omp_identifier = OMPC_REDUCTION_IDENTIFIER_mul;
          break;
        case ACCC_REDUCTION_max:
          omp_identifier = OMPC_REDUCTION_IDENTIFIER_max;
          break;
        case ACCC_REDUCTION_min:
          omp_identifier = OMPC_REDUCTION_IDENTIFIER_min;
          break;
        case ACCC_REDUCTION_bitand:
          omp_identifier = OMPC_REDUCTION_IDENTIFIER_bitand;
          break;
        case ACCC_REDUCTION_bitor:
          omp_identifier = OMPC_REDUCTION_IDENTIFIER_bitor;
          break;
        case ACCC_REDUCTION_bitxor:
          omp_identifier = OMPC_REDUCTION_IDENTIFIER_bitxor;
          break;
        case ACCC_REDUCTION_logand:
          omp_identifier = OMPC_REDUCTION_IDENTIFIER_logand;
          break;
        case ACCC_REDUCTION_logor:
          omp_identifier = OMPC_REDUCTION_IDENTIFIER_logor;
          break;
        default:;
        };
      
      omp_clause = current_directives->at(0)->addOpenMPClause(OMPC_reduction, OMPC_REDUCTION_MODIFIER_unspecified, omp_identifier); 
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
      omp_clause = current_directives->at(1)->addOpenMPClause(OMPC_num_threads);
      std::string num_workers = (*clause_iter)->expressionToString();
      char *num_threads = (char *)malloc(num_workers.size() * sizeof(char) + 1);
      strcpy(num_threads, num_workers.c_str());
      num_threads[num_workers.size()] = '\0';
      omp_clause->addLangExpr(num_threads);
      break;
    }
    case ACCC_num_gangs: {
      omp_clause = current_directives->at(0)->addOpenMPClause(OMPC_num_teams);
      std::string num_gangs = (*clause_iter)->expressionToString();
      char *num_teams = (char *)malloc(num_gangs.size() * sizeof(char) + 1);
      strcpy(num_teams, num_gangs.c_str());
      num_teams[num_gangs.size()] = '\0';
      omp_clause->addLangExpr(num_teams);
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
  case ACCD_loop:
    result = convertLoop(acc_directive);
    break;
  case ACCD_parallel:
    result = convertParallel(acc_directive);
    break;
  case ACCD_serial:
    result = convertSerial(acc_directive);
    break;
  case ACCD_kernels:
    result = convertKernels(acc_directive);
    break;
  case ACCD_data:
    result = convertData(acc_directive);
    break;
  case ACCD_enter_data:
    result = convertEnterData(acc_directive);
    break;
  case ACCD_exit_data:
    result = convertExitData(acc_directive);
    break;
  default:
    std::cout << "Unsupported OpenACC directive!\n";
    assert(0);
  }

  assert(result != NULL);

  return result;
}
