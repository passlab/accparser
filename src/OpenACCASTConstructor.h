#include "accparserBaseListener.h"

class OpenACCIRConstructor : public accparserBaseListener {
public:
  virtual void enterParallel_directive(
      accparser::Parallel_directiveContext * /*ctx*/) override;
  virtual void enterParallel_loop_directive(
      accparser::Parallel_loop_directiveContext * /*ctx*/) override;
  virtual void
  enterPrivate_clause(accparser::Private_clauseContext * /*ctx*/) override;

  virtual void
  exitGang_clause(accparser::Gang_clauseContext * /*ctx*/) override;
  virtual void
  exitWorker_clause(accparser::Worker_clauseContext * /*ctx*/) override;

  virtual void exitVar(accparser::VarContext * /*ctx*/) override;
};
