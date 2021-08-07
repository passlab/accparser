#include "OpenACCIR.h"
#include <cstdarg>

void OpenACCClause::addLangExpr(std::string expression, int line, int col) {
  //  Since the size of expression vector is supposed to be small, brute force
  //  is used here.
  for (unsigned int i = 0; i < this->expressions.size(); i++) {
    if (expressions.at(i) == expression) {
      return;
    };
  };
  expressions.push_back(expression);

  locations.push_back(ACC_SourceLocation(line, col));
};

/**
 *
 * @param kind
 * @param ..., parameters for the clause, the number of max number of parameters
 * is determined by the kind since each clause expects a fixed set of
 * parameters.
 * @return
 */
OpenACCClause *OpenACCDirective::addOpenACCClause(int k, ...) {

  OpenACCClauseKind kind = (OpenACCClauseKind)k;
  // Check whether the given kind of clause exists first.
  // If not, create an empty vector.
  if (clauses.count(kind) == 0) {
    clauses.insert(std::pair<OpenACCClauseKind, std::vector<OpenACCClause *> *>(
        kind, new std::vector<OpenACCClause *>));
  };
  std::vector<OpenACCClause *> *current_clauses = getClauses(kind);
  va_list args;
  va_start(args, k);
  OpenACCClause *new_clause = NULL;

  switch (kind) {
  case ACCC_if:
  case ACCC_attach:
  case ACCC_collapse:
  case ACCC_copy:
  case ACCC_deviceptr:
  case ACCC_firstprivate:
  case ACCC_device_type:
  case ACCC_gang:
  case ACCC_no_create:
  case ACCC_present:
  case ACCC_private:
  case ACCC_wait: {
    if (current_clauses->size() == 0) {
      new_clause = new OpenACCClause(kind);
      current_clauses = new std::vector<OpenACCClause *>();
      current_clauses->push_back(new_clause);
      clauses[kind] = current_clauses;
    } else {
      if (kind == ACCC_if) {
        std::cerr << "Cannot have two if clauses for the directive " << kind
                  << ", ignored\n";
      } else {
        /* we can have multiple clause and we merge them together now, thus we
         * return the object that is already created */
        new_clause = current_clauses->at(0);
      }
    }
    break;
  }
  case ACCC_async:
  case ACCC_num_gangs:
  case ACCC_num_workers:
  case ACCC_vector_length:
  case ACCC_self: {
    if (current_clauses->size() == 0) {
      new_clause = new OpenACCClause(kind);
      current_clauses = new std::vector<OpenACCClause *>();
      current_clauses->push_back(new_clause);
      clauses[kind] = current_clauses;
    } else {
      new_clause = new OpenACCClause(kind);
      current_clauses->push_back(new_clause);
    }
    break;
  }
  case ACCC_copyin: {
    new_clause = OpenACCCopyinClause::addClause(this);
    break;
  }
  case ACCC_reduction: {
    new_clause = OpenACCReductionClause::addClause(this);
    break;
  }
  case ACCC_copyout: {
    new_clause = OpenACCCopyoutClause::addClause(this);
    break;
  }
  case ACCC_create: {
    new_clause = OpenACCCreateClause::addClause(this);
    break;
  }
  case ACCC_default: {
    new_clause = OpenACCDefaultClause::addClause(this);
    break;
  }
  case ACCC_worker: {
    new_clause = OpenACCWorkerClause::addClause(this);
    break;
  }
  default: {
    std::cout << "Unknown OpenACC clause!\n";
    assert(0);
  }
  };

  va_end(args);
  if (new_clause != NULL && new_clause->getClausePosition() == -1) {
    this->getClausesInOriginalOrder()->push_back(new_clause);
    new_clause->setClausePosition(this->getClausesInOriginalOrder()->size() -
                                  1);
  };
  return new_clause;
};

OpenACCClause *
OpenACCCopyinClause::addClause(OpenACCDirective *directive) {

  std::map<OpenACCClauseKind, std::vector<OpenACCClause *> *> *all_clauses =
      directive->getAllClauses();
  std::vector<OpenACCClause *> *current_clauses =
      directive->getClauses(ACCC_copyin);
  OpenACCClause *new_clause = NULL;

  if (current_clauses->size() == 0) {
    new_clause = new OpenACCCopyinClause();
    current_clauses = new std::vector<OpenACCClause *>();
    current_clauses->push_back(new_clause);
    (*all_clauses)[ACCC_copyin] = current_clauses;
  } else {
    new_clause = new OpenACCCopyinClause();
    current_clauses->push_back(new_clause);
  };

  return new_clause;
};

void OpenACCCopyinClause::mergeClause(OpenACCDirective *directive,
                                            OpenACCClause *current_clause) {
  std::vector<OpenACCClause *> *current_clauses =
      directive->getClauses(ACCC_copyin);
  for (std::vector<OpenACCClause *>::iterator it = current_clauses->begin();
       it != current_clauses->end() - 1; it++) {
    if (((OpenACCCopyinClause *)(*it))->getModifier() ==
        ((OpenACCCopyinClause *)current_clause)->getModifier()) {
      std::vector<std::string> *expressions_previous_clause =
          ((OpenACCClause *)(*it))->getExpressions();
      std::vector<std::string> *expressions_current_clause =
          ((OpenACCClause *)(current_clause))->getExpressions();
      for (std::vector<std::string>::iterator it_expr_current =
               expressions_current_clause->begin();
           it_expr_current != expressions_current_clause->end();
           it_expr_current++) {
        bool para_merge = true;
        for (std::vector<std::string>::iterator it_expr_previous =
                 expressions_previous_clause->begin();
             it_expr_previous != expressions_previous_clause->end();
             it_expr_previous++) {
          if (*it_expr_current == *it_expr_previous) {
            para_merge = false;
          }
        }
        if (para_merge == true)
          expressions_previous_clause->push_back(*it_expr_current);
      }
      current_clauses->pop_back();
      directive->getClausesInOriginalOrder()->pop_back();
      break;
    }
  }
};

OpenACCClause *
OpenACCReductionClause::addClause(OpenACCDirective *directive) {

  std::map<OpenACCClauseKind, std::vector<OpenACCClause *> *> *all_clauses =
      directive->getAllClauses();
  std::vector<OpenACCClause *> *current_clauses =
      directive->getClauses(ACCC_reduction);
  OpenACCClause *new_clause = NULL;

  if (current_clauses->size() == 0) {
    new_clause = new OpenACCReductionClause();
    current_clauses = new std::vector<OpenACCClause *>();
    current_clauses->push_back(new_clause);
    (*all_clauses)[ACCC_reduction] = current_clauses;
  } else {
    new_clause = new OpenACCReductionClause();
    current_clauses->push_back(new_clause);
  };

  return new_clause;
};

void OpenACCReductionClause::mergeClause(
    OpenACCDirective *directive, OpenACCClause *current_clause) {
  std::vector<OpenACCClause *> *current_clauses =
      directive->getClauses(ACCC_reduction);
  for (std::vector<OpenACCClause *>::iterator it = current_clauses->begin();
       it != current_clauses->end() - 1; it++) {
    if (((OpenACCReductionClause *)(*it))->getOperator() ==
        ((OpenACCReductionClause *)current_clause)
            ->getOperator()) {
      std::vector<std::string> *expressions_previous_clause =
          ((OpenACCClause *)(*it))->getExpressions();
      std::vector<std::string> *expressions_current_clause =
          ((OpenACCClause *)(current_clause))->getExpressions();
      for (std::vector<std::string>::iterator it_expr_current =
               expressions_current_clause->begin();
           it_expr_current != expressions_current_clause->end();
           it_expr_current++) {
        bool para_merge = true;
        for (std::vector<std::string>::iterator it_expr_previous =
                 expressions_previous_clause->begin();
             it_expr_previous != expressions_previous_clause->end();
             it_expr_previous++) {
          if (*it_expr_current == *it_expr_previous) {
            para_merge = false;
          }
        }
        if (para_merge == true)
          expressions_previous_clause->push_back(*it_expr_current);
      }
      current_clauses->pop_back();
      directive->getClausesInOriginalOrder()->pop_back();
      break;
    }
  }
};

OpenACCClause *
OpenACCCopyoutClause::addClause(OpenACCDirective *directive) {

  std::map<OpenACCClauseKind, std::vector<OpenACCClause *> *> *all_clauses =
      directive->getAllClauses();
  std::vector<OpenACCClause *> *current_clauses =
      directive->getClauses(ACCC_copyout);
  OpenACCClause *new_clause = NULL;

  if (current_clauses->size() == 0) {
    new_clause = new OpenACCCopyoutClause();
    current_clauses = new std::vector<OpenACCClause *>();
    current_clauses->push_back(new_clause);
    (*all_clauses)[ACCC_copyout] = current_clauses;
  } else {
    new_clause = new OpenACCCopyoutClause();
    current_clauses->push_back(new_clause);
  };

  return new_clause;
};

void OpenACCCopyoutClause::mergeClause(OpenACCDirective *directive,
                                              OpenACCClause *current_clause) {
  std::vector<OpenACCClause *> *current_clauses =
      directive->getClauses(ACCC_copyout);
  for (std::vector<OpenACCClause *>::iterator it = current_clauses->begin();
       it != current_clauses->end() - 1; it++) {
    if (((OpenACCCopyoutClause *)(*it))->getModifier() ==
        ((OpenACCCopyoutClause *)current_clause)->getModifier()) {
      std::vector<std::string> *expressions_previous_clause =
          ((OpenACCClause *)(*it))->getExpressions();
      std::vector<std::string> *expressions_current_clause =
          ((OpenACCClause *)(current_clause))->getExpressions();
      for (std::vector<std::string>::iterator it_expr_current =
               expressions_current_clause->begin();
           it_expr_current != expressions_current_clause->end();
           it_expr_current++) {
        bool para_merge = true;
        for (std::vector<std::string>::iterator it_expr_previous =
                 expressions_previous_clause->begin();
             it_expr_previous != expressions_previous_clause->end();
             it_expr_previous++) {
          if (*it_expr_current == *it_expr_previous) {
            para_merge = false;
          }
        }
        if (para_merge == true)
          expressions_previous_clause->push_back(*it_expr_current);
      }
      current_clauses->pop_back();
      directive->getClausesInOriginalOrder()->pop_back();
      break;
    }
  }
};

OpenACCClause *
OpenACCCreateClause::addClause(OpenACCDirective *directive) {

  std::map<OpenACCClauseKind, std::vector<OpenACCClause *> *> *all_clauses =
      directive->getAllClauses();
  std::vector<OpenACCClause *> *current_clauses =
      directive->getClauses(ACCC_create);
  OpenACCClause *new_clause = NULL;

  if (current_clauses->size() == 0) {
    new_clause = new OpenACCCreateClause();
    current_clauses = new std::vector<OpenACCClause *>();
    current_clauses->push_back(new_clause);
    (*all_clauses)[ACCC_create] = current_clauses;
  } else {
    new_clause = new OpenACCCreateClause();
    current_clauses->push_back(new_clause);
  };

  return new_clause;
};

void OpenACCCreateClause::mergeClause(OpenACCDirective *directive,
                                            OpenACCClause *current_clause) {
  std::vector<OpenACCClause *> *current_clauses =
      directive->getClauses(ACCC_create);
  for (std::vector<OpenACCClause *>::iterator it = current_clauses->begin();
       it != current_clauses->end() - 1; it++) {
    if (((OpenACCCreateClause *)(*it))->getModifier() ==
        ((OpenACCCreateClause *)current_clause)->getModifier()) {
      std::vector<std::string> *expressions_previous_clause =
          ((OpenACCClause *)(*it))->getExpressions();
      std::vector<std::string> *expressions_current_clause =
          ((OpenACCClause *)(current_clause))->getExpressions();
      for (std::vector<std::string>::iterator it_expr_current =
               expressions_current_clause->begin();
           it_expr_current != expressions_current_clause->end();
           it_expr_current++) {
        bool para_merge = true;
        for (std::vector<std::string>::iterator it_expr_previous =
                 expressions_previous_clause->begin();
             it_expr_previous != expressions_previous_clause->end();
             it_expr_previous++) {
          if (*it_expr_current == *it_expr_previous) {
            para_merge = false;
          }
        }
        if (para_merge == true)
          expressions_previous_clause->push_back(*it_expr_current);
      }
      current_clauses->pop_back();
      directive->getClausesInOriginalOrder()->pop_back();
      break;
    }
  }
};

void OpenACCAsyncClause::mergeClause(OpenACCDirective *directive,
                                          OpenACCClause *current_clause) {
  std::vector<OpenACCClause *> *current_clauses =
      directive->getClauses(ACCC_async);

  for (std::vector<OpenACCClause *>::iterator it = current_clauses->begin();
       it != current_clauses->end() - 1; it++) {
    if (((((OpenACCClause *)(current_clause))->getExpressions())->size() !=
         0) &&
        ((((OpenACCClause *)(*it))->getExpressions())->size() != 0)) {
      std::vector<std::string> *expressions_previous_clause =
          ((OpenACCClause *)(*it))->getExpressions();
      std::vector<std::string> *expressions_current_clause =
          ((OpenACCClause *)(current_clause))->getExpressions();
      std::string new_expression = expressions_current_clause->at(0);
      std::string old_expression = expressions_previous_clause->at(0);
      if (new_expression == old_expression) {
        current_clauses->pop_back();
        directive->getClausesInOriginalOrder()->pop_back();
      }
      break;
    } else if (((((OpenACCClause *)(current_clause))->getExpressions())
                    ->size() == 0) &&
               ((((OpenACCClause *)(*it))->getExpressions())->size() == 0)) {
      current_clauses->pop_back();
      directive->getClausesInOriginalOrder()->pop_back();
    }
  }
};

void OpenACCNumGangsClause::mergeClause(OpenACCDirective *directive,
                                                OpenACCClause *current_clause) {
  std::vector<OpenACCClause *> *current_clauses =
      directive->getClauses(ACCC_num_gangs);

  for (std::vector<OpenACCClause *>::iterator it = current_clauses->begin();
       it != current_clauses->end() - 1; it++) {
    if (((((OpenACCClause *)(current_clause))->getExpressions())->size() !=
         0) &&
        ((((OpenACCClause *)(*it))->getExpressions())->size() != 0)) {
      std::vector<std::string> *expressions_previous_clause =
          ((OpenACCClause *)(*it))->getExpressions();
      std::vector<std::string> *expressions_current_clause =
          ((OpenACCClause *)(current_clause))->getExpressions();
      std::string new_expression = expressions_current_clause->at(0);
      std::string old_expression = expressions_previous_clause->at(0);
      if (new_expression == old_expression) {
        current_clauses->pop_back();
        directive->getClausesInOriginalOrder()->pop_back();
      }
      break;
    }
  }
};

void OpenACCNumWorkersClause::mergeClause(
    OpenACCDirective *directive, OpenACCClause *current_clause) {
  std::vector<OpenACCClause *> *current_clauses =
      directive->getClauses(ACCC_num_workers);

  for (std::vector<OpenACCClause *>::iterator it = current_clauses->begin();
       it != current_clauses->end() - 1; it++) {
    if (((((OpenACCClause *)(current_clause))->getExpressions())->size() !=
         0) &&
        ((((OpenACCClause *)(*it))->getExpressions())->size() != 0)) {
      std::vector<std::string> *expressions_previous_clause =
          ((OpenACCClause *)(*it))->getExpressions();
      std::vector<std::string> *expressions_current_clause =
          ((OpenACCClause *)(current_clause))->getExpressions();
      std::string new_expression = expressions_current_clause->at(0);
      std::string old_expression = expressions_previous_clause->at(0);
      if (new_expression == old_expression) {
        current_clauses->pop_back();
        directive->getClausesInOriginalOrder()->pop_back();
      }
      break;
    }
  }
};

void OpenACCVectorLengthClause::mergeClause(
    OpenACCDirective *directive, OpenACCClause *current_clause) {
  std::vector<OpenACCClause *> *current_clauses =
      directive->getClauses(ACCC_vector_length);

  for (std::vector<OpenACCClause *>::iterator it = current_clauses->begin();
       it != current_clauses->end() - 1; it++) {
    if (((((OpenACCClause *)(current_clause))->getExpressions())->size() !=
         0) &&
        ((((OpenACCClause *)(*it))->getExpressions())->size() != 0)) {
      std::vector<std::string> *expressions_previous_clause =
          ((OpenACCClause *)(*it))->getExpressions();
      std::vector<std::string> *expressions_current_clause =
          ((OpenACCClause *)(current_clause))->getExpressions();
      std::string new_expression = expressions_current_clause->at(0);
      std::string old_expression = expressions_previous_clause->at(0);
      if (new_expression == old_expression) {
        current_clauses->pop_back();
        directive->getClausesInOriginalOrder()->pop_back();
      }
      break;
    }
  }
};

void OpenACCSelfClause::mergeClause(OpenACCDirective *directive,
                                        OpenACCClause *current_clause) {
  std::vector<OpenACCClause *> *current_clauses =
      directive->getClauses(ACCC_self);

  for (std::vector<OpenACCClause *>::iterator it = current_clauses->begin();
       it != current_clauses->end() - 1; it++) {
    if (((((OpenACCClause *)(current_clause))->getExpressions())->size() !=
         0) &&
        ((((OpenACCClause *)(*it))->getExpressions())->size() != 0)) {
      std::vector<std::string> *expressions_previous_clause =
          ((OpenACCClause *)(*it))->getExpressions();
      std::vector<std::string> *expressions_current_clause =
          ((OpenACCClause *)(current_clause))->getExpressions();
      std::string new_expression = expressions_current_clause->at(0);
      std::string old_expression = expressions_previous_clause->at(0);
      if (new_expression == old_expression) {
        current_clauses->pop_back();
        directive->getClausesInOriginalOrder()->pop_back();
      }
      break;
    } else if (((((OpenACCClause *)(current_clause))->getExpressions())
                    ->size() == 0) &&
               ((((OpenACCClause *)(*it))->getExpressions())->size() == 0)) {
      current_clauses->pop_back();
      directive->getClausesInOriginalOrder()->pop_back();
    }
  }
};

OpenACCClause *
OpenACCDefaultClause::addClause(OpenACCDirective *directive) {

  std::map<OpenACCClauseKind, std::vector<OpenACCClause *> *> *all_clauses =
      directive->getAllClauses();
  std::vector<OpenACCClause *> *current_clauses =
      directive->getClauses(ACCC_default);
  OpenACCClause *new_clause = NULL;

  if (current_clauses->size() == 0) {
    new_clause = new OpenACCDefaultClause();
    current_clauses = new std::vector<OpenACCClause *>();
    current_clauses->push_back(new_clause);
    (*all_clauses)[ACCC_default] = current_clauses;
  } else { /* could be an error since default clause may only appear once */
    std::cerr << "Cannot have two default clause for the directive "
              << directive->getKind() << ", ignored\n";
  };

  return new_clause;
};

OpenACCClause *
OpenACCWorkerClause::addClause(OpenACCDirective *directive) {

  std::map<OpenACCClauseKind, std::vector<OpenACCClause *> *> *all_clauses =
      directive->getAllClauses();
  std::vector<OpenACCClause *> *current_clauses =
      directive->getClauses(ACCC_worker);
  OpenACCClause *new_clause = NULL;

  if (current_clauses->size() == 0) {
    new_clause = new OpenACCWorkerClause();
    current_clauses = new std::vector<OpenACCClause *>();
    current_clauses->push_back(new_clause);
    (*all_clauses)[ACCC_worker] = current_clauses;
  } else { /* could be an error since worker clause may only appear once */
    std::cerr << "Cannot have two worker clause for the directive "
              << directive->getKind() << ", ignored\n";
  };

  return new_clause;
};
