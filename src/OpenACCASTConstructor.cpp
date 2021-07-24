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

void OpenACCIRConstructor::enterPrivate_clause(
    accparser::Private_clauseContext *ctx) {
  current_clause = current_directive->addOpenACCClause(ACCC_private);
}

void OpenACCIRConstructor::exitVar(accparser::VarContext *ctx) {
  std::string expression = ctx->getText();
  current_clause->addLangExpr(expression);
};
