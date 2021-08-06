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
  case ACCC_async:
  case ACCC_if:
  case ACCC_self:
  case ACCC_attach:
  case ACCC_collapse:
  case ACCC_copy:
  case ACCC_deviceptr:
  case ACCC_firstprivate:
  case ACCC_device_type:
  case ACCC_gang:
  case ACCC_no_create:
  case ACCC_num_gangs:
  case ACCC_num_workers:
  case ACCC_present:
  case ACCC_private:
  case ACCC_vector_length:
  case ACCC_wait: {
    if (current_clauses->size() == 0) {
      new_clause = new OpenACCClause(kind);
      current_clauses = new std::vector<OpenACCClause *>();
      current_clauses->push_back(new_clause);
      clauses[kind] = current_clauses;
    } else {
      /* we can have multiple clause and we merge them together now, thus we
       * return the object that is already created */
      new_clause = current_clauses->at(0);
    }
    break;
  }
  case ACCC_copyin: {
    new_clause = OpenACCCopyinClause::addCopyinClause(this);
    break;
  }
  case ACCC_reduction: {
    new_clause = OpenACCReductionClause::addReductionClause(this);
    break;
  }
  case ACCC_copyout: {
    new_clause = OpenACCCopyoutClause::addCopyoutClause(this);
    break;
  }
  case ACCC_create: {
    new_clause = OpenACCCreateClause::addCreateClause(this);
    break;
  }
  case ACCC_default: {
    new_clause = OpenACCDefaultClause::addDefaultClause(this);
    break;
  }
  case ACCC_worker: {
    new_clause = OpenACCWorkerClause::addWorkerClause(this);
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
OpenACCCopyinClause::addCopyinClause(OpenACCDirective *directive) {

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
  };

  return new_clause;
};

OpenACCClause *
OpenACCReductionClause::addReductionClause(OpenACCDirective *directive) {

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
  };

  return new_clause;
};

OpenACCClause *
OpenACCCopyoutClause::addCopyoutClause(OpenACCDirective *directive) {

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
  };

  return new_clause;
};

OpenACCClause *
OpenACCCreateClause::addCreateClause(OpenACCDirective *directive) {

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
  };

  return new_clause;
};

OpenACCClause *
OpenACCDefaultClause::addDefaultClause(OpenACCDirective *directive) {

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
OpenACCWorkerClause::addWorkerClause(OpenACCDirective *directive) {

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
