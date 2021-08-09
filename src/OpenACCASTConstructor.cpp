#include "OpenACCASTConstructor.h"
#include "acclexer.h"
#include "accparser.h"
#include <antlr4-runtime.h>

OpenACCDirective *current_directive = NULL;
OpenACCClause *current_clause = NULL;

void OpenACCIRConstructor::enterData_directive(
    accparser::Data_directiveContext *ctx) {
  current_directive = new OpenACCDirective(ACCD_data);
}

void OpenACCIRConstructor::enterEnter_data_directive(
    accparser::Enter_data_directiveContext *ctx) {
  current_directive = new OpenACCDirective(ACCD_enter_data);
}

void OpenACCIRConstructor::enterExit_data_directive(
    accparser::Exit_data_directiveContext *ctx) {
  current_directive = new OpenACCDirective(ACCD_exit_data);
}

void OpenACCIRConstructor::enterParallel_directive(
    accparser::Parallel_directiveContext *ctx) {
  current_directive = new OpenACCDirective(ACCD_parallel);
}

void OpenACCIRConstructor::enterLoop_directive(
    accparser::Loop_directiveContext *ctx) {
  current_directive = new OpenACCDirective(ACCD_loop);
}

void OpenACCIRConstructor::enterParallel_loop_directive(
    accparser::Parallel_loop_directiveContext *ctx) {
  current_directive = new OpenACCDirective(ACCD_parallel_loop);
}

void OpenACCIRConstructor::enterAsync_clause(
    accparser::Async_clauseContext *ctx) {
  std::string expression = trimEnclosingWhiteSpace(ctx->getText());
  current_clause = current_directive->addOpenACCClause(ACCC_async);
}

void OpenACCIRConstructor::exitAsync_clause(
    accparser::Async_clauseContext *ctx) {
  ((OpenACCAsyncClause *)current_clause)
      ->mergeClause(current_directive, current_clause);
}

void OpenACCIRConstructor::enterAuto_clause(
    accparser::Auto_clauseContext *ctx) {
  std::string expression = trimEnclosingWhiteSpace(ctx->getText());
  current_clause = current_directive->addOpenACCClause(ACCC_auto);
}

void OpenACCIRConstructor::enterCollapse_clause(
    accparser::Collapse_clauseContext *ctx) {
  std::string expression = trimEnclosingWhiteSpace(ctx->getText());
  current_clause = current_directive->addOpenACCClause(ACCC_collapse);
}

void OpenACCIRConstructor::exitCollapse_clause(
    accparser::Collapse_clauseContext *ctx) {
  ((OpenACCCollapseClause *)current_clause)
      ->mergeClause(current_directive, current_clause);
}

void OpenACCIRConstructor::enterAttach_clause(
    accparser::Attach_clauseContext *ctx) {
  current_clause = current_directive->addOpenACCClause(ACCC_attach);
}

void OpenACCIRConstructor::enterCopy_clause(
    accparser::Copy_clauseContext *ctx) {
  current_clause = current_directive->addOpenACCClause(ACCC_copy);
}

void OpenACCIRConstructor::enterCopyin_clause(
    accparser::Copyin_clauseContext *ctx) {
  current_clause = current_directive->addOpenACCClause(ACCC_copyin);
  ((OpenACCCopyinClause *)current_clause)->setModifier(ACCC_COPYIN_unspecified);
}

void OpenACCIRConstructor::exitCopyin_clause_modifier(
    accparser::Copyin_clause_modifierContext *ctx) {
  ((OpenACCCopyinClause *)current_clause)->setModifier(ACCC_COPYIN_readonly);
}

void OpenACCIRConstructor::exitCopyin_clause(
    accparser::Copyin_clauseContext *ctx) {
  ((OpenACCCopyinClause *)current_clause)
      ->mergeClause(current_directive, current_clause);
}

void OpenACCIRConstructor::enterCopyin_no_modifier_clause(
    accparser::Copyin_no_modifier_clauseContext *ctx) {
  current_clause = current_directive->addOpenACCClause(ACCC_copyin);
  ((OpenACCCopyinClause *)current_clause)->setModifier(ACCC_COPYIN_unspecified);
}

void OpenACCIRConstructor::exitCopyin_no_modifier_clause(
    accparser::Copyin_no_modifier_clauseContext *ctx) {
  ((OpenACCCopyinClause *)current_clause)
      ->mergeClause(current_directive, current_clause);
}

void OpenACCIRConstructor::enterCopyout_clause(
    accparser::Copyout_clauseContext *ctx) {
  current_clause = current_directive->addOpenACCClause(ACCC_copyout);
  ((OpenACCCopyoutClause *)current_clause)
      ->setModifier(ACCC_COPYOUT_unspecified);
}

void OpenACCIRConstructor::exitCopyout_clause_modifier(
    accparser::Copyout_clause_modifierContext *ctx) {
  ((OpenACCCopyoutClause *)current_clause)->setModifier(ACCC_COPYOUT_zero);
}

void OpenACCIRConstructor::exitCopyout_clause(
    accparser::Copyout_clauseContext *ctx) {
  ((OpenACCCopyoutClause *)current_clause)
      ->mergeClause(current_directive, current_clause);
}

void OpenACCIRConstructor::enterCopyout_no_modifier_clause(
    accparser::Copyout_no_modifier_clauseContext *ctx) {
  current_clause = current_directive->addOpenACCClause(ACCC_copyout);
  ((OpenACCCopyoutClause *)current_clause)->setModifier(ACCC_COPYOUT_unspecified);
}

void OpenACCIRConstructor::exitCopyout_no_modifier_clause(
    accparser::Copyout_no_modifier_clauseContext *ctx) {
  ((OpenACCCopyoutClause *)current_clause)
      ->mergeClause(current_directive, current_clause);
}

void OpenACCIRConstructor::enterCreate_clause(
    accparser::Create_clauseContext *ctx) {
  current_clause = current_directive->addOpenACCClause(ACCC_create);
  ((OpenACCCreateClause *)current_clause)->setModifier(ACCC_CREATE_unspecified);
}

void OpenACCIRConstructor::exitCreate_clause(
    accparser::Create_clauseContext *ctx) {
  ((OpenACCCreateClause *)current_clause)
      ->mergeClause(current_directive, current_clause);
}

void OpenACCIRConstructor::exitCreate_clause_modifier(
    accparser::Create_clause_modifierContext *ctx) {
  ((OpenACCCreateClause *)current_clause)->setModifier(ACCC_CREATE_zero);
}

void OpenACCIRConstructor::enterDefault_clause(
    accparser::Default_clauseContext *ctx) {
  current_clause = current_directive->addOpenACCClause(ACCC_default);
};

void OpenACCIRConstructor::exitDefault_kind(
    accparser::Default_kindContext *ctx) {
  std::string expression = trimEnclosingWhiteSpace(ctx->getText());
  OpenACCDefaultClauseKind kind = ACCC_DEFAULT_unspecified;
  if (expression == "none")
    kind = ACCC_DEFAULT_none;
  else if (expression == "present")
    kind = ACCC_DEFAULT_present;
  ((OpenACCDefaultClause *)current_clause)->setKind(kind);
};

void OpenACCIRConstructor::enterDelete_clause(
    accparser::Delete_clauseContext *ctx) {
  current_clause = current_directive->addOpenACCClause(ACCC_delete);
}

void OpenACCIRConstructor::enterDetach_clause(
    accparser::Detach_clauseContext *ctx) {
  current_clause = current_directive->addOpenACCClause(ACCC_detach);
}

void OpenACCIRConstructor::enterDevice_type_clause(
    accparser::Device_type_clauseContext *ctx) {
  current_clause = current_directive->addOpenACCClause(ACCC_device_type);
}

void OpenACCIRConstructor::enterDeviceptr_clause(
    accparser::Deviceptr_clauseContext *ctx) {
  current_clause = current_directive->addOpenACCClause(ACCC_deviceptr);
}

void OpenACCIRConstructor::enterFinalize_clause(
    accparser::Finalize_clauseContext *ctx) {
  std::string expression = trimEnclosingWhiteSpace(ctx->getText());
  current_clause = current_directive->addOpenACCClause(ACCC_finalize);
}

void OpenACCIRConstructor::enterFirstprivate_clause(
    accparser::Firstprivate_clauseContext *ctx) {
  current_clause = current_directive->addOpenACCClause(ACCC_firstprivate);
}

void OpenACCIRConstructor::enterGang_clause(
    accparser::Gang_clauseContext *ctx) {
  std::string expression = trimEnclosingWhiteSpace(ctx->getText());
  current_clause = current_directive->addOpenACCClause(ACCC_gang);
};

void OpenACCIRConstructor::exitGang_clause(accparser::Gang_clauseContext *ctx) {
  ((OpenACCGangClause *)current_clause)
      ->mergeClause(current_directive, current_clause);
};

void OpenACCIRConstructor::enterIf_clause(accparser::If_clauseContext *ctx) {
  std::string expression = trimEnclosingWhiteSpace(ctx->getText());
  current_clause = current_directive->addOpenACCClause(ACCC_if);
}

void OpenACCIRConstructor::enterIndependent_clause(
    accparser::Independent_clauseContext *ctx) {
  std::string expression = trimEnclosingWhiteSpace(ctx->getText());
  current_clause = current_directive->addOpenACCClause(ACCC_independent);
}

void OpenACCIRConstructor::enterNo_create_clause(
    accparser::No_create_clauseContext *ctx) {
  current_clause = current_directive->addOpenACCClause(ACCC_no_create);
}

void OpenACCIRConstructor::enterNum_gangs_clause(
    accparser::Num_gangs_clauseContext *ctx) {
  std::string expression = trimEnclosingWhiteSpace(ctx->getText());
  current_clause = current_directive->addOpenACCClause(ACCC_num_gangs);
};

void OpenACCIRConstructor::exitNum_gangs_clause(
    accparser::Num_gangs_clauseContext *ctx) {
  ((OpenACCNumGangsClause *)current_clause)
      ->mergeClause(current_directive, current_clause);
};

void OpenACCIRConstructor::enterNum_workers_clause(
    accparser::Num_workers_clauseContext *ctx) {
  std::string expression = trimEnclosingWhiteSpace(ctx->getText());
  current_clause = current_directive->addOpenACCClause(ACCC_num_workers);
};

void OpenACCIRConstructor::exitNum_workers_clause(
    accparser::Num_workers_clauseContext *ctx) {
  ((OpenACCNumWorkersClause *)current_clause)
      ->mergeClause(current_directive, current_clause);
};

void OpenACCIRConstructor::enterPresent_clause(
    accparser::Present_clauseContext *ctx) {
  current_clause = current_directive->addOpenACCClause(ACCC_present);
}

void OpenACCIRConstructor::enterPrivate_clause(
    accparser::Private_clauseContext *ctx) {
  current_clause = current_directive->addOpenACCClause(ACCC_private);
}

void OpenACCIRConstructor::enterReduction_clause(
    accparser::Reduction_clauseContext *ctx) {
  current_clause = current_directive->addOpenACCClause(ACCC_reduction);
  ((OpenACCReductionClause *)current_clause)
      ->setOperator(ACCC_REDUCTION_unspecified);
}

void OpenACCIRConstructor::exitReduction_operator(
    accparser::Reduction_operatorContext *ctx) {
  std::string expression = trimEnclosingWhiteSpace(ctx->getText());
  OpenACCReductionClauseOperator reduction_operator =
      ACCC_REDUCTION_unspecified;
  if (expression == "+")
    reduction_operator = ACCC_REDUCTION_add;
  else if (expression == "*")
    reduction_operator = ACCC_REDUCTION_mul;
  else if (expression == "max")
    reduction_operator = ACCC_REDUCTION_max;
  else if (expression == "min")
    reduction_operator = ACCC_REDUCTION_min;
  else if (expression == "&")
    reduction_operator = ACCC_REDUCTION_bitand;
  else if (expression == "|")
    reduction_operator = ACCC_REDUCTION_bitor;
  else if (expression == "^")
    reduction_operator = ACCC_REDUCTION_bitxor;
  else if (expression == "&&")
    reduction_operator = ACCC_REDUCTION_logand;
  else if (expression == "||")
    reduction_operator = ACCC_REDUCTION_logor;
  ((OpenACCReductionClause *)current_clause)->setOperator(reduction_operator);
};

void OpenACCIRConstructor::exitReduction_clause(
    accparser::Reduction_clauseContext *ctx) {
  ((OpenACCReductionClause *)current_clause)
      ->mergeClause(current_directive, current_clause);
}

void OpenACCIRConstructor::enterSelf_clause(
    accparser::Self_clauseContext *ctx) {
  std::string expression = trimEnclosingWhiteSpace(ctx->getText());
  current_clause = current_directive->addOpenACCClause(ACCC_self);
}

void OpenACCIRConstructor::exitSelf_clause(accparser::Self_clauseContext *ctx) {
  ((OpenACCSelfClause *)current_clause)
      ->mergeClause(current_directive, current_clause);
}

void OpenACCIRConstructor::exitCondition(accparser::ConditionContext *ctx) {
  std::string expression = trimEnclosingWhiteSpace(ctx->getText());
  current_clause->addLangExpr(expression);
};

void OpenACCIRConstructor::enterSeq_clause(accparser::Seq_clauseContext *ctx) {
  std::string expression = trimEnclosingWhiteSpace(ctx->getText());
  current_clause = current_directive->addOpenACCClause(ACCC_seq);
}

void OpenACCIRConstructor::enterTile_clause(
    accparser::Tile_clauseContext *ctx) {
  current_clause = current_directive->addOpenACCClause(ACCC_tile);
}

void OpenACCIRConstructor::enterVector_clause(
    accparser::Vector_clauseContext *ctx) {
  current_clause = current_directive->addOpenACCClause(ACCC_vector);
  ((OpenACCVectorClause *)current_clause)->setModifier(ACCC_VECTOR_unspecified);
}

void OpenACCIRConstructor::exitVector_clause_modifier(
    accparser::Vector_clause_modifierContext *ctx) {
  ((OpenACCVectorClause *)current_clause)->setModifier(ACCC_VECTOR_length);
}

void OpenACCIRConstructor::exitVector_clause(
    accparser::Vector_clauseContext *ctx) {
  ((OpenACCVectorClause *)current_clause)
      ->mergeClause(current_directive, current_clause);
}

void OpenACCIRConstructor::enterVector_length_clause(
    accparser::Vector_length_clauseContext *ctx) {
  std::string expression = trimEnclosingWhiteSpace(ctx->getText());
  current_clause = current_directive->addOpenACCClause(ACCC_vector_length);
};

void OpenACCIRConstructor::exitVector_length_clause(
    accparser::Vector_length_clauseContext *ctx) {
  ((OpenACCVectorLengthClause *)current_clause)
      ->mergeClause(current_directive, current_clause);
};

void OpenACCIRConstructor::enterWait_clause(
    accparser::Wait_clauseContext *ctx) {
  std::string expression = trimEnclosingWhiteSpace(ctx->getText());
  current_clause = current_directive->addOpenACCClause(ACCC_wait);
};

void OpenACCIRConstructor::exitWait_clause(accparser::Wait_clauseContext *ctx) {
  ((OpenACCWaitClause *)current_clause)
      ->mergeClause(current_directive, current_clause);
};

void OpenACCIRConstructor::enterWorker_clause(
    accparser::Worker_clauseContext *ctx) {
  current_clause = current_directive->addOpenACCClause(ACCC_worker);
  ((OpenACCWorkerClause *)current_clause)->setModifier(ACCC_WORKER_unspecified);
};

void OpenACCIRConstructor::exitWorker_clause_modifier(
    accparser::Worker_clause_modifierContext *ctx) {
  std::string expression = trimEnclosingWhiteSpace(ctx->getText());
  ((OpenACCWorkerClause *)current_clause)->setModifier(ACCC_WORKER_num);
};

void OpenACCIRConstructor::exitWorker_clause(
    accparser::Worker_clauseContext *ctx) {
  ((OpenACCWorkerClause *)current_clause)
      ->mergeClause(current_directive, current_clause);
}

void OpenACCIRConstructor::exitConst_int(accparser::Const_intContext *ctx) {
  std::string expression = trimEnclosingWhiteSpace(ctx->getText());
  current_clause->addLangExpr(expression);
};

void OpenACCIRConstructor::exitInt_expr(accparser::Int_exprContext *ctx) {
  std::string expression = trimEnclosingWhiteSpace(ctx->getText());
  current_clause->addLangExpr(expression);
};

void OpenACCIRConstructor::exitVar(accparser::VarContext *ctx) {
  std::string expression = trimEnclosingWhiteSpace(ctx->getText());
  current_clause->addLangExpr(expression);
};

std::string trimEnclosingWhiteSpace(std::string expression) {

  const std::string white_space = " \n\r\t\f\v";

  size_t start = expression.find_first_not_of(white_space);
  if (start != std::string::npos) {
    expression = expression.substr(start);
  }

  size_t end = expression.find_last_not_of(white_space);
  if (end != std::string::npos) {
    expression = expression.substr(0, end + 1);
  }

  return expression;
}

OpenACCDirective *parseOpenACC(std::string source) {

  antlr4::ANTLRInputStream input(source);
  acclexer lexer(&input);
  antlr4::CommonTokenStream tokens(&lexer);
  tokens.fill();
  accparser parser(&tokens);
  parser.setBuildParseTree(true);
  parser.setErrorHandler(std::make_shared<antlr4::BailErrorStrategy>());

  current_directive = NULL;
  antlr4::tree::ParseTree *tree = parser.acc();

  antlr4::tree::ParseTreeWalker *walker = new antlr4::tree::ParseTreeWalker();
  walker->walk(new OpenACCIRConstructor(), tree);
  assert(current_directive != NULL);

  return current_directive;
}
