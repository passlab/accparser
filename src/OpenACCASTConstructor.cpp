#include "OpenACCASTConstructor.h"
#include "OpenACCIR.h"

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

void OpenACCIRConstructor::enterPrivate_clause(accparser::Private_clauseContext *ctx) {
  current_clause = current_directive->addOpenACCClause(ACCC_private);
}

void OpenACCIRConstructor::enterFirstprivate_clause(accparser::Firstprivate_clauseContext *ctx) {
  current_clause = current_directive->addOpenACCClause(ACCC_firstprivate);
}

void OpenACCIRConstructor::enterAttach_clause(accparser::Attach_clauseContext *ctx) {
  current_clause = current_directive->addOpenACCClause(ACCC_attach);
}

void OpenACCIRConstructor::enterNo_create_clause(accparser::No_create_clauseContext *ctx) {
  current_clause = current_directive->addOpenACCClause(ACCC_no_create);
}

void OpenACCIRConstructor::enterAsync_clause(accparser::Async_clauseContext *ctx) {
  std::string expression = ctx->getText();
  current_clause = current_directive->addOpenACCClause(ACCC_async);
}

void OpenACCIRConstructor::enterCopy_clause(accparser::Copy_clauseContext *ctx) {
  current_clause = current_directive->addOpenACCClause(ACCC_copy);
}

void OpenACCIRConstructor::enterPresent_clause(accparser::Present_clauseContext *ctx) {
  current_clause = current_directive->addOpenACCClause(ACCC_present);
}

void OpenACCIRConstructor::enterDeviceptr_clause(accparser::Deviceptr_clauseContext *ctx) {
  current_clause = current_directive->addOpenACCClause(ACCC_deviceptr);
}

void OpenACCIRConstructor::exitGang_clause(accparser::Gang_clauseContext *ctx) {
  std::string expression = ctx->getText();
  current_clause = current_directive->addOpenACCClause(ACCC_gang);
};

void OpenACCIRConstructor::enterNum_gangs_clause(accparser::Num_gangs_clauseContext *ctx) {
  std::string expression = ctx->getText();
  current_clause = current_directive->addOpenACCClause(ACCC_num_gangs);
};

void OpenACCIRConstructor::exitWorker_clause(accparser::Worker_clauseContext *ctx) {
  std::string expression = ctx->getText();
  current_clause = current_directive->addOpenACCClause(ACCC_worker);
};

void OpenACCIRConstructor::exitConst_int(accparser::Const_intContext *ctx) {
  std::string expression = ctx->getText();
  current_clause->addLangExpr(expression);
};

void OpenACCIRConstructor::exitInt_expr(accparser::Int_exprContext *ctx) {
  std::string expression = ctx->getText();
  current_clause->addLangExpr(expression);
};

void OpenACCIRConstructor::exitVar(accparser::VarContext *ctx) {
  std::string expression = ctx->getText();
  current_clause->addLangExpr(expression);
};
