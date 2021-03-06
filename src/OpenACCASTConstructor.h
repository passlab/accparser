#include "OpenACCIR.h"
#include "accparserBaseListener.h"

class OpenACCIRConstructor : public accparserBaseListener {
public:
  virtual void enterC_prefix(accparser::C_prefixContext * /*ctx*/) override;
  virtual void
  enterFortran_prefix(accparser::Fortran_prefixContext * /*ctx*/) override;
  virtual void
  enterAtomic_directive(accparser::Atomic_directiveContext * /*ctx*/) override;
  virtual void
  enterCache_directive(accparser::Cache_directiveContext * /*ctx*/) override;
  virtual void exitCache_directive_modifier(
      accparser::accparser::Cache_directive_modifierContext * /*ctx*/) override;
  virtual void
  enterData_directive(accparser::Data_directiveContext * /*ctx*/) override;
  virtual void enterDeclare_directive(
      accparser::Declare_directiveContext * /*ctx*/) override;
  virtual void
  enterEnd_directive(accparser::End_directiveContext * /*ctx*/) override;
  virtual void exitFortran_paired_directive(
      accparser::Fortran_paired_directiveContext * /*ctx*/) override;
  virtual void enterEnter_data_directive(
      accparser::Enter_data_directiveContext * /*ctx*/) override;
  virtual void enterExit_data_directive(
      accparser::Exit_data_directiveContext * /*ctx*/) override;
  virtual void enterHost_data_directive(
      accparser::Host_data_directiveContext * /*ctx*/) override;
  virtual void enterEnd_host_data_directive(
      accparser::End_host_data_directiveContext * /*ctx*/) override;
  virtual void
  enterInit_directive(accparser::Init_directiveContext * /*ctx*/) override;
  virtual void enterKernels_directive(
      accparser::Kernels_directiveContext * /*ctx*/) override;
  virtual void enterKernels_loop_directive(
      accparser::Kernels_loop_directiveContext * /*ctx*/) override;
  virtual void
  enterLoop_directive(accparser::Loop_directiveContext * /*ctx*/) override;
  virtual void enterParallel_loop_directive(
      accparser::Parallel_loop_directiveContext * /*ctx*/) override;
  virtual void enterParallel_directive(
      accparser::Parallel_directiveContext * /*ctx*/) override;
  virtual void enterRoutine_directive(
      accparser::Routine_directiveContext * /*ctx*/) override;
  virtual void exitName(accparser::NameContext * /*ctx*/) override;
  virtual void
  enterSerial_directive(accparser::Serial_directiveContext * /*ctx*/) override;
  virtual void enterSerial_loop_directive(
      accparser::Serial_loop_directiveContext * /*ctx*/) override;
  virtual void
  enterSet_directive(accparser::Set_directiveContext * /*ctx*/) override;
  virtual void enterShutdown_directive(
      accparser::Shutdown_directiveContext * /*ctx*/) override;
  virtual void
  enterUpdate_directive(accparser::Update_directiveContext * /*ctx*/) override;
  virtual void
  enterWait_directive(accparser::Wait_directiveContext * /*ctx*/) override;

  virtual void
  enterAsync_clause(accparser::Async_clauseContext * /*ctx*/) override;
  virtual void
  exitAsync_clause(accparser::Async_clauseContext * /*ctx*/) override;
  virtual void
  enterAttach_clause(accparser::Attach_clauseContext * /*ctx*/) override;
  virtual void
  enterAuto_clause(accparser::Auto_clauseContext * /*ctx*/) override;
  virtual void
  enterBind_clause(accparser::Bind_clauseContext * /*ctx*/) override;
  virtual void
  exitName_or_string(accparser::Name_or_stringContext * /*ctx*/) override;
  virtual void
  exitBind_clause(accparser::Bind_clauseContext * /*ctx*/) override;
  virtual void
  enterCapture_clause(accparser::Capture_clauseContext * /*ctx*/) override;
  virtual void
  enterCollapse_clause(accparser::Collapse_clauseContext * /*ctx*/) override;
  virtual void
  exitCollapse_clause(accparser::Collapse_clauseContext * /*ctx*/) override;
  virtual void
  enterCopy_clause(accparser::Copy_clauseContext * /*ctx*/) override;
  virtual void
  enterCopyin_clause(accparser::Copyin_clauseContext * /*ctx*/) override;
  virtual void exitCopyin_clause_modifier(
      accparser::Copyin_clause_modifierContext * /*ctx*/) override;
  virtual void
  exitCopyin_clause(accparser::Copyin_clauseContext * /*ctx*/) override;
  virtual void enterCopyin_no_modifier_clause(
      accparser::Copyin_no_modifier_clauseContext * /*ctx*/) override;
  virtual void exitCopyin_no_modifier_clause(
      accparser::Copyin_no_modifier_clauseContext * /*ctx*/) override;
  virtual void
  enterCopyout_clause(accparser::Copyout_clauseContext * /*ctx*/) override;
  virtual void exitCopyout_clause_modifier(
      accparser::Copyout_clause_modifierContext * /*ctx*/) override;
  virtual void
  exitCopyout_clause(accparser::Copyout_clauseContext * /*ctx*/) override;
  virtual void enterCopyout_no_modifier_clause(
      accparser::Copyout_no_modifier_clauseContext * /*ctx*/) override;
  virtual void exitCopyout_no_modifier_clause(
      accparser::Copyout_no_modifier_clauseContext * /*ctx*/) override;
  virtual void
  enterCreate_clause(accparser::Create_clauseContext * /*ctx*/) override;
  virtual void exitCreate_clause_modifier(
      accparser::Create_clause_modifierContext * /*ctx*/) override;
  virtual void
  exitCreate_clause(accparser::Create_clauseContext * /*ctx*/) override;
  virtual void enterCreate_no_modifier_clause(
      accparser::Create_no_modifier_clauseContext * /*ctx*/) override;
  virtual void exitCreate_no_modifier_clause(
      accparser::Create_no_modifier_clauseContext * /*ctx*/) override;
  virtual void
  enterDefault_clause(accparser::Default_clauseContext * /*ctx*/) override;
  virtual void
  exitDefault_kind(accparser::Default_kindContext * /*ctx*/) override;
  virtual void enterDefault_async_clause(
      accparser::Default_async_clauseContext * /*ctx*/) override;
  virtual void exitDefault_async_clause(
      accparser::Default_async_clauseContext * /*ctx*/) override;
  virtual void
  enterDelete_clause(accparser::Delete_clauseContext * /*ctx*/) override;
  virtual void
  enterDetach_clause(accparser::Detach_clauseContext * /*ctx*/) override;
  virtual void
  enterDevice_clause(accparser::Device_clauseContext * /*ctx*/) override;
  virtual void enterDevice_num_clause(
      accparser::Device_num_clauseContext * /*ctx*/) override;
  virtual void
  exitDevice_num_clause(accparser::Device_num_clauseContext * /*ctx*/) override;
  virtual void enterDevice_resident_clause(
      accparser::Device_resident_clauseContext * /*ctx*/) override;
  virtual void enterDevice_type_clause(
      accparser::Device_type_clauseContext * /*ctx*/) override;
  virtual void
  enterDeviceptr_clause(accparser::Deviceptr_clauseContext * /*ctx*/) override;
  virtual void
  enterFinalize_clause(accparser::Finalize_clauseContext * /*ctx*/) override;
  virtual void enterFirstprivate_clause(
      accparser::Firstprivate_clauseContext * /*ctx*/) override;
  virtual void
  enterGang_clause(accparser::Gang_clauseContext * /*ctx*/) override;
  virtual void
  exitGang_clause(accparser::Gang_clauseContext * /*ctx*/) override;
  virtual void
  enterNohost_clause(accparser::Nohost_clauseContext * /*ctx*/) override;
  virtual void enterGang_no_list_clause(
      accparser::Gang_no_list_clauseContext * /*ctx*/) override;
  virtual void
  enterHost_clause(accparser::Host_clauseContext * /*ctx*/) override;
  virtual void enterIf_clause(accparser::If_clauseContext * /*ctx*/) override;
  virtual void enterIf_present_clause(
      accparser::If_present_clauseContext * /*ctx*/) override;
  virtual void enterIndependent_clause(
      accparser::Independent_clauseContext * /*ctx*/) override;
  virtual void
  enterLink_clause(accparser::Link_clauseContext * /*ctx*/) override;
  virtual void
  enterNo_create_clause(accparser::No_create_clauseContext * /*ctx*/) override;
  virtual void
  enterNum_gangs_clause(accparser::Num_gangs_clauseContext * /*ctx*/) override;
  virtual void
  exitNum_gangs_clause(accparser::Num_gangs_clauseContext * /*ctx*/) override;
  virtual void enterNum_workers_clause(
      accparser::Num_workers_clauseContext * /*ctx*/) override;
  virtual void exitNum_workers_clause(
      accparser::Num_workers_clauseContext * /*ctx*/) override;
  virtual void
  enterPresent_clause(accparser::Present_clauseContext * /*ctx*/) override;
  virtual void
  enterPrivate_clause(accparser::Private_clauseContext * /*ctx*/) override;
  virtual void
  enterRead_clause(accparser::Read_clauseContext * /*ctx*/) override;
  virtual void
  enterReduction_clause(accparser::Reduction_clauseContext * /*ctx*/) override;
  virtual void exitReduction_operator(
      accparser::Reduction_operatorContext * /*ctx*/) override;
  virtual void
  exitReduction_clause(accparser::Reduction_clauseContext * /*ctx*/) override;
  virtual void
  enterSelf_clause(accparser::Self_clauseContext * /*ctx*/) override;
  virtual void
  exitSelf_clause(accparser::Self_clauseContext * /*ctx*/) override;
  virtual void
  enterSelf_list_clause(accparser::Self_list_clauseContext * /*ctx*/) override;
  virtual void enterSeq_clause(accparser::Seq_clauseContext * /*ctx*/) override;
  virtual void
  enterTile_clause(accparser::Tile_clauseContext * /*ctx*/) override;
  virtual void
  enterUpdate_clause(accparser::Update_clauseContext * /*ctx*/) override;
  virtual void enterUse_device_clause(
      accparser::Use_device_clauseContext * /*ctx*/) override;
  virtual void
  enterVector_clause(accparser::Vector_clauseContext * /*ctx*/) override;
  virtual void exitVector_clause_modifier(
      accparser::Vector_clause_modifierContext * /*ctx*/) override;
  virtual void
  exitVector_clause(accparser::Vector_clauseContext * /*ctx*/) override;
  virtual void enterVector_length_clause(
      accparser::Vector_length_clauseContext * /*ctx*/) override;
  virtual void exitVector_length_clause(
      accparser::Vector_length_clauseContext * /*ctx*/) override;
  virtual void enterVector_no_modifier_clause(
      accparser::Vector_no_modifier_clauseContext * /*ctx*/) override;
  virtual void
  enterWait_clause(accparser::Wait_clauseContext * /*ctx*/) override;
  virtual void
  exitWait_clause(accparser::Wait_clauseContext * /*ctx*/) override;
  virtual void enterWait_argument_clause(
      accparser::Wait_argument_clauseContext * /*ctx*/) override;
  virtual void enterWait_argument_queues(
      accparser::Wait_argument_queuesContext * /*ctx*/) override;
  virtual void exitWait_argument_int_expr(
      accparser::Wait_argument_int_exprContext * /*ctx*/) override;
  virtual void exitWait_argument_clause(
      accparser::Wait_argument_clauseContext * /*ctx*/) override;
  virtual void
  enterWorker_clause(accparser::Worker_clauseContext * /*ctx*/) override;
  virtual void exitWorker_clause_modifier(
      accparser::Worker_clause_modifierContext * /*ctx*/) override;
  virtual void
  exitWorker_clause(accparser::Worker_clauseContext * /*ctx*/) override;
  virtual void enterWorker_no_modifier_clause(
      accparser::Worker_no_modifier_clauseContext * /*ctx*/) override;
  virtual void
  enterWrite_clause(accparser::Write_clauseContext * /*ctx*/) override;

  virtual void exitConst_int(accparser::Const_intContext * /*ctx*/) override;
  virtual void exitInt_expr(accparser::Int_exprContext * /*ctx*/) override;
  virtual void
  exitWait_int_expr(accparser::Wait_int_exprContext * /*ctx*/) override;
  virtual void exitCondition(accparser::ConditionContext * /*ctx*/) override;
  virtual void exitVar(accparser::VarContext * /*ctx*/) override;
};

OpenACCDirective *parseOpenACC(std::string);

std::string trimEnclosingWhiteSpace(std::string);
