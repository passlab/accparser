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
  case ACCD_end: {
    result += ((OpenACCEndDirective *)this)
                  ->getPairedDirective()
                  ->generatePragmaString("", "", "");
    break;
  }
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
  case ACCD_atomic:
    result += "atomic ";
    break;
  case ACCD_data:
    result += "data ";
    break;
  case ACCD_declare:
    result += "declare ";
    break;
  case ACCD_end:
    result += "end ";
    break;
  case ACCD_enter_data:
    result += "enter data ";
    break;
  case ACCD_exit_data:
    result += "exit data ";
    break;
  case ACCD_host_data:
    result += "host_data ";
    break;
  case ACCD_init:
    result += "init ";
    break;
  case ACCD_kernels:
    result += "kernels ";
    break;
  case ACCD_kernels_loop:
    result += "kernels loop ";
    break;
  case ACCD_loop:
    result += "loop ";
    break;
  case ACCD_parallel:
    result += "parallel ";
    break;
  case ACCD_parallel_loop:
    result += "parallel loop ";
    break;
  case ACCD_routine:
    result += "routine ";
    if (((OpenACCRoutineDirective *)this)->getName() != "")
      result += "(" + ((OpenACCRoutineDirective *)this)->getName() + ") ";
    ;
    break;
  case ACCD_serial:
    result += "serial ";
    break;
  case ACCD_serial_loop:
    result += "serial loop ";
    break;
  case ACCD_set:
    result += "set ";
    break;
  case ACCD_shutdown:
    result += "shutdown ";
    break;
  case ACCD_update:
    result += "update ";
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
  case ACCC_async:
    result += "async ";
    break;
  case ACCC_attach:
    result += "attach ";
    break;
  case ACCC_auto:
    result += "auto ";
    break;
  case ACCC_bind:
    result += "bind ";
    break;
  case ACCC_capture:
    result += "capture ";
    break;
  case ACCC_collapse:
    result += "collapse ";
    break;
  case ACCC_copy:
    result += "copy ";
    break;
  case ACCC_default_async:
    result += "default_async ";
    break;
  case ACCC_delete:
    result += "delete ";
    break;
  case ACCC_detach:
    result += "detach ";
    break;
  case ACCC_device:
    result += "device ";
    break;
  case ACCC_device_num:
    result += "device_num ";
    break;
  case ACCC_device_resident:
    result += "device_resident ";
    break;
  case ACCC_device_type:
    result += "device_type ";
    break;
  case ACCC_deviceptr:
    result += "deviceptr ";
    break;
  case ACCC_finalize:
    result += "finalize ";
    break;
  case ACCC_firstprivate:
    result += "firstprivate ";
    break;
  case ACCC_gang:
    result += "gang ";
    break;
  case ACCC_host:
    result += "host ";
    break;
  case ACCC_if:
    result += "if ";
    break;
  case ACCC_if_present:
    result += "if_present ";
    break;
  case ACCC_independent:
    result += "independent ";
    break;
  case ACCC_link:
    result += "link ";
    break;
  case ACCC_nohost:
    result += "nohost ";
    break;
  case ACCC_no_create:
    result += "no_create ";
    break;
  case ACCC_num_gangs:
    result += "num_gangs ";
    break;
  case ACCC_num_workers:
    result += "num_workers ";
    break;
  case ACCC_present:
    result += "present ";
    break;
  case ACCC_private:
    result += "private ";
    break;
  case ACCC_read:
    result += "read ";
    break;
  case ACCC_self:
    result += "self ";
    break;
  case ACCC_seq:
    result += "seq ";
    break;
  case ACCC_tile:
    result += "tile ";
    break;
  case ACCC_update:
    result += "update ";
    break;
  case ACCC_use_device:
    result += "use_device ";
  case ACCC_vector_length:
    result += "vector_length ";
    break;
  case ACCC_wait:
    result += "wait ";
    break;
  case ACCC_write:
    result += "write ";
    break;
  case ACCC_vector:
    result += "vector ";
    break;
  case ACCC_worker:
    result += "worker ";
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

std::string OpenACCCacheDirective::expressionToString() {

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

std::string OpenACCCacheDirective::toString() {

  std::string result = "cache (";
  std::string parameter_string = "";
  OpenACCCacheDirectiveModifier modifier = this->getModifier();
  switch (modifier) {
  case ACCC_CACHE_readonly:
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

std::string OpenACCWaitDirective::expressionToString() {

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

std::string OpenACCWaitDirective::toString() {

  std::string result = "wait ";
  std::string parameter_string = "";
  if (this->getExpressions()->size() != 0) {
    parameter_string += "( ";
    std::string devnum = this->getDevnum();
    if (devnum != "") {
      parameter_string += "devnum: " + devnum + ": ";
    };
    if (this->getQueues() == true) {
      parameter_string += "queues: ";
    };

    parameter_string += this->expressionToString();
    if (parameter_string.size() > 0) {
      result += parameter_string + ") ";
    } else {
      result = result.substr(0, result.size() - 1);
    }
  }
  return result;
};

std::string OpenACCCopyinClause::toString() {

  std::string result = "copyin (";
  std::string parameter_string = "";
  OpenACCCopyinClauseModifier modifier = this->getModifier();
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
  OpenACCCopyoutClauseModifier modifier = this->getModifier();
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
  OpenACCCreateClauseModifier modifier = this->getModifier();
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
  OpenACCDefaultClauseKind default_kind = this->getKind();
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

std::string OpenACCReductionClause::toString() {

  std::string result = "reduction (";
  std::string parameter_string = "";
  OpenACCReductionClauseOperator reduction_operator = this->getOperator();
  switch (reduction_operator) {
  case ACCC_REDUCTION_add:
    parameter_string = "+: ";
    break;
  case ACCC_REDUCTION_mul:
    parameter_string = "*: ";
    break;
  case ACCC_REDUCTION_max:
    parameter_string = "max: ";
    break;
  case ACCC_REDUCTION_min:
    parameter_string = "min: ";
    break;
  case ACCC_REDUCTION_bitand:
    parameter_string = "$: ";
    break;
  case ACCC_REDUCTION_bitor:
    parameter_string = "|: ";
    break;
  case ACCC_REDUCTION_bitxor:
    parameter_string = "^: ";
    break;
  case ACCC_REDUCTION_logand:
    parameter_string = "&&: ";
    break;
  case ACCC_REDUCTION_logor:
    parameter_string = "||: ";
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

std::string OpenACCVectorClause::toString() {

  std::string result = "vector (";
  std::string parameter_string = "";
  OpenACCVectorClauseModifier modifier = this->getModifier();
  switch (modifier) {
  case ACCC_VECTOR_length:
    parameter_string = "length: ";
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

std::string OpenACCWaitClause::toString() {

  std::string result = "wait ";
  std::string parameter_string = "";
  if (this->getExpressions()->size() != 0) {
    parameter_string += "(";
    std::string devnum = this->getDevnum();
    if (devnum != "") {
      parameter_string += "devnum: " + devnum + ": ";
    };
    if (this->getQueues() == true) {
      parameter_string += "queues: ";
    };

    parameter_string += this->expressionToString();
    if (parameter_string.size() > 0) {
      result += parameter_string + ") ";
    } else {
      result = result.substr(0, result.size() - 1);
    }
  }

  return result;
};

std::string OpenACCWorkerClause::toString() {

  std::string result = "worker (";
  std::string parameter_string = "";
  OpenACCWorkerClauseModifier modifier = this->getModifier();
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
