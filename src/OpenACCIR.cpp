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

  locations.push_back(SourceLocation(line, col));
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
  case ACCC_collapse:
  case ACCC_copy:
  case ACCC_copyin:
  case ACCC_copyout:
  case ACCC_firstprivate:
  case ACCC_num_gangs:
  case ACCC_num_workers:
  case ACCC_private:
  case ACCC_wait: {
    if (current_clauses->size() == 0) {
      new_clause = new OpenACCClause(kind);
      current_clauses = new std::vector<OpenACCClause *>();
      current_clauses->push_back(new_clause);
      clauses[kind] = current_clauses;
    } else {
      if (kind == ACCC_num_gangs) {
        std::cerr << "Cannot have two num_gangs clause for the directive "
                  << kind << ", ignored\n";
      } else if (kind == ACCC_num_workers) {
        std::cerr << "Cannot have two num_workers clause for the directive "
                  << kind << ", ignored\n";
      } else {
        /* we can have multiple clause and we merge them together now, thus we
         * return the object that is already created */
        new_clause = current_clauses->at(0);
      }
    }
    break;
  }
  case ACCC_default: {
    OpenACCDefaultClauseKind default_kind =
        (OpenACCDefaultClauseKind)va_arg(args, int);
    new_clause = OpenACCDefaultClause::addDefaultClause(this, default_kind);
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
OpenACCDefaultClause::addDefaultClause(OpenACCDirective *directive,
                                       OpenACCDefaultClauseKind default_kind) {

  std::map<OpenACCClauseKind, std::vector<OpenACCClause *> *> *all_clauses =
      directive->getAllClauses();
  std::vector<OpenACCClause *> *current_clauses =
      directive->getClauses(ACCC_default);
  OpenACCClause *new_clause = NULL;

  if (current_clauses->size() == 0) {
    new_clause = new OpenACCDefaultClause(default_kind);
    current_clauses = new std::vector<OpenACCClause *>();
    current_clauses->push_back(new_clause);
    (*all_clauses)[ACCC_default] = current_clauses;
  } else { /* could be an error since if clause may only appear once */
    std::cerr << "Cannot have two default clause for the directive "
              << directive->getKind() << ", ignored\n";
  };

  return new_clause;
};
