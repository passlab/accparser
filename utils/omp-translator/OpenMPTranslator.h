#include "OpenACCASTConstructor.h"
#include "OpenMPIR.h"

std::vector<OpenMPDirective *> *convertParallelLoop(OpenACCDirective *);

void convertOpenACCClauses(OpenACCDirective *, std::vector<OpenMPDirective *> *);

std::vector<OpenMPDirective *> *generateOpenMP(OpenACCDirective *);
