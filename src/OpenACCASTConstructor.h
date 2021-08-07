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
  exitCopyin_clause(accparser::Copyin_clauseContext * /*ctx*/) override;

  virtual void
  enterReduction_clause(accparser::Reduction_clauseContext * /*ctx*/) override;

  virtual void exitReduction_operator(
      accparser::Reduction_operatorContext * /*ctx*/) override;

  virtual void
  exitReduction_clause(accparser::Reduction_clauseContext * /*ctx*/) override;

  virtual void
  enterCopyout_clause(accparser::Copyout_clauseContext * /*ctx*/) override;

  virtual void exitCopyout_clause_modifier(
      accparser::Copyout_clause_modifierContext * /*ctx*/) override;

  virtual void
  exitCopyout_clause(accparser::Copyout_clauseContext * /*ctx*/) override;

  virtual void enterDevice_type_clause(
      accparser::Device_type_clauseContext * /*ctx*/) override;

  virtual void
  enterCreate_clause(accparser::Create_clauseContext * /*ctx*/) override;

  virtual void exitCreate_clause_modifier(
      accparser::Create_clause_modifierContext * /*ctx*/) override;

  virtual void
  exitCreate_clause(accparser::Create_clauseContext * /*ctx*/) override;

  virtual void
  enterNo_create_clause(accparser::No_create_clauseContext * /*ctx*/) override;

  virtual void
  enterDeviceptr_clause(accparser::Deviceptr_clauseContext * /*ctx*/) override;

  virtual void
  enterAsync_clause(accparser::Async_clauseContext * /*ctx*/) override;

  virtual void
  exitAsync_clause(accparser::Async_clauseContext * /*ctx*/) override;

  virtual void enterIf_clause(accparser::If_clauseContext * /*ctx*/) override;

  virtual void
  enterSelf_clause(accparser::Self_clauseContext * /*ctx*/) override;

  virtual void
  exitSelf_clause(accparser::Self_clauseContext * /*ctx*/) override;

  virtual void
  enterPresent_clause(accparser::Present_clauseContext * /*ctx*/) override;

  virtual void
  enterAttach_clause(accparser::Attach_clauseContext * /*ctx*/) override;

  virtual void enterNum_workers_clause(
      accparser::Num_workers_clauseContext * /*ctx*/) override;

  virtual void exitNum_workers_clause(
      accparser::Num_workers_clauseContext * /*ctx*/) override;

  virtual void
  enterWait_clause(accparser::Wait_clauseContext * /*ctx*/) override;

  virtual void
  enterDefault_clause(accparser::Default_clauseContext * /*ctx*/) override;

  virtual void
  exitDefault_kind(accparser::Default_kindContext * /*ctx*/) override;

  virtual void enterVector_length_clause(
      accparser::Vector_length_clauseContext * /*ctx*/) override;

  virtual void exitVector_length_clause(
      accparser::Vector_length_clauseContext * /*ctx*/) override;

  virtual void
  exitGang_clause(accparser::Gang_clauseContext * /*ctx*/) override;
  virtual void
  enterNum_gangs_clause(accparser::Num_gangs_clauseContext * /*ctx*/) override;
  virtual void
  exitNum_gangs_clause(accparser::Num_gangs_clauseContext * /*ctx*/) override;
  virtual void
  enterWorker_clause(accparser::Worker_clauseContext * /*ctx*/) override;
  virtual void exitWorker_clause_modifier(
      accparser::Worker_clause_modifierContext * /*ctx*/) override;

  virtual void exitConst_int(accparser::Const_intContext * /*ctx*/) override;
  virtual void exitInt_expr(accparser::Int_exprContext * /*ctx*/) override;
  virtual void exitCondition(accparser::ConditionContext * /*ctx*/) override;
  virtual void exitVar(accparser::VarContext * /*ctx*/) override;
};

OpenACCDirective *parseOpenACC(std::string);

std::string trimEnclosingWhiteSpace(std::string);
