#include "OpenACCASTConstructor.h"
#include "acclexer.h"
#include "accparser.h"
#include <antlr4-runtime.h>

OpenACCDirective *current_directive = NULL;
OpenACCClause *current_clause = NULL;

void OpenACCIRConstructor::enterParallel_directive(
    accparser::Parallel_directiveContext *ctx) {
  current_directive = new OpenACCDirective(ACCD_parallel);
}

void OpenACCIRConstructor::enterParallel_loop_directive(
    accparser::Parallel_loop_directiveContext *ctx) {
  current_directive = new OpenACCDirective(ACCD_parallel_loop);
}

void OpenACCIRConstructor::enterPrivate_clause(
    accparser::Private_clauseContext *ctx) {
  current_clause = current_directive->addOpenACCClause(ACCC_private);
}

void OpenACCIRConstructor::enterFirstprivate_clause(
    accparser::Firstprivate_clauseContext *ctx) {
  current_clause = current_directive->addOpenACCClause(ACCC_firstprivate);
}

void OpenACCIRConstructor::enterDevice_type_clause(
    accparser::Device_type_clauseContext *ctx) {
  current_clause = current_directive->addOpenACCClause(ACCC_device_type);
}

void OpenACCIRConstructor::enterAttach_clause(
    accparser::Attach_clauseContext *ctx) {
  current_clause = current_directive->addOpenACCClause(ACCC_attach);
}

void OpenACCIRConstructor::enterNo_create_clause(
    accparser::No_create_clauseContext *ctx) {
  current_clause = current_directive->addOpenACCClause(ACCC_no_create);
}

void OpenACCIRConstructor::enterAsync_clause(
    accparser::Async_clauseContext *ctx) {
  std::string expression = trimEnclosingWhiteSpace(ctx->getText());
  current_clause = current_directive->addOpenACCClause(ACCC_async);
}

void OpenACCIRConstructor::enterIf_clause(
    accparser::If_clauseContext *ctx) {
  std::string expression = trimEnclosingWhiteSpace(ctx->getText());
  current_clause = current_directive->addOpenACCClause(ACCC_if);
}

void OpenACCIRConstructor::enterSelf_clause(
    accparser::Self_clauseContext *ctx) {
  std::string expression = trimEnclosingWhiteSpace(ctx->getText());
  current_clause = current_directive->addOpenACCClause(ACCC_self);
}

void OpenACCIRConstructor::enterCopy_clause(
    accparser::Copy_clauseContext *ctx) {
  current_clause = current_directive->addOpenACCClause(ACCC_copy);
}

void OpenACCIRConstructor::enterCopyin_clause(
    accparser::Copyin_clauseContext *ctx) {
  current_clause = current_directive->addOpenACCClause(ACCC_copyin);
  ((OpenACCCopyinClause *)current_clause)
      ->setCopyinClauseModifier(ACCC_COPYIN_unspecified);
}

void OpenACCIRConstructor::exitCopyin_clause_modifier(
    accparser::Copyin_clause_modifierContext *ctx) {
  ((OpenACCCopyinClause *)current_clause)
      ->setCopyinClauseModifier(ACCC_COPYIN_readonly);
}

void OpenACCIRConstructor::exitCopyin_clause(
    accparser::Copyin_clauseContext *ctx) {
  ((OpenACCCopyinClause *)current_clause)
      ->mergeCopyinClause(current_directive, current_clause);
}

void OpenACCIRConstructor::enterReduction_clause(
    accparser::Reduction_clauseContext *ctx) {
  current_clause = current_directive->addOpenACCClause(ACCC_reduction);
  ((OpenACCReductionClause *)current_clause)
      ->setReductionClauseOperator(ACCC_REDUCTION_unspecified);
}

void OpenACCIRConstructor::exitReduction_operator(
    accparser::Reduction_operatorContext *ctx) {
  std::string expression = trimEnclosingWhiteSpace(ctx->getText());
  OpenACCReductionClauseOperator reduction_operator = ACCC_REDUCTION_unspecified;
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
  ((OpenACCReductionClause *)current_clause)->setReductionClauseOperator(reduction_operator);
};

void OpenACCIRConstructor::exitReduction_clause(
    accparser::Reduction_clauseContext *ctx) {
  ((OpenACCReductionClause *)current_clause)
      ->mergeReductionClause(current_directive, current_clause);
}

void OpenACCIRConstructor::enterCopyout_clause(
    accparser::Copyout_clauseContext *ctx) {
  current_clause = current_directive->addOpenACCClause(ACCC_copyout);
  ((OpenACCCopyoutClause *)current_clause)
      ->setCopyoutClauseModifier(ACCC_COPYOUT_unspecified);
}

void OpenACCIRConstructor::exitCopyout_clause_modifier(
    accparser::Copyout_clause_modifierContext *ctx) {
  ((OpenACCCopyoutClause *)current_clause)
      ->setCopyoutClauseModifier(ACCC_COPYOUT_zero);
}

void OpenACCIRConstructor::exitCopyout_clause(
    accparser::Copyout_clauseContext *ctx) {
  ((OpenACCCopyoutClause *)current_clause)
      ->mergeCopyoutClause(current_directive, current_clause);
}

void OpenACCIRConstructor::enterCreate_clause(
    accparser::Create_clauseContext *ctx) {
  current_clause = current_directive->addOpenACCClause(ACCC_create);
  ((OpenACCCreateClause *)current_clause)
      ->setCreateClauseModifier(ACCC_CREATE_unspecified);
}

void OpenACCIRConstructor::exitCreate_clause(
    accparser::Create_clauseContext *ctx) {
  ((OpenACCCreateClause *)current_clause)
      ->mergeCreateClause(current_directive, current_clause);
}

void OpenACCIRConstructor::exitCreate_clause_modifier(
    accparser::Create_clause_modifierContext *ctx) {
  ((OpenACCCreateClause *)current_clause)
      ->setCreateClauseModifier(ACCC_CREATE_zero);
}

void OpenACCIRConstructor::enterPresent_clause(
    accparser::Present_clauseContext *ctx) {
  current_clause = current_directive->addOpenACCClause(ACCC_present);
}

void OpenACCIRConstructor::enterDeviceptr_clause(
    accparser::Deviceptr_clauseContext *ctx) {
  current_clause = current_directive->addOpenACCClause(ACCC_deviceptr);
}

void OpenACCIRConstructor::exitGang_clause(accparser::Gang_clauseContext *ctx) {
  std::string expression = trimEnclosingWhiteSpace(ctx->getText());
  current_clause = current_directive->addOpenACCClause(ACCC_gang);
};

void OpenACCIRConstructor::enterNum_gangs_clause(
    accparser::Num_gangs_clauseContext *ctx) {
  std::string expression = trimEnclosingWhiteSpace(ctx->getText());
  current_clause = current_directive->addOpenACCClause(ACCC_num_gangs);
};

void OpenACCIRConstructor::enterNum_workers_clause(
    accparser::Num_workers_clauseContext *ctx) {
  std::string expression = trimEnclosingWhiteSpace(ctx->getText());
  current_clause = current_directive->addOpenACCClause(ACCC_num_workers);
};

void OpenACCIRConstructor::enterWait_clause(
    accparser::Wait_clauseContext *ctx) {
  std::string expression = trimEnclosingWhiteSpace(ctx->getText());
  current_clause = current_directive->addOpenACCClause(ACCC_wait);
};

void OpenACCIRConstructor::enterVector_length_clause(
    accparser::Vector_length_clauseContext *ctx) {
  std::string expression = trimEnclosingWhiteSpace(ctx->getText());
  current_clause = current_directive->addOpenACCClause(ACCC_vector_length);
};

void OpenACCIRConstructor::enterWorker_clause(
    accparser::Worker_clauseContext *ctx) {
  current_clause = current_directive->addOpenACCClause(ACCC_worker);
  ((OpenACCWorkerClause *)current_clause)
      ->setWorkerClauseModifier(ACCC_WORKER_unspecified);
};

void OpenACCIRConstructor::exitWorker_clause_modifier(
    accparser::Worker_clause_modifierContext *ctx) {
  std::string expression = trimEnclosingWhiteSpace(ctx->getText());
  ((OpenACCWorkerClause *)current_clause)
      ->setWorkerClauseModifier(ACCC_WORKER_num);
};

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
  ((OpenACCDefaultClause *)current_clause)->setDefaultClauseKind(kind);
};

void OpenACCIRConstructor::exitConst_int(accparser::Const_intContext *ctx) {
  std::string expression = trimEnclosingWhiteSpace(ctx->getText());
  current_clause->addLangExpr(expression);
};

void OpenACCIRConstructor::exitInt_expr(accparser::Int_exprContext *ctx) {
  std::string expression = trimEnclosingWhiteSpace(ctx->getText());
  current_clause->addLangExpr(expression);
};

void OpenACCIRConstructor::exitCondition(accparser::ConditionContext *ctx) {
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
