#include "accparserBaseListener.h"

class OpenACCIRConstructor : public accparserBaseListener {
    public:
        virtual void enterParallel_directive(accparser::Parallel_directiveContext * /*ctx*/) override;
        virtual void exitParallel_directive(accparser::Parallel_directiveContext * /*ctx*/) override;
        virtual void enterPrivate_clause(accparser::Private_clauseContext * /*ctx*/) override;
        virtual void exitPrivate_clause(accparser::Private_clauseContext * /*ctx*/) override;

        //virtual void enterVar(accparser::Var_clauseContext * /*ctx*/) override;
        virtual void exitVar(accparser::VarContext * /*ctx*/) override;
};
