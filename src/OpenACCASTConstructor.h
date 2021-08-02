#include "OpenACCIR.h"
#include "accparserBaseListener.h"

class OpenACCIRConstructor : public accparserBaseListener {
public:
  virtual void enterParallel_directive(
      accparser::Parallel_directiveContext * /*ctx*/) override;
  virtual void enterParallel_loop_directive(
      accparser::Parallel_loop_directiveContext * /*ctx*/) override;
  virtual void
  enterPrivate_clause(accparser::Private_clauseContext * /*ctx*/) override;

  virtual void enterFirstprivate_clause(
      accparser::Firstprivate_clauseContext * /*ctx*/) override;

  virtual void
  enterCopy_clause(accparser::Copy_clauseContext * /*ctx*/) override;

  virtual void
  enterCopyin_clause(accparser::Copyin_clauseContext * /*ctx*/) override;

  virtual void exitCopyin_clause_modifier(
      accparser::Copyin_clause_modifierContext * /*ctx*/) override;

  virtual void
  enterNo_create_clause(accparser::No_create_clauseContext * /*ctx*/) override;

  virtual void
  enterDeviceptr_clause(accparser::Deviceptr_clauseContext * /*ctx*/) override;

  virtual void
  enterAsync_clause(accparser::Async_clauseContext * /*ctx*/) override;

  virtual void
  enterPresent_clause(accparser::Present_clauseContext * /*ctx*/) override;

  virtual void
  enterAttach_clause(accparser::Attach_clauseContext * /*ctx*/) override;

  virtual void enterNum_workers_clause(
      accparser::Num_workers_clauseContext * /*ctx*/) override;

  virtual void
  enterWait_clause(accparser::Wait_clauseContext * /*ctx*/) override;

  virtual void
  enterDefault_clause(accparser::Default_clauseContext * /*ctx*/) override;

  virtual void
  exitDefault_kind(accparser::Default_kindContext * /*ctx*/) override;

  virtual void enterVector_length_clause(
      accparser::Vector_length_clauseContext * /*ctx*/) override;

  virtual void
  exitGang_clause(accparser::Gang_clauseContext * /*ctx*/) override;
  virtual void
  enterNum_gangs_clause(accparser::Num_gangs_clauseContext * /*ctx*/) override;
  virtual void
  enterWorker_clause(accparser::Worker_clauseContext * /*ctx*/) override;
  virtual void exitWorker_clause_modifier(
      accparser::Worker_clause_modifierContext * /*ctx*/) override;

  virtual void exitConst_int(accparser::Const_intContext * /*ctx*/) override;
  virtual void exitInt_expr(accparser::Int_exprContext * /*ctx*/) override;
  virtual void exitVar(accparser::VarContext * /*ctx*/) override;
};

OpenACCDirective *parseOpenACC(std::string);

std::string trimEnclosingWhiteSpace(std::string);
