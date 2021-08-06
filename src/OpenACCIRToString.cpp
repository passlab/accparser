#include "OpenACCIR.h"
#include <cstdarg>

std::string OpenACCDirective::generatePragmaString(std::string prefix,
                                                   std::string beginning_symbol,
                                                   std::string ending_symbol) {

  if (this->getBaseLang() == ACC_Lang_Fortran && prefix == "#pragma acc ") {
    prefix = "!$acc ";
  };
  std::string result = prefix;

  result += this->toString();

  result += beginning_symbol;

  switch (this->getKind()) {

  // case ACCD_end: {
  //     result +=
  //     ((OpenACCEndDirective*)this)->getPairedDirective()->generatePragmaString("",
  //     "", ""); break;
  // }
  default: {
    ;
  }
  };

  std::vector<OpenACCClause *> *clauses = this->getClausesInOriginalOrder();
  if (clauses->size() != 0) {
    std::vector<OpenACCClause *>::iterator iter;
    for (iter = clauses->begin(); iter != clauses->end(); iter++) {
      result += (*iter)->toString();
    }
    result = result.substr(0, result.size() - 1);
  }
  result += ending_symbol;

  return result;
};

std::string OpenACCDirective::toString() {

  std::string result;

  switch (this->getKind()) {
  case ACCD_loop:
    result += "loop ";
    break;
  case ACCD_parallel:
    result += "parallel ";
    break;
  case ACCD_parallel_loop:
    result += "parallel loop ";
    break;
  default:
    printf("The directive enum is not supported yet.\n");
    assert(0);
  };

  return result;
};

std::string OpenACCClause::expressionToString() {

  std::string result;
  std::vector<std::string> *expr = this->getExpressions();
  if (expr != NULL) {
    std::vector<std::string>::iterator it;
    for (it = expr->begin(); it != expr->end(); it++) {
      result += *it + ", ";
    };
    result = result.substr(0, result.size() - 2);
  }

  return result;
};

std::string OpenACCClause::toString() {

  std::string result;

  switch (this->getKind()) {
  case ACCC_private:
    result += "private ";
    break;
  case ACCC_firstprivate:
    result += "firstprivate ";
    break;
  case ACCC_no_create:
    result += "no_create ";
    break;
  case ACCC_async:
    result += "async ";
    break;
  case ACCC_vector_length:
    result += "vector_length ";
    break;
  case ACCC_attach:
    result += "attach ";
    break;
  case ACCC_deviceptr:
    result += "deviceptr ";
    break;
  case ACCC_present:
    result += "present ";
    break;
  case ACCC_copy:
    result += "copy ";
    break;
  case ACCC_num_gangs:
    result += "num_gangs ";
    break;
  case ACCC_num_workers:
    result += "num_workers ";
    break;
  case ACCC_gang:
    result += "gang ";
    break;
  case ACCC_collapse:
    result += "collapse ";
    break;
  case ACCC_wait:
    result += "wait ";
    break;
  default:
    printf("The clause enum is not supported yet.\n");
  }

  std::string clause_string = "(";
  clause_string += this->expressionToString();
  clause_string += ") ";
  if (clause_string.size() > 3) {
    result += clause_string;
  }

  return result;
};

std::string OpenACCCopyinClause::toString() {

  std::string result = "copyin (";
  std::string parameter_string = "";
  OpenACCCopyinClauseModifier modifier = this->getCopyinClauseModifier();
  switch (modifier) {
  case ACCC_COPYIN_readonly:
    parameter_string = "readonly: ";
    break;
  default:;
  };
  parameter_string += this->expressionToString();
  if (parameter_string.size() > 0) {
    result += parameter_string + ") ";
  } else {
    result = result.substr(0, result.size() - 1);
  }

  return result;
};

std::string OpenACCCopyoutClause::toString() {

  std::string result = "copyout (";
  std::string parameter_string = "";
  OpenACCCopyoutClauseModifier modifier = this->getCopyoutClauseModifier();
  switch (modifier) {
  case ACCC_COPYOUT_zero:
    parameter_string = "zero: ";
    break;
  default:;
  };
  parameter_string += this->expressionToString();
  if (parameter_string.size() > 0) {
    result += parameter_string + ") ";
  } else {
    result = result.substr(0, result.size() - 1);
  }

  return result;
};

std::string OpenACCCreateClause::toString() {

  std::string result = "create (";
  std::string parameter_string = "";
  OpenACCCreateClauseModifier modifier = this->getCreateClauseModifier();
  switch (modifier) {
  case ACCC_CREATE_zero:
    parameter_string = "zero: ";
    break;
  default:;
  };
  parameter_string += this->expressionToString();
  if (parameter_string.size() > 0) {
    result += parameter_string + ") ";
  } else {
    result = result.substr(0, result.size() - 1);
  }

  return result;
};

std::string OpenACCDefaultClause::toString() {

  std::string result = "default (";
  std::string parameter_string;
  OpenACCDefaultClauseKind default_kind = this->getDefaultClauseKind();
  switch (default_kind) {
  case ACCC_DEFAULT_present:
    parameter_string = "present";
    break;
  case ACCC_DEFAULT_none:
    parameter_string = "none";
    break;
  default:
    std::cout << "The parameter of default clause is not supported.\n";
  };

  if (parameter_string.size() > 0) {
    result += parameter_string + ") ";
  } else {
    result = result.substr(0, result.size() - 2);
  }

  return result;
};

std::string OpenACCWorkerClause::toString() {

  std::string result = "worker (";
  std::string parameter_string = "";
  OpenACCWorkerClauseModifier modifier = this->getWorkerClauseModifier();
  switch (modifier) {
  case ACCC_WORKER_num:
    parameter_string = "num: ";
    break;
  default:;
  };
  parameter_string += this->expressionToString();
  if (parameter_string.size() > 0) {
    result += parameter_string + ") ";
  } else {
    result = result.substr(0, result.size() - 1);
  }

  return result;
};
