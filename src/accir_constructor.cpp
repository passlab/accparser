#include "accir_constructor.h"

void OpenACCIRConstructor::enterParallel_directive(accparser::Parallel_directiveContext * /*ctx*/) {
    std::cout << "A PARALLEL directive begins.\n";
}

void OpenACCIRConstructor::exitParallel_directive(accparser::Parallel_directiveContext * /*ctx*/) {
    std::cout << "A PARALLEL directive ends.\n";
}

void OpenACCIRConstructor::enterPrivate_clause(accparser::Private_clauseContext * /*ctx*/) {
    std::cout << "A PRIVATE clause begins.\n";
}

void OpenACCIRConstructor::exitPrivate_clause(accparser::Private_clauseContext * /*ctx*/) {
    std::cout << "A PRIVATE clause ends.\n";
}
