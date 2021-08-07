#include <cassert>
#include <cstring>
#include <fstream>
#include <iostream>
#include <map>
#include <vector>

#include "OpenACCKinds.h"

enum OpenACCBaseLang {
  ACC_Lang_C,
  ACC_Lang_Cplusplus,
  ACC_Lang_Fortran,
  ACC_Lang_unknown
};

class ACC_SourceLocation {
  int line;
  int column;

  ACC_SourceLocation *parent_construct;

public:
  ACC_SourceLocation(int _line = 0, int _col = 0,
                     ACC_SourceLocation *_parent_construct = NULL)
      : line(_line), column(_col), parent_construct(_parent_construct){};
  void setParentConstruct(ACC_SourceLocation *_parent_construct) {
    parent_construct = _parent_construct;
  };
  ACC_SourceLocation *getParentConstruct() { return parent_construct; };
  int getLine() { return line; };
  void setLine(int _line) { line = _line; };
  int getColumn() { return column; };
  void setColumn(int _column) { column = _column; };
};

/**
 * The class or baseclass for all the clause classes. For all the clauses that
 * only take 0 to multiple expression or variables, we use this class to create
 * objects. For all other clauses, which requires at least one parameters, we
 * will have an inherit class from this one, and the superclass contains fields
 * for the parameters
 */
class OpenACCClause : public ACC_SourceLocation {
protected:
  OpenACCClauseKind kind;
  // the clause position in the vector of clauses in original order
  int clause_position = -1;

  /* consider this is a struct of array, i.e.
   * the expression/localtionLine/locationColumn are the same index are one
   * record for an expression and its location
   */
  std::vector<std::string> expressions;

  std::vector<ACC_SourceLocation> locations;

public:
  OpenACCClause(OpenACCClauseKind k, int _line = 0, int _col = 0)
      : ACC_SourceLocation(_line, _col), kind(k){};

  OpenACCClauseKind getKind() { return kind; };
  int getClausePosition() { return clause_position; };
  void setClausePosition(int _clause_position) {
    clause_position = _clause_position;
  };

  // a list of expressions or variables that are language-specific for the
  // clause, accparser does not parse them, instead, it only stores them as
  // strings
  void addLangExpr(std::string expression_string, int line = 0, int col = 0);

  std::vector<std::string> *getExpressions() { return &expressions; };

  virtual std::string toString();
  std::string expressionToString();
};

/**
 * The class for all the OpenACC directives
 */
class OpenACCDirective : public ACC_SourceLocation {
protected:
  OpenACCDirectiveKind kind;
  OpenACCBaseLang lang;

  /* The vector is used to store the pointers of clauses in original order.
   * While unparsing, the generated pragma keeps the clauses in the same order
   * as the input. For example, #pragma omp parallel shared(a) private(b) is the
   * input. The unparsing won't switch the order of share and private clause.
   * Share clause is always the first.
   *
   * For the clauses that could be normalized, we always merge the second one to
   * the first one. Then the second one will be eliminated and not stored
   * anywhere.
   */
  std::vector<OpenACCClause *> *clauses_in_original_order =
      new std::vector<OpenACCClause *>();

  /* the map to store clauses of the directive, for each clause, we store a
   * vector of OpenACCClause objects since there could be multiple clause
   * objects for those clauses that take parameters, e.g. reduction clause
   *
   * for those clauses just take no parameters, but may take some variables or
   * expressions, we only need to have one OpenACCClause object, e.g. shared,
   * private.
   *
   * The design and use of this map should make sure that for any clause, we
   * should only have one OpenACCClause object for each instance of kind and
   * full parameters
   */
  std::map<OpenACCClauseKind, std::vector<OpenACCClause *> *> clauses;
  /**
   *
   * This method searches the clauses map to see whether one or more
   * OpenACCClause objects of the specified kind parameters exist in the
   * directive, if so it returns the objects that match.
   * @param kind clause kind
   * @param parameters clause parameters
   * @return
   */
  std::vector<OpenACCClause *> searchOpenACCClause(OpenACCClauseKind kind,
                                                   int num, int *parameters);

  /**
   * Search and add a clause of kind and parameters specified by the variadic
   * parameters. This should be the only call used to add an OpenACCClause
   * object.
   *
   * The method may simply create an OpenACCClause-subclassed object and return
   * it. In this way, normalization will be needed later on.
   *
   * Or the method may do the normalization while adding a clause.
   * it first searches the clauses map to see whether an OpenACCClause object
   * of the specified kind and parameters exists in the map. If so, it only
   * return that OpenACCClause object, otherwise, it should create a new
   * OpenACCClause object and insert in the map
   *
   * NOTE: if only partial parameters are provided as keys to search for a
   * clause, the function will only return the first one that matches. Thus, the
   * method should NOT be called with partial parameters of a specific clause
   * @param kind
   * @param parameters clause parameters, number of parameters should be
   * determined by the kind
   * @return
   */
  OpenACCClause *addOpenACCClause(OpenACCClauseKind kind, int *parameters);
  /**
   * normalize all the clause of a specific kind
   * @param kind
   * @return
   */
  void *normalizeClause(OpenACCClauseKind kind);

public:
  OpenACCDirective(OpenACCDirectiveKind k,
                   OpenACCBaseLang _lang = ACC_Lang_unknown, int _line = 0,
                   int _col = 0)
      : ACC_SourceLocation(_line, _col), kind(k), lang(_lang){};

  OpenACCDirectiveKind getKind() { return kind; };

  std::map<OpenACCClauseKind, std::vector<OpenACCClause *> *> *getAllClauses() {
    return &clauses;
  };

  std::vector<OpenACCClause *> *getClauses(OpenACCClauseKind kind) {
    return clauses[kind];
  };
  std::vector<OpenACCClause *> *getClausesInOriginalOrder() {
    return clauses_in_original_order;
  };

  std::string toString();

  std::string generatePragmaString(std::string _prefix = "#pragma acc ",
                                   std::string _beginning_symbol = "",
                                   std::string _ending_symbol = "");
  // To call this method directly to add new clause, it can't be protected.
  OpenACCClause *addOpenACCClause(int, ...);
  void setBaseLang(OpenACCBaseLang _lang) { lang = _lang; };
  OpenACCBaseLang getBaseLang() { return lang; };
};

// Copyin Clause
class OpenACCCopyinClause : public OpenACCClause {

protected:
  OpenACCCopyinClauseModifier modifier = ACCC_COPYIN_unspecified;

public:
  OpenACCCopyinClause() : OpenACCClause(ACCC_copyin){};

  OpenACCCopyinClauseModifier getCopyinClauseModifier() { return modifier; };

  void setCopyinClauseModifier(OpenACCCopyinClauseModifier _modifier) {
    modifier = _modifier;
  };

  static OpenACCClause *addCopyinClause(OpenACCDirective *);
  std::string toString();
  void mergeCopyinClause(OpenACCDirective *, OpenACCClause *);
};

// Async Clause
class OpenACCAsyncClause : public OpenACCClause {

public:
  OpenACCAsyncClause() : OpenACCClause(ACCC_async){};

  static OpenACCClause *addAsyncClause(OpenACCDirective *);
  std::string toString();
  void mergeAsyncClause(OpenACCDirective *, OpenACCClause *);
};

// Num_gangs Clause
class OpenACCNumGangsClause : public OpenACCClause {

public:
  OpenACCNumGangsClause() : OpenACCClause(ACCC_num_gangs){};

  static OpenACCClause *addNumGangsClause(OpenACCDirective *);
  std::string toString();
  void mergeNumGangsClause(OpenACCDirective *, OpenACCClause *);
};

// Num_workers Clause
class OpenACCNumWorkersClause : public OpenACCClause {

public:
  OpenACCNumWorkersClause() : OpenACCClause(ACCC_num_workers){};

  static OpenACCClause *addNumWorkersClause(OpenACCDirective *);
  std::string toString();
  void mergeNumWorkersClause(OpenACCDirective *, OpenACCClause *);
};

// Vector_length Clause
class OpenACCVectorLengthClause : public OpenACCClause {

public:
  OpenACCVectorLengthClause() : OpenACCClause(ACCC_vector_length){};

  static OpenACCClause *addVectorLengthClause(OpenACCDirective *);
  std::string toString();
  void mergeVectorLengthClause(OpenACCDirective *, OpenACCClause *);
};

// Vector_length Clause
class OpenACCSelfClause : public OpenACCClause {

public:
  OpenACCSelfClause() : OpenACCClause(ACCC_self){};

  static OpenACCClause *addSelfClause(OpenACCDirective *);
  std::string toString();
  void mergeSelfClause(OpenACCDirective *, OpenACCClause *);
};

// Reduction Clause
class OpenACCReductionClause : public OpenACCClause {

protected:
  OpenACCReductionClauseOperator reduction_operator =
      ACCC_REDUCTION_unspecified;

public:
  OpenACCReductionClause() : OpenACCClause(ACCC_reduction){};

  OpenACCReductionClauseOperator getReductionClauseOperator() {
    return reduction_operator;
  };

  void setReductionClauseOperator(OpenACCReductionClauseOperator _operator) {
    reduction_operator = _operator;
  };

  static OpenACCClause *addReductionClause(OpenACCDirective *);
  std::string toString();
  void mergeReductionClause(OpenACCDirective *, OpenACCClause *);
};

// Copyout Clause
class OpenACCCopyoutClause : public OpenACCClause {

protected:
  OpenACCCopyoutClauseModifier modifier = ACCC_COPYOUT_unspecified;

public:
  OpenACCCopyoutClause() : OpenACCClause(ACCC_copyout){};

  OpenACCCopyoutClauseModifier getCopyoutClauseModifier() { return modifier; };

  void setCopyoutClauseModifier(OpenACCCopyoutClauseModifier _modifier) {
    modifier = _modifier;
  };

  static OpenACCClause *addCopyoutClause(OpenACCDirective *);
  std::string toString();
  void mergeCopyoutClause(OpenACCDirective *, OpenACCClause *);
};

// Create Clause
class OpenACCCreateClause : public OpenACCClause {

protected:
  OpenACCCreateClauseModifier modifier = ACCC_CREATE_unspecified;

public:
  OpenACCCreateClause() : OpenACCClause(ACCC_create){};

  OpenACCCreateClauseModifier getCreateClauseModifier() { return modifier; };

  void setCreateClauseModifier(OpenACCCreateClauseModifier _modifier) {
    modifier = _modifier;
  };

  static OpenACCClause *addCreateClause(OpenACCDirective *);
  std::string toString();
  void mergeCreateClause(OpenACCDirective *, OpenACCClause *);
};

// Default Clause
class OpenACCDefaultClause : public OpenACCClause {

protected:
  OpenACCDefaultClauseKind default_kind = ACCC_DEFAULT_unspecified;

public:
  OpenACCDefaultClause() : OpenACCClause(ACCC_default){};

  OpenACCDefaultClauseKind getDefaultClauseKind() { return default_kind; };

  void setDefaultClauseKind(OpenACCDefaultClauseKind _default_kind) {
    default_kind = _default_kind;
  };

  static OpenACCClause *addDefaultClause(OpenACCDirective *);
  std::string toString();
};

// Worker Clause
class OpenACCWorkerClause : public OpenACCClause {

protected:
  OpenACCWorkerClauseModifier modifier = ACCC_WORKER_unspecified;

public:
  OpenACCWorkerClause() : OpenACCClause(ACCC_worker){};

  OpenACCWorkerClauseModifier getWorkerClauseModifier() { return modifier; };

  void setWorkerClauseModifier(OpenACCWorkerClauseModifier _modifier) {
    modifier = _modifier;
  };

  static OpenACCClause *addWorkerClause(OpenACCDirective *);
  std::string toString();
};
