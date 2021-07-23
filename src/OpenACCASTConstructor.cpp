#include "OpenACCASTConstructor.h"
#include "OpenACCIR.h"

OpenACCDirective* current_directive = NULL;
OpenACCClause* current_clause = NULL;

void OpenACCIRConstructor::enterParallel_directive(accparser::Parallel_directiveContext * /*ctx*/) {
    current_directive = new OpenACCDirective(ACCD_parallel);
}

void OpenACCIRConstructor::exitParallel_directive(accparser::Parallel_directiveContext * /*ctx*/) {
    ;
}

void OpenACCIRConstructor::enterPrivate_clause(accparser::Private_clauseContext * /*ctx*/) {
    current_clause = current_directive->addOpenACCClause(ACCC_private);
}

void OpenACCIRConstructor::exitPrivate_clause(accparser::Private_clauseContext * /*ctx*/) {
    ;
}

void OpenACCIRConstructor::exitVar(accparser::VarContext * ctx) {
    std::string expression = ctx->getText();
    current_clause->addLangExpr(expression);
};

